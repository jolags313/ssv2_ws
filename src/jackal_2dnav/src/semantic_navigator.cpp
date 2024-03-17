
#include <semantic_navigator.h>

// Note- following https://answers.ros.org/question/59725/publishing-to-a-topic-via-subscriber-callback-function/

semanticExplore::semanticExplore(){

  // ROS_INFO("Object created");
  
  // Topic to publish (vector of inflated goal poses to pass to explore_lite)
  objPub_ = nh_.advertise<jackal_2dnav::sPoses>("/semantic_goals", 1);
  
  // Topic to publish (vector of lists of four floats (grass bounding box limits))
  grassPub_ = nh_.advertise<jackal_2dnav::grasslands>("/grassland", 1);
  
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
  
  // get current robot pose
  geometry_msgs::Pose robotPose = getCurrentPose();
  float robotX = robotPose.position.x;
  float robotY = robotPose.position.y; 
  
  // string for label
  std::string label;
  
  // iterator
  for(octomap::ColorOcTree::leaf_iterator it = octree->begin_leafs(), end = octree->end_leafs(); it!=end; ++it){
  
    // ROS_INFO("In iterator");
  
    // get color -> class octomap::ColorOcTreeNode::Color has three fields r, g, b (0 to 255)
    octomap::ColorOcTreeNode::Color currentColor = it->getColor();
    
    // ROS_INFO("Color extracted");
    // ROS_INFO_STREAM("R is " << currentColor.r << "    G is " << currentColor.g << "    B is " << currentColor.b << '\n');
    
    bool isObject = false;
    bool isGrass = false;
    
    if(((currentColor.r == 64  && currentColor.g == 0   && currentColor.b == 128)  || 
        (currentColor.r == 128 && currentColor.g == 192 && currentColor.b == 0)    || 
        (currentColor.r == 160 && currentColor.g == 192 && currentColor.b == 192)) && 
        (it.getZ() > 0.3 && it.getZ() < 1.5)){
        
      // is member of desired class
      isObject = true;
    }
    
    if(((currentColor.r == 192  && currentColor.g == 0    && currentColor.b == 0)    ||
        (currentColor.r == 192  && currentColor.g == 0    && currentColor.b == 128)  ||
        (currentColor.r == 192  && currentColor.g == 64   && currentColor.b == 128)) &&
        it.getZ() <= 0.3)
      isGrass = true;
      
    // add a z requirement to avoid counting shadows as goals, current colors are for people, chairs, balls
    if(isObject || isGrass){
    
      if(currentColor.r == 64  && currentColor.g == 0   && currentColor.b == 128){
        // ROS_INFO("Person found");
        label = "person";
      }
      else if(currentColor.r == 128 && currentColor.g == 192 && currentColor.b == 0){
        // ROS_INFO("Chair found");
        label = "chair";
      }
      else if(currentColor.r == 160 && currentColor.g == 192 && currentColor.b == 192){
        // ROS_INFO("Ball found");
        label = "ball";
      }
      else if(isGrass){
        // ROS_INFO("Grass found");
        label = "grass";
      }
        
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
          
          label,
        };
            
        // add to vector
        // ROS_INFO("First BB");
        bbInstances.push_back(tempBB);
        
        // test, show center of very first node
        continue;
      }
      else{
      
        // ROS_INFO("Non-empty BB");
            
        // iterate through bounding boxes -> DO NOT USE AN ITERATOR, YOU CANNOT CHANGE A VECTOR AS YOU ITERATE OVER IT
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
              
              label,
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
  
  int currentSize = bbInstances.size();
  int currentIdx = 0;
  int numErased = 0;
  
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
      else if(bbInstances[currentIdx].label != "grass"){    

        // ROS_INFO_STREAM("Current vector size = " << bbInstances.size() << " and idx = " << idx << '\n');
        
        // make newGoal and push into newGoals
        geometry_msgs::Pose newGoal = inflateGoal(robotX, robotY, bbInstances[currentIdx]);

        msgInstance.objPose = newGoal;
        msgInstance.objLabel = bbInstances[currentIdx].label;
        
        // ROS_INFO_STREAM("New message with area " << currentArea << " with x at " << newGoal.position.x << " and y at " << newGoal.position.y);
        
        msgPoses.sPoses.push_back(msgInstance); 
      }
      else if(bbInstances[currentIdx].label == "grass" && currentArea > 0.3){  
        
        // fill vector of messages of four floats (bounding box limits)
        grassBox.minX = bbInstances[currentIdx].minX;
        grassBox.maxX = bbInstances[currentIdx].maxX;
        
        grassBox.minY = bbInstances[currentIdx].minY;
        grassBox.maxY = bbInstances[currentIdx].maxY;
      
        grassland.grasslands.push_back(grassBox);
      }
    }
  }
  
  // publish goals and grass
  objPub_.publish(msgPoses);
  grassPub_.publish(grassland);
  
  // clear vectors
  bbInstances.clear();
  msgPoses.sPoses.clear();
  grassland.grasslands.clear();
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
  
  // higher minimum distance for grass 
  if(currentBB.label == "grass")
    minDistance = 0.5;
  else
    minDistance = 0.2;
  
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
  
  // create an object of class semanticExplore that will take care of everything
  semanticExplore semanticExplorer;
  
  ros::Rate r(0.5); // every 2 seconds
  
  while(ros::ok()){
        
    ros::spinOnce();   
    r.sleep();
  }

  return 0;
}
