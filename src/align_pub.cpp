#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

nav_msgs::OccupancyGrid map1;
bool newMap1 = false;
bool MapReceivedOnce = false;

void map1Callback(const nav_msgs::OccupancyGrid::ConstPtr &msg) 
{
   map1 = *msg; 
}

int main(int argc, char** argv) 
{ 

   ros::init(argc, argv, "align_pub");

   ros::NodeHandle n;
   ros::Publisher map_pub = n.advertise<nav_msgs::OccupancyGrid>("align", 1);
   ros::Subscriber map1_sub = n.subscribe("world", 1, map1Callback);

   ros::Rate(5.0);
   while(n.ok()){

       map_pub.publish(map1);

    }


   ros::spinOnce();

}

