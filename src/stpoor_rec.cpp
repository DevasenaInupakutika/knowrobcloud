/* Recording Initial pose and orientation of Turtlebot 1  */

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose.h>
#include <rosbag/bag.h>
#include <stdio.h>


rosbag::Bag bag("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/startpoor.bag", rosbag::bagmode::Write);
geometry_msgs::Pose start_odom;
int count=0;
/* Simple receipt of Start Pose and Odom (Robot Orientation) messages. */

void poseCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  if (count==0)
    {
     start_odom=msg->pose.pose;
     ROS_INFO("Starting position of turtlebot recorded");
     //bag.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/startpoor.bag", rosbag::bagmode::Write);
     bag.write("start_odom",ros::Time::now(),start_odom);
     bag.close();
     count++;
    }
}

int main(int argc,char **argv)
{
     ros::init(argc, argv, "stpoor_rec");
     ros::NodeHandle n;

     ros::Subscriber sub = n.subscribe("odom", 1, poseCallback);

     while(n.ok() && !count)
      {
	ros::spinOnce();
      }

     return 0;

}
