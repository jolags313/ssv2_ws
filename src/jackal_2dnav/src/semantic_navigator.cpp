// should just need this explore.h from explore_lite
#include <semantic_navigator.h>

// Note- following https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/

semanticExplore::semanticExplore(){

  // ROS_INFO("Object created");
  
  // Topic to publish (vector of inflated goal poses to pass to explore_lite)
  pub_ = nh_.advertise<jackal_2dnav::sPoses>("/semantic_goals", 1);
  
  // Topic to subscribe to (full octomap message from octomap_generator)
  sub_ = nh_.subscribe("floatlazer/octomap_full", 1, &semanticExplore::semanticCallback, this);
  
}

// populate goal (geometry_msgs/PoseStamped)
void semanticExplore::semanticCallback(const octomap_msgs::Octomap& octomap_msg){

  // ROS_INFO("Entering callback");
  
  // use Octomap iterator to find colors, first deserialize
  octomap::AbstractOcTree* tree = octomap_msgs::msgToMap(octomap_msg);
  // ROS_INFO("Deserialized Octomap");
  
  // going from base to derived types (Abstract -> Color)
  octomap::ColorOcTree* octree = dynamic_cast<octomap::ColorOcTree*>(tree);
  // ROS_INFO("Dynamic Casted");
  
  /*
  // declare vector of bounding boxes -> comment out since already declared as private below
  std::vector<boundingBox> bbInstances;
  ROS_INFO("BB vector declared");
  */
  
  // get current robot pose
  geometry_msgs::Pose robotPose = getCurrentPose();
  float robotX = robotPose.position.x;
  float robotY = robotPose.position.y; 
  
  // iterator
  for(octomap::ColorOcTree::leaf_iterator it = octree->begin_leafs(), end = octree->end_leafs(); it!=end; ++it){
  
    // ROS_INFO("In iterator");
  
    // get color -> class octomap::ColorOcTreeNode::Color has three fields r, g, b (0 to 255)
    octomap::ColorOcTreeNode::Color currentColor = it->getColor();
    
    // ROS_INFO("Color extracted");
    // ROS_INFO_STREAM("R is " << currentColor.r << "    G is " << currentColor.g << "    B is " << currentColor.b << '\n');
    
    // values are for the color of a person, add a z requirement to avoid counting shadows as goals
    if((currentColor.r == 64 && currentColor.g == 0 && currentColor.b == 128) && (it.getZ() > 0.3 && it.getZ() < 1.5)){
    
      // ROS_INFO("Person found");
        
      // check if the vector of bounding boxes is empty
      if(bbInstances.size() == 0){
      
        // ROS_INFO("Empty BB");
            
        // populate struct fields with center, max/min x/y, no need to check z (everything is projected onto a 2D map), all units in m
        boundingBox tempBB = {
        
          // why do we use it.getX() instead of it->getX()?
          it.getX(), // center x
          it.getY(), // center y
                
          // minimum x, set bounds using it.getSize() and not it.getSize() / 2 for padding when checking for adjacency      
          it.getX() - it.getSize(), 
          it.getX() + it.getSize(), // maximum x
                
          it.getY() - it.getSize(), // minimum y
          it.getY() + it.getSize(), // maximum y  
        };
            
        // add to vector
        // ROS_INFO("First BB");
        bbInstances.push_back(tempBB);
        
        // test, show center of very first node
        continue;
      }
      else{
      
        // ROS_INFO("Non-empty BB");
            
        // iterate through bounding boxes -> DO NOT USE AN ITERATOR (https://stackoverflow.com/questions/37900109/adding-an-element-to-a-vector-while-iterating-over-it)
        int currentSize = bbInstances.size();          
        for(int i = 0; i < currentSize; ++i){
          
          //ROS_INFO("In BB iterator");
          
          if(checkAdjacency(it.getX(), it.getY(), bbInstances[i])){
                                   
            // update center and bounds of bounding box, is there a way to check which side without multiple ifs?
            bbInstances[i].minX = (bbInstances[i].minX >= it.getX() - it.getSize() / 2) ? it.getX() - it.getSize() / 2 : bbInstances[i].minX;
            bbInstances[i].maxX = (it.getX() + it.getSize() / 2 >= bbInstances[i].maxX) ? it.getX() + it.getSize() / 2 : bbInstances[i].maxX;
                   
            bbInstances[i].minY = (bbInstances[i].minY >= it.getY() - it.getSize() / 2) ? it.getY() - it.getSize() / 2 : bbInstances[i].minY;
            bbInstances[i].maxY = (it.getY() + it.getSize() / 2 >= bbInstances[i].maxY) ? it.getY() + it.getSize() / 2 : bbInstances[i].maxY;
                   
            bbInstances[i].xCenter = bbInstances[i].minX + (bbInstances[i].maxX - bbInstances[i].minX) / 2;
            bbInstances[i].yCenter = bbInstances[i].minY + (bbInstances[i].maxY - bbInstances[i].minY) / 2;
            
            // ROS_INFO("Existing bounding box"); 
            // ROS_INFO_STREAM("Adjacent, current center at (" << bbInstances[i].xCenter << ", " << bbInstances[i].yCenter << ") with size " << (bbInstances[i].maxX - bbInstances[i].minX) << " by " << (bbInstances[i].maxY - bbInstances[i].minY)); 
            // ROS_INFO_STREAM("^ New X at " << it.getX() << "    New Y at " << it.getY() << "    with size " << it.getSize() << '\n');  
            
            break;                
          }
          // if we get through the entire vector without a match, add a new bounding box
          else if(i == currentSize - 1){
          
            // if not adjacent, add new bounding box
            boundingBox tempBB = {
              it.getX(), // center x
              it.getY(), // center y
                
              it.getX() - it.getSize() / 2, // minimum x
              it.getX() + it.getSize() / 2, // maximum x
                
              it.getY() - it.getSize() / 2, // minimum y
              it.getY() + it.getSize() / 2, // maximum y  
            };
            
            // add to vector
            // ROS_INFO("New bounding box");
            bbInstances.push_back(tempBB);
          }
        } 
      }
    }
  }
  
  // ROS_INFO("Outside of iterator");
  // ROS_INFO_STREAM("Vector size is " << bbInstances.size() << " before trimming" << '\n');
  
  // check to see which is the largest in area (placeholder metric, will be using a vector of these when used with explore_lite like with the frontiers -> weighted to choose the best one)
  float minArea = 0.1; // 0.1 m^2 = about 4 inches x 4 inches
  float bbArea = minArea;
  int idx = 0;
  
  int currentSize = bbInstances.size();
  int currentIdx = 0;
  int numErased = 0;
  
  int msgLength = 0;
     
  // make sure we have bounding box(es)
  if(currentSize > 0){   
         
    for(int i = 0; i < currentSize; ++i){
    
      currentIdx = i - numErased;
      // ROS_INFO_STREAM("Current index = " << currentIdx << '\n');
      
      float currentArea = (bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) * (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY);
    
      // ROS_INFO_STREAM("X size " << (bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) << "    Y size " << (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY) << '\n');
      // ROS_INFO_STREAM("Bounding box area is " << currentArea << '\n');
      
      if(currentArea < minArea){
        bbInstances.erase(bbInstances.begin() + currentIdx);
        numErased++;
        
        // ROS_INFO_STREAM("Current vector size = " << bbInstances.size() << '\n');
      }
      else if(currentArea > bbArea){    
        bbArea = currentArea;
        idx = currentIdx;
        // ROS_INFO_STREAM("Current vector size = " << bbInstances.size() << " and idx = " << idx << '\n');
        
        // make newGoal and push into newGoals
        geometry_msgs::Pose newGoal = inflateGoal(robotX, robotY, bbInstances[currentIdx]);
        myGoal = newGoal;
        
        // ROS_INFO_STREAM("New message with area " << currentArea << " with x at " << newGoal.position.x << " and y at " << newGoal.position.y);
        
        // newGoals.push_back(newGoal);
        msgPoses.poses.push_back(newGoal);      
        msgLength++;
      }
      else{  
        geometry_msgs::Pose newGoal = inflateGoal(robotX, robotY, bbInstances[currentIdx]);
        
        // ROS_INFO_STREAM("New message with area " << currentArea << " with x at " << newGoal.position.x << " and y at " << newGoal.position.y);
        
        msgPoses.poses.push_back(newGoal);      
        msgLength++;    
      }
    }
  }
    
  // ROS_INFO_STREAM("Vector size is " << bbInstances.size() << " after trimming, message array length is " << msgLength);
  
  // ROS_INFO_STREAM("Max area was " << bbArea << " = " << bbInstances[idx].maxX - bbInstances[idx].minX << " x " << bbInstances[idx].maxY - bbInstances[idx].minY);
  
  // ROS_INFO_STREAM("Idx is " << idx << "    X at " << myGoal.position.x << "    Y at " << myGoal.position.y << '\n');
  
  // ROS_INFO_STREAM("When adjusted, X at " << newGoals[idx].position.x << "    Y at " << newGoals[idx].position.y << '\n');
  
  /*
  sGoal.target_pose.header.frame_id = "map"; //global frame
  sGoal.target_pose.header.stamp = ros::Time::now();

  sGoal.target_pose.pose.position.x = bbArea <= minArea ? 0 : myGoal.position.x;
  sGoal.target_pose.pose.position.y = bbArea <= minArea ? 0 : myGoal.position.y;
  sGoal.target_pose.pose.position.z = 0; // can we just leave this as 0?
  
  ROS_INFO_STREAM("X AT " << sGoal.target_pose.pose.position.x << "    Y AT " <<  sGoal.target_pose.pose.position.y);

  sGoal.target_pose.pose.orientation.x = bbArea <= minArea ? 0 : myGoal.orientation.x;
  sGoal.target_pose.pose.orientation.y = bbArea <= minArea ? 0 : myGoal.orientation.y;
  sGoal.target_pose.pose.orientation.z = bbArea <= minArea ? 0 : myGoal.orientation.z;
  sGoal.target_pose.pose.orientation.w = 1.0;
  */
  
  // publish goals
  pub_.publish(msgPoses);
  
  // clear vectors
  bbInstances.clear();
  // newGoals.clear();
  msgPoses.poses.clear();
}

