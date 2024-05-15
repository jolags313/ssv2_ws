# Navigation with Semantic SLAM
Developed by Joshua Lagria (thesis at the University of Texas at Dallas)

This repository allows for the autonomous exploration of and navigation through an unknown environment by a Clearpath Jackal (or any other type of wheeled robot given adjustments to the relevant parameters) using a RGB-D camera and a semantic segmentation model. Tested on Ubuntu 20.04 and ROS Noetic.


## Packages/Libraries
### Main Pipeline
- semantic_slam (by Xuan Zhang, used to create a 3D semantically annotated map of the environment, https://github.com/floatlazer/semantic_slam)
- ROS navigation stack (used to path plan given a frontier or semantic goal, http://wiki.ros.org/navigation)
- explore_lite (by Jiri Horner, used for frontier-based exploration, https://github.com/hrnr/m-explore)
- Clearpath Jackal libraries (https://github.com/jackal/jackal)
- realsense-ros (https://github.com/IntelRealSense/realsense-ros)
- jackal_2dnav, new_layers (used for semantic navigation based on desired classes/terrain)

### Simulation
- Gazebo (https://gazebosim.org/home)
- aws-robomaker-small-house-world (simulation environment, https://github.com/aws-robotics/aws-robomaker-small-house-world)
- Realsense Gazebo plugin (https://github.com/m-tartari/realsense_gazebo_plugin)

### Miscellaneous
- rrt_global_planner (sampling-based path planner https://github.com/mech0ctopus/rrt-global-planner)

**!!! Note that most of the needed packages are already included in this repository as they have been edited !!!**

## Usage
### In simulation
Pull and `catkin build` the main branch (or the octomap_script branch if the main branch has changed as of May 15, 2024) and run the following commands
- `roslaunch aws_robomaker_small_house_world small_house.launch`
- `roslaunch semantic_slam slam.launch`
- `roslaunch semantic_slam semantic_mapping.launch`

Wait for Gazebo to load before running the second command. Upon running the last command, an Rviz window will appear. At this point, use the controller/joystick to move the simulated Jackal forward just a bit (if you do not do this, the Jackal will regard its initial position as an obstacle and will not be able to move from its starting position). The OctoMap, costmap, frontiers, paths, etc can be toggled on and off as the Jackal engages in autonomous movement.

### With a real Jackal
**!!! Needs work, I have now graduated and will no longer be able to contribute to this part as of May 2024 !!!**

Work done on this is in the real_jackal branch, which is the one currently used on the CONLab Linux machine. The camera data streams and the SLAM and semantic mapping launch files work, but there is an issue with the map representation in Rviz (map drift likely due to tf issues)

To run the pipeline on the real Jackal, see the manual in Box and make sure the `.bashrc` or relevant environment variables have been set up properly- you should be able to see all of the Jackal sensor topics from the PC if this is the case. Then, just run the latter two commands above.

## Edits
### Semantic Classes
To set which semantic classes the Jackal should navigate to, edit lines 55-57 in `jackal_2dnav/semantic_navigator.cpp` and change the rgb colors to match whichever colors correspond to the desired semantic classes in the OctoMap representation. Line 64 corresponds to types of terrain. The sequence in which each desired class is visited can be edited in `m-explore/explore/include/explore/explore.h` in the vector `sequence_`. You will also need to change variable names like `isBall` in the same file and in `m-explore/explore/src/explore.cpp` to match whichever classes you want. 

These changes/parameters should have been put into a .yaml file for ease of editing, but I didn't get around to it- this can be a quick and easy QoL change in the future for whoever wants to work on this further. Other parameters regarding path planning, movement, frontiers, etc can be found in other packages and are expanded upon in packages' respective documentation. For example, to test different path planners, one would edit the parameter in `jackal_2dnav/launch/move_base.launch`. 

