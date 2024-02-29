#include <ros/ros.h>

#include <vector>

#include <octomap/octomap.h>
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

// make a class and have the callback as a method + add goal as a member state so that it can be filled in the callback
class semanticExploration{

public:

  semanticExploration(){
    // Topic to publish (nothing here, just need to fill out the goal using subscribed info in semanticCallback)
    // pub_ = nh_.advertise<PUBLISHED_MESSAGE_TYPE>("/published_topic", queue size)
    
    // Topic to subscribe to (full octomap message from octomap_generator
    sub_ = nh_.subscribe("/octomap_full", 10, &semanticExploration::semanticCallback, this);
  }
  
  // populate goal (geometry_msgs/PoseStamped)
  void semanticCallback(const octomap_msgs::Octomap& octomap_msg){
  
    // use Octomap iterator to find colors, first deserialize
    octomap::AbstractOcTree* tree = octomap_msgs::msgToMap(octomap_msg);
    
    // why doesn't this work? we're going from base to derived types (Abstract -> Color)
    octomap::OcTree* octree = dynamic_cast<octomap::ColorOcTree*>(tree);
    
    // declare vector of bounding boxes
    std::vector<boundingBox> bbInstances;
    
    // iterator
    for(octomap::OcTree::leaf_iterator it = octree->begin_leafs(), end = octree->end_leafs(); it!=end; ++it){
      // get color -> class octomap::ColorOcTreeNode::Color has three fields r, g, b (0 to 255), does this even work? getColor isn't listed in the leaf iterator documentation
      octomap::ColorOcTreeNode::Color currentColor = it->getColor();
      
      // correct access of color class of ColorOcTreeNode?
      int semR = currentColor.r;
      int semG = currentColor.b;
      int semB = currentColor.g;
      
      // maybe do this octomap::ColorOcTreeNode* node = octomap_.search(pcl_cloud->begin()->x, pcl_cloud->begin()->y, pcl_cloud->begin()->z);
      
      // values are for a person
      if(semR == 64 && semG == 0 && semB == 128){
          
        // check if the vector of bounding boxes is empty
        if(bbInstances.size() == 0){
              
          // populate struct fields with center, max/min x/y, no need to check z (everything is projected onto a 2D map), all units in m
          boundingBox tempBB = {
          
            // why do we use it.getX() instead of it->getX()?
            it.getX(), // center x
            it.getY(), // center y
                  
            it.getX() - octomap_msg.resolution / 2, // minimum x
            it.getX() + octomap_msg.resolution / 2, // maximum x
                  
            it.getY() - octomap_msg.resolution / 2, // minimum y
            it.getY() + octomap_msg.resolution / 2, // maximum y  
          };
              
          // add to vector
          bbInstances.push_back(tempBB);
        }
        else{
              
          // check to see if the current node is adjacent to/in an existing bounding box (just check x and y and if in limits)
          // (xMin - resolution/2 <= x <= XMax + resolution/2) and (yMin - resolution/2 <= y <= yMax + resolution/2)
              
          // iterate through bounding boxes
          for(std::vector<boundingBox>::iterator bbIt = bbInstances.begin(); bbIt != bbInstances.end(); bbIt++){
                  
            // check for adjacency/limits
            if(bbIt->minX - octomap_msg.resolution/2 <= it.getX() && 
              it.getX() <= bbIt->maxX + octomap_msg.resolution/2 &&
                      
              bbIt->minY - octomap_msg.resolution/2 <= it.getY() && 
              it.getY() <= bbIt->maxY + octomap_msg.resolution/2 ){
                          
              // update center and bounds of bounding box, is there a way to check which side without multiple ifs?
              bbIt->minX = (bbIt->minX - octomap_msg.resolution/2 == it.getX()) ? it.getX() - octomap_msg.resolution/2 : bbIt->minX;
              bbIt->maxX = (it.getX() == bbIt->maxX + octomap_msg.resolution/2) ? it.getX() + octomap_msg.resolution/2 : bbIt->maxX;
                     
              bbIt->minY = (bbIt->minY - octomap_msg.resolution/2 == it.getY()) ? it.getY() - octomap_msg.resolution/2 : bbIt->minY;
              bbIt->maxY = (it.getY() == bbIt->maxY + octomap_msg.resolution/2) ? it.getY() + octomap_msg.resolution/2 : bbIt->maxY;
                     
              bbIt->xCenter = bbIt->minX + (bbIt->maxX - bbIt->minX) / 2;
              bbIt->yCenter = bbIt->minY + (bbIt->maxY - bbIt->minY) / 2;
                          
            }
            else{
              // if not adjacent, add new bounding box
              boundingBox tempBB = {
                it.getX(), // center x
                it.getY(), // center y
                  
                it.getX() - octomap_msg.resolution / 2, // minimum x
                it.getX() + octomap_msg.resolution / 2, // maximum x
                  
                it.getY() - octomap_msg.resolution / 2, // minimum y
                it.getY() + octomap_msg.resolution / 2, // maximum y  
              };
              
              // add to vector
              bbInstances.push_back(tempBB);
            }
          }
        }
      }
    }
    
    // check to see which is the largest in area (placeholder metric, will be using a vector of these when used with explore_lite like with the frontiers -> weighted to choose the best one)
    float bbArea = 0;
    int idx = 0;
    
    for(std::vector<boundingBox>::iterator bbIt = bbInstances.begin(); bbIt != bbInstances.end(); bbIt++){
      
      if(bbArea < (bbIt->maxX - bbIt->minX) * (bbIt->maxY - bbIt->minY)){
        
        bbArea = (bbIt->maxX - bbIt->minX) * (bbIt->maxY - bbIt->minY);
        idx = std::distance(bbInstances.begin(), bbIt);
      }         
    }
    
    goal.target_pose.header.frame_id = "map"; //global frame
    goal.target_pose.header.stamp = ros::Time::now();
  
    goal.target_pose.pose.position.x = bbInstances[idx].xCenter;
    goal.target_pose.pose.position.y = bbInstances[idx].yCenter;
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
    double xCenter;
    double yCenter;
      
    double minX;
    double maxX;
      
    double minY;
    double maxY;
  };
    
    std::vector<boundingBox> bbInstances;
  
  // add one for visualization
  // void visualizeLocations(const std::vector<
};

int main(int argc, char** argv){
  ros::init(argc, argv, "semantic_exploration"); //node name

  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  // set frequency to 0.1 Hz
  // ros::Rate rate(0.1);
  
  // think contents should be inside loop but comment out for now for testing and until we find a way to blacklist visited goals
  
  // while(ros::ok()){
    // create an object of class semanticExploration that will take care of everything
    semanticExploration semanticExplorer;
    // ROS_INFO_STREAM("X AT " << goal.target_pose.pose.position.x << "    Y AT " <<  goal.target_pose.pose.position.y << '\n');
    
    // note that we wouldn't be able to call the above anyway since goal is out of scope
    
    // rate.sleep();
    
    // send goal of the location input using callback -> how can we get the goal from inside? -> just make it a global variable for now
    // ROS_INFO("Sending goal");
    // ac.sendGoal(goal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      ROS_INFO("Object reached");
    else
      ROS_INFO("Exploration failed");
  // }

  return 0;
}