geometry_msgs::Pose semanticExplore::getCurrentPose(){
 
  tf::Stamped<tf::Pose> globalPose; 
  globalPose.setIdentity();
  
  tf::Stamped<tf::Pose> currentPose;
  currentPose.setIdentity();
  
  currentPose.frame_id_ = "base_link";
  currentPose.stamp_ = ros::Time();
  ros::Time currentTime = ros::Time::now();
  
  // get the global pose of the robot
  try{
    tf_->transformPose("map", currentPose, globalPose);
  } catch (tf::LookupException& ex){
    ROS_ERROR_THROTTLE(1.0, "No Transform available Error looking up robot pose: %s\n", ex.what());
    return {};
    
  } catch (tf::ConnectivityException& ex){
    ROS_ERROR_THROTTLE(1.0, "Connectivity Error looking up robot pose: %s\n", ex.what());
    return {};
    
  } catch (tf::ExtrapolationException& ex){
    ROS_ERROR_THROTTLE(1.0, "Extrapolation Error looking up robot pose: %s\n", ex.what());
    return {};
  }
  
  // check globalPose timeout
  if (currentTime.toSec() - globalPose.stamp_.toSec() > 0.3){
    ROS_WARN_THROTTLE(1.0, "Costmap2DClient transform timeout. Current time: %.4f, globalPose stamp: %.4f, tolerance: %.4f",
                      currentTime.toSec(), globalPose.stamp_.toSec(),
                      0.3);
    return {};
  }

  geometry_msgs::PoseStamped msg;
  
  tf::poseStampedTFToMsg(globalPose, msg);
  
  return msg.pose;
}

