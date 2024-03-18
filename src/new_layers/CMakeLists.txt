cmake_minimum_required(VERSION 3.0.2)
project(new_layers)

find_package(catkin REQUIRED COMPONENTS
  costmap_2d
  dynamic_reconfigure
  roscpp
  jackal_2dnav
)

catkin_package(
   INCLUDE_DIRS include
   LIBRARIES terrain_layer
   CATKIN_DEPENDS costmap_2d dynamic_reconfigure pluginlib roscpp jackal_2dnav
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(terrain_layer src/terrain_layer.cpp)

add_dependencies(terrain_layer ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(
    terrain_layer ${catkin_LIBRARIES}
)

install(FILES costmap_plugins.xml
	      DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(TARGETS terrain_layer
	      LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})
	      
install(
    DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
