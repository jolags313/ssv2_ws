#include <ros/ros.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Point.h>

// where does this go?
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

// make a class and have the callback as a method + add goal as a member state so that it can be filled in the callback
class semanticExploration{
  move_base_msgs::MoveBaseGoal goal;
  
private:
  void semanticCallback(const geometry_msgs::Point& semanticPoint);
  
  // add one for visualization
  // void visualizeLocations(const std::vector<

}

// populate goal (geometry_msgs/PoseStamped)
void semanticCallback(const geometry_msgs::Point& semanticPoint){
  goal.target_pose.header.frame_id = "map"; //global frame
  goal.target_pose.header.stamp = ros::Time::now();
  
  goal.target_pose.pose.position.x = semanticPoint.x;
  goal.target_pose.pose.position.y = semanticPoint.y;
  goal.target_pose.pose.position.z = semanticPoint.z;
  
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = 0.0;
  goal.target_pose.pose.orientation.w = 1.0;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals"); //node name

  // tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  ros::NodeHandle nh;
  
  // create a subscriber to pass in the object locations taken from the Octomap
  // message queue size = 100?
  // add callback to populate goal with the object's location (x, y, z) -> /semantic poses should stream point messages
  ros::Subscriber sub = nh.subscribe("/semantic_poses", 100, semanticCallback);

  // send goal of the location input using callback
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

  return 0;
}
