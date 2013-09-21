/* Simple Translation Recipe */
/* Recording Path followed by Turtlebot 1 at UoS Robotics Lab */

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <rosbag/bag.h>
#include <std_msgs/UInt32.h>
#include <stdio.h>


rosbag::Bag bag1("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/rate_rec.bag",rosbag::bagmode::Write);
rosbag::Bag bag2("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag",rosbag::bagmode::Write);

geometry_msgs::Twist cmdvel;
int count=0;

/* Subscribing cmd_vel topic and recording robot rate and velocity */

void pathCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
     cmdvel=*msg;

    /* if((cmdvel.linear.x != 0.0) || (cmdvel.angular.z != 0.0))
     {
         if (count==0)
           count++;
         else
           bag2.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag", rosbag::bagmode::Append);
         //bag2.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag", rosbag::bagmode::Append);
         bag2.write("cmdvel_rec",ros::Time::now(),cmdvel);
         bag2.close();
     }*/

}

int main(int argc,char **argv)
{
     ros::init(argc, argv, "path_rec");
     ros::NodeHandle n;

     std_msgs::UInt32 rate;
     rate.data = 10;
     ROS_INFO("Recording rate in bag file \n");

     //bag.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/rate_rec.bag",rosbag::bagmode::Write);
     bag1.write("rate",ros::Time::now(),rate);
     bag1.close();

     ros::Rate loop_rate(rate.data);
     ROS_INFO("Recording Turtlebot path started \n");
     ros::Subscriber sub = n.subscribe("cmd_vel",1 ,pathCallback);

     while(ros::ok())
     {

     //ros::Subscriber sub = n.subscribe("cmd_vel",10,pathcallback);
     
     ros::spinOnce();
      if((cmdvel.linear.x != 0.0) || (cmdvel.angular.z != 0.0))
     {
         if (count==0)
           count++;
         else
         bag2.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag", rosbag::bagmode::Append);
         //bag2.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag", rosbag::bagmode::Append);
         bag2.write("cmdvel_rec",ros::Time::now(),cmdvel);
         bag2.close();
     }

     loop_rate.sleep();

     }
     //bag2.close();
     return 0;

}

