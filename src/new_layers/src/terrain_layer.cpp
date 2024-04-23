#include <new_layers/terrain_layer.h>
#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(terrain_layer_namespace::TerrainLayer, costmap_2d::Layer)

using costmap_2d::LETHAL_OBSTACLE;
using costmap_2d::NO_INFORMATION;

namespace terrain_layer_namespace
{

TerrainLayer::TerrainLayer() {}

void TerrainLayer::onInitialize()
{
  ros::NodeHandle nh("~/" + name_);
  current_ = true;
  default_value_ = NO_INFORMATION;
  matchSize();

  dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);
  dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(&TerrainLayer::reconfigureCB, this, _1, _2);
  dsrv_->setCallback(cb);
  
  sub_ = nh.subscribe("/grassland", 1, &TerrainLayer::grassCallback, this);
}

void TerrainLayer::grassCallback(const jackal_2dnav::grasslands& grassyAreas){
  // just copying into class member
  grassyAreas_ = grassyAreas;
}

void TerrainLayer::matchSize()
{
  Costmap2D* master = layered_costmap_->getCostmap();
  resizeMap(master->getSizeInCellsX(), master->getSizeInCellsY(), master->getResolution(), master->getOriginX(), master->getOriginY());
}


void TerrainLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level)
{
  enabled_ = config.enabled;
}

void TerrainLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x, double* max_y)
{
  if (!enabled_)
    return;
  
  // resolution (meters/cell)
  Costmap2D* tempPtr = layered_costmap_->getCostmap();
  float resolution = tempPtr->getResolution();
  
  // grassyAreas_ length = number of grassy areas
  for(int i = 0; i < grassyAreas_.grasslands.size(); ++i){
    
    // find number of columns and rows in the x and y -> result is an int, so the fractional part is discarded
    int numX = (grassyAreas_.grasslands[i].maxX - grassyAreas_.grasslands[i].minX) / resolution;
    int numY = (grassyAreas_.grasslands[i].maxY - grassyAreas_.grasslands[i].minY) / resolution;
    
    // find points within each cell and set the cost for that cell
    for(int row = 0; row < numY; ++row){
    
      for(int col = 0; col < numX; ++col){
      
        unsigned int mapX;
        unsigned int mapY;
        
        double worldX = grassyAreas_.grasslands[i].minX + (col * resolution);
        double worldY = grassyAreas_.grasslands[i].minY + (row * resolution);
        
        // set cost
        if(worldToMap(worldX, worldY, mapX, mapY)){
          setCost(mapX, mapY, GRASS_COST_);
          
        // update bounds
        *min_x = std::min(*min_x, worldX);
        *max_x = std::max(*max_x, worldX);
    
        *min_y = std::min(*min_y, worldY);
        *max_y = std::max(*max_y, worldY);
        }
      }
    }
  }
}

void TerrainLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j)
{
  if (!enabled_)
    return;

  for (int j = min_j; j < max_j; j++)
  {
    for (int i = min_i; i < max_i; i++)
    {
      int index = getIndex(i, j);
      
      if (costmap_[index] == NO_INFORMATION)
        continue;
        
      master_grid.setCost(i, j, costmap_[index]); 
    }
  }
}

} // end namespace
