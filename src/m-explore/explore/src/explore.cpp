/*********************************************************************
 *
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Robert Bosch LLC.
 *  Copyright (c) 2015-2016, Jiri Horner.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Jiri Horner nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************/

#include <explore/explore.h>

#include <thread>

inline static bool operator==(const geometry_msgs::Point& one,
                              const geometry_msgs::Point& two)
{
  double dx = one.x - two.x;
  double dy = one.y - two.y;
  double dist = sqrt(dx * dx + dy * dy);
  return dist < 0.01;
}

namespace explore
{
Explore::Explore()
  : private_nh_("~")
  , tf_listener_(ros::Duration(10.0))
  , costmap_client_(private_nh_, relative_nh_, &tf_listener_)
  , move_base_client_("move_base")
  , prev_distance_(0)
  , last_markers_count_(0)
{
  double timeout;
  double min_frontier_size;
  private_nh_.param("planner_frequency", planner_frequency_, 1.0);
  private_nh_.param("progress_timeout", timeout, 10.0);
  progress_timeout_ = ros::Duration(timeout);
  private_nh_.param("visualize", visualize_, false);
  private_nh_.param("potential_scale", potential_scale_, 1e-3);
  private_nh_.param("orientation_scale", orientation_scale_, 0.0);
  private_nh_.param("gain_scale", gain_scale_, 1.0);
  private_nh_.param("min_frontier_size", min_frontier_size, 0.4);
  
  // subscribe to semantic_goals
  sub_ = relative_nh_.subscribe("/semantic_goals", 1, &Explore::sPoseCallback, this);

  search_ = frontier_exploration::FrontierSearch(costmap_client_.getCostmap(),
                                                 potential_scale_, gain_scale_,
                                                 min_frontier_size);

  if (visualize_) {
    marker_array_publisher_ =
        private_nh_.advertise<visualization_msgs::MarkerArray>("frontiers", 10);
  }

  ROS_INFO("Waiting to connect to move_base server");
  move_base_client_.waitForServer();
  ROS_INFO("Connected to move_base server");

  exploring_timer_ =
      relative_nh_.createTimer(ros::Duration(1. / planner_frequency_),
                               [this](const ros::TimerEvent&) { makePlan(); });
}

Explore::~Explore()
{
  stop();
}

void Explore::visualizeFrontiers(
    const std::vector<frontier_exploration::Frontier>& frontiers)
{
  std_msgs::ColorRGBA blue;
  blue.r = 0;
  blue.g = 0;
  blue.b = 1.0;
  blue.a = 1.0;
  std_msgs::ColorRGBA red;
  red.r = 1.0;
  red.g = 0;
  red.b = 0;
  red.a = 1.0;
  std_msgs::ColorRGBA green;
  green.r = 0;
  green.g = 1.0;
  green.b = 0;
  green.a = 1.0;

  ROS_INFO("visualising %lu frontiers", frontiers.size());
  visualization_msgs::MarkerArray markers_msg;
  std::vector<visualization_msgs::Marker>& markers = markers_msg.markers;
  visualization_msgs::Marker m;

  m.header.frame_id = costmap_client_.getGlobalFrameID();
  m.header.stamp = ros::Time::now();
  m.ns = "frontiers";
  m.scale.x = 1.0;
  m.scale.y = 1.0;
  m.scale.z = 1.0;
  m.color.r = 0;
  m.color.g = 0;
  m.color.b = 255;
  m.color.a = 255;
  // lives forever
  m.lifetime = ros::Duration(0);
  m.frame_locked = true;

  // weighted frontiers are always sorted
  double min_cost = frontiers.empty() ? 0. : frontiers.front().cost;

  m.action = visualization_msgs::Marker::ADD;
  size_t id = 0;
  for (auto& frontier : frontiers) {
    m.type = visualization_msgs::Marker::POINTS;
    m.id = int(id);
    m.pose.position = {};
    m.scale.x = 0.1;
    m.scale.y = 0.1;
    m.scale.z = 0.1;
    m.points = frontier.points;
    if (goalOnBlacklist(frontier.centroid, false)) {
      m.color = red;
    } else {
      m.color = blue;
    }
    markers.push_back(m);
    ++id;
    m.type = visualization_msgs::Marker::SPHERE;
    m.id = int(id);
    m.pose.position = frontier.initial;
    // scale frontier according to its cost (costier frontiers will be smaller)
    double scale = std::min(std::abs(min_cost * 0.4 / frontier.cost), 0.5);
    m.scale.x = scale;
    m.scale.y = scale;
    m.scale.z = scale;
    m.points = {};
    m.color = green;
    markers.push_back(m);
    ++id;
  }
  size_t current_markers_count = markers.size();

  // delete previous markers, which are now unused
  m.action = visualization_msgs::Marker::DELETE;
  for (; id < last_markers_count_; ++id) {
    m.id = int(id);
    markers.push_back(m);
  }

  last_markers_count_ = current_markers_count;
  marker_array_publisher_.publish(markers_msg);
}

void Explore::sPoseCallback(const jackal_2dnav::sPoses& sPose_msg){
  
  // empty out object queues
  sPeople_.clear();
  sChairs_.clear();
  sBalls_.clear();
  
  if(sPose_msg.sPoses.size() > 0){
  
    // make temporary point
    sGoal temp; 
    
    // iterate through and then push back 
    for(int i = 0; i < sPose_msg.sPoses.size(); ++i){
    
      temp.sPoint.x = sPose_msg.sPoses[i].objPose.position.x;
      temp.sPoint.y = sPose_msg.sPoses[i].objPose.position.y;
      
      temp.label = sPose_msg.sPoses[i].objLabel;
    
      if(temp.label == "person")
        sPeople_.push_back(temp);      
      
      if(temp.label == "chair")
        sChairs_.push_back(temp);      
      
      if(temp.label == "ball")
        sBalls_.push_back(temp);
    }
    
    if(sPeople_.size() > numObj_[0]){
      numObj_[0] = sPeople_.size();
      newObj_[0] = true;
    }
    else
      newObj_[0] = false; 
      
    if(sChairs_.size() > numObj_[1]){
      numObj_[1] = sChairs_.size();
      newObj_[1] = true;
    }
    else
      newObj_[1] = false; 
      
    if(sBalls_.size() > numObj_[2]){
      numObj_[2] = sBalls_.size();
      newObj_[2] = true;
    }
    else
      newObj_[2] = false; 
  }
}

void Explore::sGoalSort(std::vector<sGoal> &sGoals, const geometry_msgs::Pose currentPose){

  // assign cost to each semantic goal based on distance
  for(int i = 0; i < sGoals.size(); ++i){
    float dx = sGoals[i].sPoint.x - currentPose.position.x;
    float dy = sGoals[i].sPoint.y - currentPose.position.y;
    
    sGoals[i].distance = sqrt(pow(dx, 2) + pow(dy, 2));
  }
  
  // sort
  std::sort(sGoals.begin(), sGoals.end(), [](const sGoal& s1, const sGoal& s2) { return s1.distance < s2.distance; });
}

geometry_msgs::Pose Explore::setAngle(const geometry_msgs::Pose currentPose, const geometry_msgs::Point target){
  // x and y distances
  float dx = target.x - currentPose.position.x;
  float dy = target.y - currentPose.position.y;
  
  // angle between the object and the current pose, recall atan2(y, x)
  double theta = atan2(dy, dx);
  
  // new goal, no need to set position, all we want is the orientation which we will just pass into the goal
  geometry_msgs::Pose newGoal;     
  
  // orientation
  quat_.setRPY(0, 0, theta);
    
  newGoal.orientation.x = quat_.getX();
  newGoal.orientation.y = quat_.getY();
  newGoal.orientation.z = quat_.getZ();
  newGoal.orientation.w = quat_.getW();
  
  return newGoal;
}

void Explore::makePlan()
{
  // find frontiers
  auto pose = costmap_client_.getRobotPose();
  
  // get frontiers sorted according to cost
  auto frontiers = search_.searchFrom(pose.position);
  ROS_INFO("found %lu frontiers", frontiers.size());
  
  // get semantic goals sorted according to distance
  sGoalSort(sPeople_, pose);
  sGoalSort(sChairs_, pose);
  sGoalSort(sBalls_, pose);
  
  for (size_t i = 0; i < frontiers.size(); ++i) {
    // ROS_INFO("frontier %zd cost: %f", i, frontiers[i].cost);
  }

  if (frontiers.empty()) {
    stop();
    ROS_DEBUG("No new frontiers found");
    return;
  }

  // publish frontiers as visualization markers, should edit this as well to visualize objects
  if (visualize_) {
    visualizeFrontiers(frontiers);
  }

  // find non blacklisted frontier -> returns the first non blacklisted frontier, note the frontiers are already sorted by cost
  auto frontier =
      std::find_if_not(frontiers.begin(), frontiers.end(),
                       [this](const frontier_exploration::Frontier& f) {
                         return goalOnBlacklist(f.centroid, false);
                       });
                       
  if (frontier == frontiers.end()) {
    stop();
    ROS_INFO("No unvisited frontiers found");
    return;
  }
  
  // do the same for semantic goals
  std::vector<sGoal>::iterator bestS;
  
  // if on the first loop 
  if(!notFirst)
    lastSeqMove = ros::Time::now();
  
  // iterate over sequence if semantic goal
  if(notFirst && (ros::Time::now() - lastSeqMove > classPatience)){
    
    lastSeqMove = ros::Time::now();
    
    // save skipped class so we can return to it
    if(firstSkip){
    
      skippedClass = seqNum;
      
      skip = true;
      firstSkip = false;
    }
    
    if(seqNum == sequence_.size() - 1)
      seqNum = 0;
    else
      seqNum++;
  }
  
  notFirst = true;
  
  // return to skipped class if instance is found
  if(skip && newObj_[skippedClass] == true){  
  
    seqNum = skippedClass;
    
    skip = false;
    firstSkip = true;
  }
  
  isPerson = false;
  isChair = false;
  isBall = false;
  
  ROS_INFO_STREAM("Currently searching for a " << sequence_[seqNum]);
  
  if((sequence_[seqNum] == "person") && (sPeople_.size() > 0)){ 
    
    bestS = std::find_if_not(sPeople_.begin(), sPeople_.end(),
                            [this](const sGoal& s) {
                              return goalOnBlacklist(s.sPoint, true);
                            });
    if(bestS != sPeople_.end()){                        
      isPerson = true; 
      // ROS_INFO("isPerson"); 
    }    
  }
  else if((sequence_[seqNum] == "chair") && (sChairs_.size() > 0)){
    
    bestS = std::find_if_not(sChairs_.begin(), sChairs_.end(),
                            [this](const sGoal& s) {
                              return goalOnBlacklist(s.sPoint, true);
                            });
                            
    if(bestS != sChairs_.end()){
      isChair = true;
      // ROS_INFO("isChair");
    }
  }
  else if((sequence_[seqNum] == "ball") && (sBalls_.size() > 0)){ 

    bestS = std::find_if_not(sBalls_.begin(), sBalls_.end(),
                            [this](const sGoal& s) {
                              return goalOnBlacklist(s.sPoint, true);
                            });
                            
    if(bestS != sBalls_.end()){
      isBall = true;
      // ROS_INFO("isBall");
    }
  }

  isFrontier = true;
  geometry_msgs::Point target_position;
  
  // if semantic goal is present, prioritize it
  if(isPerson || isChair || isBall){
     
    // ROS_INFO("isNotFrontier"); 
    
    target_position = bestS->sPoint;
    isFrontier = false;
  }
  else{
    target_position = frontier->centroid;
    isFrontier = true;
  }

  // time out if we are not making any progress
  bool same_goal = prev_goal_ == target_position;
  prev_goal_ = target_position;
  
  if(isFrontier){
  
    if (!same_goal || prev_distance_ > frontier->min_distance) {
      // we have different goal or we made some progress
      last_progress_ = ros::Time::now();
      prev_distance_ = frontier->min_distance;
    }
  }
  
  // black list if we've made no progress for a long time
  if (isFrontier && (ros::Time::now() - last_progress_ > progress_timeout_)) {
    frontier_blacklist_.push_back(target_position);
    ROS_INFO("Adding current goal to black list due to lack of progress");
    
    makePlan();
    return;
  }

  // we don't need to do anything if we still pursuing the same goal
  if (same_goal) {
    ROS_INFO("Pursuing same goal");
    return;
  }

  // send goal to move_base if we have something new to pursue
  if(isFrontier)
    ROS_INFO("New goal is a frontier");
  else{
    ROS_INFO_STREAM("New goal is a semantic goal at " << target_position.x << ", " << target_position.y);
  }
    
  // find goal orientation (the angle of the robot's approach)
  geometry_msgs::Pose tempPose = setAngle(pose, target_position);
  
  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.pose.position = target_position;
  
  goal.target_pose.pose.orientation.x = tempPose.orientation.x;
  goal.target_pose.pose.orientation.y = tempPose.orientation.y;
  goal.target_pose.pose.orientation.z = tempPose.orientation.z;
  goal.target_pose.pose.orientation.w = tempPose.orientation.w;
  
  goal.target_pose.header.frame_id = costmap_client_.getGlobalFrameID();
  goal.target_pose.header.stamp = ros::Time::now();
  
  move_base_client_.sendGoal(
      goal, [this, target_position](
                const actionlib::SimpleClientGoalState& status,
                const move_base_msgs::MoveBaseResultConstPtr& result) {
        reachedGoal(status, result, target_position);
      });
}

bool Explore::goalOnBlacklist(const geometry_msgs::Point& goal, bool sFlag)
{
  // separate tolerances for frontiers and semantic goals, resolution is 0.02, so a tolerance of 5 = 4 inches, sTolerance was 15
  constexpr static size_t fTolerance = 5;
  constexpr static size_t sTolerance = 50;
    
  costmap_2d::Costmap2D* costmap2d = costmap_client_.getCostmap();

  // check if a goal is on the blacklist for goals that we're pursuing
  for (auto& frontier_goal : frontier_blacklist_) {
    double x_diff = fabs(goal.x - frontier_goal.x);
    double y_diff = fabs(goal.y - frontier_goal.y);
 
    if (sFlag && (x_diff < sTolerance * costmap2d->getResolution() && y_diff < sTolerance * costmap2d->getResolution()))
      return true;
    else if (!sFlag && (x_diff < fTolerance * costmap2d->getResolution() && y_diff < fTolerance * costmap2d->getResolution()))
      return true;
  }
  return false;
}

void Explore::reachedGoal(const actionlib::SimpleClientGoalState& status,
                          const move_base_msgs::MoveBaseResultConstPtr&,
                          const geometry_msgs::Point& frontier_goal)
{
  ROS_INFO("Reached goal with status: %s", status.toString().c_str());
  if (status == actionlib::SimpleClientGoalState::ABORTED || status == actionlib::SimpleClientGoalState::SUCCEEDED) {
    frontier_blacklist_.push_back(frontier_goal);
    ROS_INFO_STREAM("Adding goal " << frontier_goal.x << ", " << frontier_goal.y << " to black list");
  }
  
  // not frontier = semantic goal, iterate through sequence and reset flags
  if(!isFrontier){
  
    ROS_INFO_STREAM("Found a " << sequence_[seqNum]);
    lastSeqMove = ros::Time::now();
    
    if(seqNum == sequence_.size() - 1){
    
      seqNum = 0;
      ROS_INFO("End of sequence");
    }
    else{
    
      seqNum++;     
      ROS_INFO_STREAM("Advance one, sequence number is " << seqNum);
    }
    
    isPerson = false;
    isChair = false;
    isBall = false;
  } 

  // find new goal immediatelly regardless of planning frequency.
  // execute via timer to prevent dead lock in move_base_client (this is
  // callback for sendGoal, which is called in makePlan). the timer must live
  // until callback is executed.
  oneshot_ = relative_nh_.createTimer(
      ros::Duration(0, 0), [this](const ros::TimerEvent&) { makePlan(); },
      true);
}

void Explore::start()
{
  exploring_timer_.start();
}

void Explore::stop()
{
  move_base_client_.cancelAllGoals();
  exploring_timer_.stop();
  ROS_INFO("Exploration stopped.");
}

}  // namespace explore

int main(int argc, char** argv)
{
  ros::init(argc, argv, "explore");
  if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                     ros::console::levels::Debug)) {
    ros::console::notifyLoggerLevelsChanged();
  }
  explore::Explore explore;
  ros::spin();

  return 0;
}

