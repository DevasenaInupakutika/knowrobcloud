
#include <ros/ros.h>
#include "pcl_ros/point_cloud.h"
#include "pcl/point_types . h"
#include "pcl/filters/passthrough.h"
#include "pcl/filters/voxel_grid.h"
#include "pcl/features/organized_edge_detection.h"
#include "pcl/filters/radius_outlier_removal.h"
#include "geometry_msgs/Twist.h"

//Represents a request for a particular drive action , which may be to go straight , turn left , or turn right


enum DriveAction
{
   FORWARD, LEFT, RIGHT

};

//Performs obstacle detection and avoidance using two algorithms simultaneously

class TandemObstacleAvoidance
{
   private:
     ros::NodeHandle node;
     ros::Publisher velocity;
     ros::Publisher panorama;       //downsampled cloud
     
     ros::Publisher height;        //heightRange's region of interest
     ros::Publisher ground;        //groundEdges ' s region of interest
     ros::Publisher occlusions;    //ground level occlusions
  
     DriveAction currentMOTION ;  //pilot's account of what was last done : detection algorithms should not modify !

     DriveAction directionsPrimary;
     DriveAction directionsSecondary;
     std::list<int> heightRangeFrontSamples;
     double last_GROUND_CLOSEY, last_GROUND_CLOSEZ, last_GROUND_FARY, last_GROUND_FARZ;

     double GROUND_SLOPE, GROUND_YINTERCEPT;
     DriveAction groundLastForcedTurn;

     const char* directionRepresentation(DriveAction plan)
     {

        switch(plan)
        {

          case LEFT:
               return "LEFT";
          case RIGHT:
               return "RIGHT";
          default:
               return "FORWARD";
        }
      }

    public:

       TandemObstacleAvoidance(ros::NodeHandle& handle):
          node(handle), velocity(node.advertise<geometry_msgs::Twist>("/cmd_vel",1)),panorama(node . advertise<pcl::PointCloud<pcl::PointXYZ>>("panorama",1)),height (node.advertise<pcl::PointCloud<pcl::PointXYZ>>("height", 1)) , ground (node.advertise<pcl::PointCloud<pcl::PointXYZ>>("ground" , 1) ) ,occlusions (node.advertise<pcl::PointCloud<pcl::PointXYZ>>("occlusions" , 1) ) ,currentMOTION(FORWARD) , directionsPrimary(FORWARD) , directionsSecondary (FORWARD) ,last_GROUND_CLOSEY(0) , last_GROUND_CLOSEZ(0),last_GROUND_FARY(0) , last_GROUND_FARZ(0),groundLastForcedTurn(LEFT)
          {

            ros::MultiThreadedSpinner threads(3);
            ros::Subscriber heightRange= node.subscribe("/cloud_throttled",1,

