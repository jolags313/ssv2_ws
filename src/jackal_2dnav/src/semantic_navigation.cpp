#include <ros/ros.h>

#include <iostream>
#include <stdlib.h>

#include <math.h>
#include <vector>
#include <algorithm>

#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <octomap/ColorOcTree.h>

#include <octomap_msgs/Octomap.h>
#include <octomap_msgs/conversions.h>

#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Note- following https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/

// where does this go?
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

// global variable for use in main and callback, should probably change this in the future
move_base_msgs::MoveBaseGoal goal;

// make a class and have the callback as a method
class semanticExploration{

public:

  semanticExploration(){
    // Topic to publish (nothing here, just need to fill out the goal using subscribed info in semanticCallback)
    // pub_ = nh_.advertise<PUBLISHED_MESSAGE_TYPE>("/published_topic", queue size)
    
    ROS_INFO("Object created");
    
    // Topic to subscribe to (full octomap message from octomap_generator
    sub_ = nh_.subscribe("floatlazer/octomap_full", 1, &semanticExploration::semanticCallback, this);
  }
  
  // populate goal (geometry_msgs/PoseStamped)
  void semanticCallback(const octomap_msgs::Octomap& octomap_msg){
  
    ROS_INFO("Entering callback");
    
    // use Octomap iterator to find colors, first deserialize
    octomap::AbstractOcTree* tree = octomap_msgs::msgToMap(octomap_msg);
    ROS_INFO("Deserialized Octomap");
    
    // going from base to derived types (Abstract -> Color)
    octomap::ColorOcTree* octree = dynamic_cast<octomap::ColorOcTree*>(tree);
    ROS_INFO("Dynamic Casted");
    
    // declare vector of bounding boxes -> comment out since already declared as private below
    // std::vector<boundingBox> bbInstances;
    // ROS_INFO("BB vector declared");
    
    // iterator
    for(octomap::ColorOcTree::leaf_iterator it = octree->begin_leafs(), end = octree->end_leafs(); it!=end; ++it){
    
      // ROS_INFO("In iterator");
    
      // get color -> class octomap::ColorOcTreeNode::Color has three fields r, g, b (0 to 255)
      octomap::ColorOcTreeNode::Color currentColor = it->getColor();
      // ROS_INFO("Color extracted");
      
      // correct access of color class of ColorOcTreeNode?
      int semR = currentColor.r;
      int semG = currentColor.g;
      int semB = currentColor.b;
      // ROS_INFO_STREAM("R is " << semR << "    G is " << semG << "    B is " << semB << '\n');
      
      // values are for the color of a person
      if(semR == 64 && semG == 0 && semB == 128){
      
        // ROS_INFO("Person found");
          
        // check if the vector of bounding boxes is empty
        if(bbInstances.size() == 0){
        
          ROS_INFO("Empty BB");
              
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
          ROS_INFO("First BB");
          bbInstances.push_back(tempBB);
          
          // test, show center of very first node
          continue;
        }
        else{
        
          // ROS_INFO("Non-empty BB");
              
          // check to see if the current node is adjacent to/in an existing bounding box (just check x and y and if in limits)
          // (xMin - resolution/2 <= x <= XMax + resolution/2) and (yMin - resolution/2 <= y <= yMax + resolution/2)
              
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
              ROS_INFO_STREAM("Adjacent, current center at (" << bbInstances[i].xCenter << ", " << bbInstances[i].yCenter << ") with size " << (bbInstances[i].maxX - bbInstances[i].minX) << " by " << (bbInstances[i].maxY - bbInstances[i].minY)); 
              ROS_INFO_STREAM("^ New X at " << it.getX() << "    New Y at " << it.getY() << "    with size " << it.getSize() << '\n');  
              
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
              ROS_INFO("New bounding box");
              bbInstances.push_back(tempBB);
            }
          } 
        }
      }
    }
    
    ROS_INFO("Outside of iterator");
    ROS_INFO_STREAM("Vector size is " << bbInstances.size() << " before trimming" << '\n');
    
    // check to see which is the largest in area (placeholder metric, will be using a vector of these when used with explore_lite like with the frontiers -> weighted to choose the best one)
    float minArea = 0.1; // 0.1 m^2 = about 4 inches x 4 inches
    float bbArea = minArea;
    int idx = 0;
    
    int currentSize = bbInstances.size();
    int currentIdx = 0;
    int numErased = 0;
              
    for(int i = 0; i < currentSize; ++i){
    
      currentIdx = i - numErased;
      ROS_INFO_STREAM("Current index = " << currentIdx << '\n');
    
      ROS_INFO_STREAM("X size " << (bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) << "    Y size " << (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY) << '\n');
      ROS_INFO_STREAM("Bounding box area is " << (bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) * (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY) << '\n');
      
      if((bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) * (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY) < minArea){
        bbInstances.erase(bbInstances.begin() + currentIdx);
        numErased++;
        
        ROS_INFO_STREAM("Current vector size = " << bbInstances.size() << '\n');
      }
      else if(bbArea < (bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) * (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY)){
        
        bbArea = (bbInstances[currentIdx].maxX - bbInstances[currentIdx].minX) * (bbInstances[currentIdx].maxY - bbInstances[currentIdx].minY);
        idx = currentIdx;
        ROS_INFO_STREAM("Current vector size = " << bbInstances.size() << " and idx = " << idx << '\n');
      }
    }
      
    ROS_INFO_STREAM("Max area was " << bbArea << " = " << bbInstances[idx].maxX - bbInstances[idx].minX << " x " << bbInstances[idx].maxY - bbInstances[idx].minY << '\n');
    ROS_INFO_STREAM("Vector size is " << bbInstances.size() << " after trimming" << '\n');
    
    // unable to output this- is it a problem accessing the vector?
    ROS_INFO_STREAM("Idx is " << idx << "    X at " << bbInstances[idx].xCenter << "    Y at " << bbInstances[idx].yCenter << '\n');
    
    goal.target_pose.header.frame_id = "map"; //global frame
    goal.target_pose.header.stamp = ros::Time::now();
  
    goal.target_pose.pose.position.x = bbArea <= minArea ? 0 : bbInstances[idx].xCenter;
    goal.target_pose.pose.position.y = bbArea <= minArea ? 0 : bbInstances[idx].yCenter;
    goal.target_pose.pose.position.z = 0; // can we just leave this as 0?
    
    ROS_INFO_STREAM("X AT " << goal.target_pose.pose.position.x << "    Y AT " <<  goal.target_pose.pose.position.y << '\n');
  
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1.0;
    
    // do we need something to send the action goals? If we send the goal up here, ac is not in scope
  }
  
  // move_base_msgs::MoveBaseGoal goal;
  
