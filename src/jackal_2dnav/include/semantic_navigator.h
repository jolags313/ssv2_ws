#include <ros/ros.h>

#include <iostream>
#include <stdlib.h>

#include <math.h>
#include <vector>
#include <string>
#include <algorithm>

#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap/ColorOcTree.h>

#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

#include <geometry_msgs/Pose.h>
#include "jackal_2dnav/sPoses.h"
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>

// #include <move_base_msgs/MoveBaseAction.h>
// #include <actionlib/client/simple_action_client.h>

// Note- following https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/

// typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

// global variable for use in main and callback, should probably change this in the future
// move_base_msgs::MoveBaseGoal sGoal;

// make a class and have the callback as a method
class semanticExplore{

public:

  semanticExplore();
  
  // populate goal (geometry_msgs/PoseStamped)
  void semanticCallback(const octomap_msgs::Octomap& octomap_msg);
  
private:

  ros::NodeHandle nh_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
  
  tf::TransformListener tf_listener_;
  const tf::TransformListener* const tf_ = &tf_listener_;
  
  tf2::Quaternion quat_;
  
  struct boundingBox{
    float xCenter;
    float yCenter;
      
    float minX;
    float maxX;
      
    float minY;
    float maxY;
    
    std::string label;
  };
    
  // bounding boxes  
  std::vector<boundingBox> bbInstances;
  
  // instance to use as goal
  jackal_2dnav::sInstance msgInstance;
  
  // message to publish
  jackal_2dnav::sPoses msgPoses;
  
  // minimum distance the center of a voxel can be from the bounding box to be considered adjacent (m)
  float minDistance = 0.2; // 0.1 m is about 3.93 inches
  
  // check for adjacency
  bool checkAdjacency(double newX, 
                      double newY, 
                      const boundingBox currentBB);
                      
  // pull current robot pose
  geometry_msgs::Pose getCurrentPose();

  // inflate goal, output geometry_msg::Point to be pushed to explore
  geometry_msgs::Pose inflateGoal(float robotX,
                                  float robotY,
                                  const boundingBox currentBB);
};

