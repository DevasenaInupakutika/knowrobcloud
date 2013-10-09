#ifndef MERGE_GRIDS_H
#define MERGE_GRIDS_H

#include <nav_msgs/OccupancyGrid.h>

namespace occupancy_grid_merge
{

// merges occupancy grids
//
// The resulting grid's origin will be a translated version of grid 1's origin, with resolution \a resolution//
// The policy for combination is that for each cell, we look at each grid cell that 
// intersects it and consider their values.  Map these to integers, where everything above
// OCCUPIED (100) goes to -1(Unknown).  Then take the max.  If there are no intersecting cells, value is -1. 
//
// Assumes all grids lie on the xy plane.
nav_msgs::OccupancyGrid::Ptr mergeGrids(const std::vector<nav_msgs::OccupancyGrid::ConstPtr>& grids, double resolution);

// mergeGrids function which uses the resolution of the first grid.
nav_msgs::OccupancyGrid::Ptr mergeGrids(const std::vector<nav_msgs::OccupancyGrid::ConstPtr>& grids);



} // namespace occupancy_grid_merge

#endif // include guard
