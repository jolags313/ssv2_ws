#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>

// Note- following https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/

// where does this go?
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

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
    AbstractOcTree* tree = octomap_msgs::msgToMap(octomap_msg);
    
    // what does this do? makes tree of type OcTree and not AbstractOcTree?
    OcTree octree* = dynamic_cast<OcTree*>(tree);
    
    // iterator
    for(OcTree::leaf_iterator it = octree.begin_leafs(), end = octree.end_leafs(); it!=end; ++it){
      // get color -> class octomap::ColorOcTreeNode::Color has three fields r, g, b (0 to 255), does this even work? getColor isn't listed in the leaf iterator documentation
      octomap::ColorOcTreeNode::Color currentColor = it->getColor();
      
      // correct access of color class of ColorOcTreeNode?
      int semR = currentColor.r;
      int semG = currentColor.b;
      int semB = currentColor.g;
      
      // maybe do this octomap::ColorOcTreeNode* node = octomap_.search(pcl_cloud->begin()->x, pcl_cloud->begin()->y, pcl_cloud->begin()->z);
      
      if(semR == )
         
      // get xy center + recall that octomap_msg.resolution has the resolution of the smallest nodes in m
      float xCenter = it->getX();
      float yCenter = it->getY();
      
      // check for adjacency
    }
    
    goal.target_pose.header.frame_id = "map"; //global frame
    goal.target_pose.header.stamp = ros::Time::now();
  
    goal.target_pose.pose.position.x = semanticPoint.x;
    goal.target_pose.pose.position.y = semanticPoint.y;
    goal.target_pose.pose.position.z = semanticPoint.z;
  
    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1.0;
    
    // do we need something to send the action goals? 
  }
  
  move_base_msgs::MoveBaseGoal goal;
  
private:
  ros::NodeHandle nh_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
  
  // add one for visualization
  // void visualizeLocations(const std::vector<

}



int main(int argc, char** argv){
  ros::init(argc, argv, "semantic_exploration"); //node name

  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  // create an object of class semanticExploration that will take care of everything
  semanticExploration semanticExplorer;
  
  /*
  // create a subscriber to pass in the object locations taken from the Octomap
  // message queue size = 100?
  // add callback to populate goal with the object's location (x, y, z) -> /semantic poses should stream point messages
  ros::Subscriber sub = nh.subscribe("/semantic_poses", 100, semanticCallback);
  */

  // send goal of the location input using callback
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Object reached");
  else
    ROS_INFO("Exploration failed");

  return 0;
}
