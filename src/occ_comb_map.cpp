#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include "merge_grids.h"

using namespace occupancy_grid_merge;

nav_msgs::OccupancyGrid::ConstPtr map1;
nav_msgs::OccupancyGrid::ConstPtr map2;
bool Map1rec = false;
bool Map2rec = false;
bool maps_get_once = false;

void map1Callback(const nav_msgs::OccupancyGrid::ConstPtr &msg) 
{
   map1 = msg; Map1rec = true; 
}

void map2Callback(const nav_msgs::OccupancyGrid::ConstPtr &msg) 
{
   map2 = msg; Map2rec = true; 
}

int main(int argc, char** argv) 
{ 

   ros::init(argc, argv, "occ_comb_map");

   ros::NodeHandle n;
   ros::Publisher map_pub = n.advertise<nav_msgs::OccupancyGrid>("map", 1);
   ros::Subscriber map1_sub = n.subscribe("/map1", 1, map1Callback);
   
   ros::Time received_map = ros::Time::now();
   
   ros::Subscriber map2_sub = n.subscribe("/map2", 1, map2Callback);
   tf::TransformListener listener;

   ros::Rate r(5.0);

   while(n.ok()){
      if (Map1rec && Map2rec) {
          maps_get_once = true;
      }

    if(maps_get_once && (Map1rec || Map2rec)){
        std::vector<nav_msgs::OccupancyGrid::ConstPtr> grids(2);
        nav_msgs::OccupancyGrid::ConstPtr merged_map;

      

        grids[0] = map1;
        grids[1] = map2;

        merged_map = mergeGrids(grids, 0.05);
        map_pub.publish(merged_map);

        Map1rec = false;
        Map2rec = false;

    }

    ros::Time pub_merge_map = ros::Time::now();
    ros::spinOnce();
    r.sleep();
    double ToR = (pub_merge_map - received_map).toSec();
    ROS_INFO("Time to response is: %f",ToR);
}

}
   
