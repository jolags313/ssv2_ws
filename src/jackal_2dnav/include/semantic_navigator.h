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

#include "jackal_2dnav/sInstance.h"
#include "jackal_2dnav/sPoses.h"

#include "jackal_2dnav/grassLimits.h"
#include "jackal_2dnav/grasslands.h"

#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>

// Note- following https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/

// make a class and have the callback as a method
class semanticExplore{

public:

  semanticExplore();
  
  // populate goal (geometry_msgs/PoseStamped)
  void semanticCallback(const octomap_msgs::Octomap& octomap_msg);
  
private:

  ros::NodeHandle nh_;
  ros::Subscriber sub_;
  ros::Publisher objPub_;
  ros::Publisher grassPub_;
  
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
  
  // instance to use as goal, made up of a pose and label
  jackal_2dnav::sInstance msgInstance;
  
  // vector of ^ to publish over objPub_
  jackal_2dnav::sPoses msgPoses;
  
  // grass limits, made up of four floats
  jackal_2dnav::grassLimits grassBox;
  
  // vector of ^ to publish over grassPub_
  jackal_2dnav::grasslands grassland;
  
  // minimum distance the center of a voxel can be from the bounding box to be considered adjacent (m), 0.1 m is about 3.93 inches
  float minDistance;
  
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

