#ifndef GRID_LAYER_H_
#define GRID_LAYER_H_

#include <ros/ros.h>

#include <costmap_2d/layer.h>
#include <costmap_2d/layered_costmap.h>
#include <costmap_2d/GenericPluginConfig.h>

#include <jackal_2dnav/grassLimits.h>
#include <jackal_2dnav/grasslands.h>

#include <dynamic_reconfigure/server.h>

namespace terrain_layer_namespace
{

class TerrainLayer : public costmap_2d::Layer, public costmap_2d::Costmap2D
{

public:
  TerrainLayer();

  virtual void onInitialize();
  
  // find the areas we want to change (grass) and expand the min/max bounds to include them. We then set the cost in the layer's own costmap using the setCost method
  virtual void updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x, double* max_y);
  
  // Overwrite previous values of the master costmap to include our marks; we do not overwrite if the layer's costmap value is NO_INFORMATION
  virtual void updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j);
  
  bool isDiscretized()
  {
    return true;
  }

  virtual void matchSize();

private:
  void reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level);
  dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig> *dsrv_;
  
  // subscriber for /grassland
  ros::Subscriber sub_;
  
  // vector of grassLimits messages = /grassland
  jackal_2dnav::grasslands grassyAreas_;
  
  void grassCallback(const jackal_2dnav::grasslands& grassyAreas);
  
  // grass cost, just use 50 (see figure explaining inflation) -> why is this a char? Just following how they do it in cost_values.h and the documentation
  static const unsigned char GRASS_COST_ = 15;
  
  
}; // class

} // namespace

#endif