private:
  ros::NodeHandle nh_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
  
  // are these necessary?
  struct boundingBox{
    float xCenter;
    float yCenter;
      
    float minX;
    float maxX;
      
    float minY;
    float maxY;
  };
    
  std::vector<boundingBox> bbInstances;
  
  // minimum distance the center of a voxel can be from the bounding box to be considered adjacent (m)
  float minDistance = 0.1; // about 3.93 inches
  
  // add one for visualization
  // void visualizeLocations(const std::vector< >)
  
  // check for adjacency
  bool checkAdjacency(double newX, double newY, const boundingBox currentBB){
  
    // first convert doubles newX and newY to floats so that we can use std::max
    // float floatX = static_cast<float>(newX);
    // float floatY = static_cast<float>(newY);
    
    float dx = std::max({currentBB.minX - newX, 0.0, newX - currentBB.maxX});
    float dy = std::max({currentBB.minY - newY, 0.0, newY - currentBB.maxY});
    
    if(sqrt(pow(dx, 2) + pow(dy, 2)) <= minDistance)
      return true;
    else 
      return false;      
  }
};

int main(int argc, char** argv){
  ros::init(argc, argv, "semantic_exploration"); //node name

  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  // think contents (including below object creation) should be inside loop but comment out for now for testing and until we find a way to blacklist visited goals
  
  // create an object of class semanticExploration that will take care of everything
  semanticExploration semanticExplorer;
  
  ros::Rate r(0.1); // every 10 seconds
  
  while(ros::ok()){
    
    ROS_INFO("Before callback call");
    ros::getGlobalCallbackQueue()->callOne();
    ROS_INFO("After callback call");
    ros::getGlobalCallbackQueue()->clear();
    ROS_INFO("After callback clear");
    
    // send goal of the location input using callback -> how can we get the goal from inside? -> just make it a global variable for now
    ROS_INFO("Sending goal");
    ROS_INFO_STREAM("X AT " << goal.target_pose.pose.position.x << "    Y AT " <<  goal.target_pose.pose.position.y << '\n');
    ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Object reached");
    else
      ROS_INFO("Exploration failed");
      
    // try here
    // ros::spinOnce();
      
    r.sleep();
  }
    
    // ROS_INFO_STREAM("X AT " << goal.target_pose.pose.position.x << "    Y AT " <<  goal.target_pose.pose.position.y << '\n');
    
    // note that we wouldn't be able to call the above anyway since goal is out of scope    
    // rate.sleep();

  return 0;
}