bool semanticExplore::checkAdjacency(double newX, 
                                     double newY, 
                                     const boundingBox currentBB){
  
  float dx = std::max({currentBB.minX - newX, 0.0, newX - currentBB.maxX});
  float dy = std::max({currentBB.minY - newY, 0.0, newY - currentBB.maxY});
  
  if(sqrt(pow(dx, 2) + pow(dy, 2)) <= minDistance)
    return true;
  else 
    return false;      
}

geometry_msgs::Pose semanticExplore::inflateGoal(float robotX,
                                                 float robotY,
                                                 const boundingBox currentBB){
  // x and y distances
  float dx = currentBB.xCenter - robotX;
  float dy = currentBB.yCenter - robotY;
  
  // angle between the object and the current pose, recall atan2(y, x)
  double theta = atan2(dy, dx);
  
  // radius of bounding box (distance from center to a corner), add an additional couple of inches to account for inflation layer
  float radius = sqrt(pow((currentBB.maxX - currentBB.minX) / 2, 2) + pow((currentBB.maxY - currentBB.minY) / 2, 2)) + 0.5;
  
  // new goal
  geometry_msgs::Pose newGoal;
  
  newGoal.position.x = currentBB.xCenter - radius * cos(theta);
  newGoal.position.y = currentBB.yCenter - radius * sin(theta);      
  newGoal.position.z = 0;      
  
  // orientation
  quat_.setRPY(0, 0, theta);
    
  newGoal.orientation.x = quat_.getX();
  newGoal.orientation.y = quat_.getY();
  newGoal.orientation.z = quat_.getZ();
  newGoal.orientation.w = quat_.getW();
  
  return newGoal;                                       
}

int main(int argc, char** argv){
  ros::init(argc, argv, "semantic_explorer"); //node name

  /*
  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  */
  
  // create an object of class semanticExplore that will take care of everything
  semanticExplore semanticExplorer;
  
  ros::Rate r(0.5); // every 2 seconds
  
  while(ros::ok()){
    
    // ROS_INFO("Before callback call");
    // ros::getGlobalCallbackQueue()->callOne();
    // ROS_INFO("After callback call");
    // ros::getGlobalCallbackQueue()->clear();
    // ROS_INFO("After callback clear");
    
    /*
    // send goal of the location input using callback -> how can we get the goal from inside? -> just make it a global variable for now
    ROS_INFO("Sending goal");
    ROS_INFO_STREAM("X AT " << sGoal.target_pose.pose.position.x << "    Y AT " <<  sGoal.target_pose.pose.position.y << '\n');
    ac.sendGoal(sGoal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Object reached");
      
      // reset goal
      sGoal.target_pose.pose.position.x = 0;
      sGoal.target_pose.pose.position.y = 0;
      sGoal.target_pose.pose.position.z = 0;

      sGoal.target_pose.pose.orientation.x = 0;
      sGoal.target_pose.pose.orientation.y = 0;
      sGoal.target_pose.pose.orientation.z = 0;
      sGoal.target_pose.pose.orientation.w = 1.0;
    }
    else{
      ROS_INFO("Exploration failed");
      ac.cancelGoal();
    }
    */
      
    // try here
    
    ros::spinOnce();
    // ROS_INFO("After");
    
    r.sleep();
  }

  return 0;
}