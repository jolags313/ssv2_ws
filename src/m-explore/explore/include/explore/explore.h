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
#ifndef NAV_EXPLORE_H_
#define NAV_EXPLORE_H_

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>

#include <explore/costmap_client.h>
#include <explore/frontier_search.h>

#include <jackal_2dnav/sInstance.h>
#include <jackal_2dnav/sPoses.h>

namespace explore
{
/**
 * @class Explore
 * @brief A class adhering to the robot_actions::Action interface that moves the
 * robot base to explore its environment.
 */
class Explore
{
public:
  Explore();
  ~Explore();

  void start();
  void stop();

private:
  
  // struct with minimum distances included as a member to sort semantic goals
  struct sGoal{
    geometry_msgs::Point sPoint;
    float distance;
    
    std::string label;
  };
  
  // semantic objects, populate with points from semantic_navigator
  // std::vector<sGoal> sGoals_;
  
  // object queues, use people, chairs, and balls + flags for each
  std::vector<sGoal> sPeople_;
  std::vector<sGoal> sChairs_;
  std::vector<sGoal> sBalls_;
  
  bool isPerson = false;
  bool isChair = false;
  bool isBall = false;
  
  // sequence to follow and a counter
  std::vector<std::string> sequence_ = {"person", "chair", "ball"};
  int seqNum = 0;
  
  // flag for first run, just used for skip stuff
  bool notFirst = false;
  
  // time since last move in sequence + patience for each class search
  ros::Time lastSeqMove;
  ros::Duration classPatience = ros::Duration(100.0);
  
  // placeholder for skipped class + bool firstSkip so make sure we only save the earliest skip
  int skippedClass;
  bool skip = false;
  bool firstSkip = true;
  
  // number of instances found of each class, use to check if a new one has been found for the skipped class, same order as sequence + T/F if a new one has been found
  std::vector<int> numObj_ = {0, 0, 0};
  std::vector<bool> newObj_ = {false, false, false};
  
  // here from cpp
  bool isFrontier = false;
  
  tf2::Quaternion quat_;
  
  /**
   * @brief  Make a global plan
   */
  void makePlan();
  
  // populate sGoals_ with the points from semantic_navigator
  void sPoseCallback(const jackal_2dnav::sPoses& sPose_msg);
  
  // set semantic goal cost, sort just by cost just like is done in FrontierSearch::searchFrom,  pass in sPoints_ by reference (to sort it) and the robot pose
  void sGoalSort(std::vector<sGoal> &sGoals, const geometry_msgs::Pose currentPose);
  
  // set goal orientation
  geometry_msgs::Pose setAngle(const geometry_msgs::Pose currentPose, const geometry_msgs::Point target);

  /**
   * @brief  Publish a frontiers as markers
   */
  void visualizeFrontiers(
      const std::vector<frontier_exploration::Frontier>& frontiers);
      
  // void visualizeBoundingBoxes()?

  void reachedGoal(const actionlib::SimpleClientGoalState& status,
                   const move_base_msgs::MoveBaseResultConstPtr& result,
                   const geometry_msgs::Point& frontier_goal);

  bool goalOnBlacklist(const geometry_msgs::Point& goal, bool sFlag);
  
  ros::NodeHandle private_nh_;
  ros::NodeHandle relative_nh_;
  ros::Publisher marker_array_publisher_;
  tf::TransformListener tf_listener_;
  
  // subscribes to /semantic_goals
  ros::Subscriber sub_;

  Costmap2DClient costmap_client_;
  actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
      move_base_client_;
  frontier_exploration::FrontierSearch search_;
  ros::Timer exploring_timer_;
  ros::Timer oneshot_;

  std::vector<geometry_msgs::Point> frontier_blacklist_;
  geometry_msgs::Point prev_goal_;
  double prev_distance_;
  ros::Time last_progress_;
  size_t last_markers_count_;

  // parameters
  double planner_frequency_;
  double potential_scale_, orientation_scale_, gain_scale_;
  ros::Duration progress_timeout_;
  bool visualize_;
};
}

#endif
