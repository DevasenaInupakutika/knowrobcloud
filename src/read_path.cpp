#include <ros/ros.h>
#include <rosbag/bag.h>
#include <geometry_msgs/Twist.h>
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#include <std_msgs/UInt32.h>
#include <stdio.h>

int main(int argc,char** argv)
{
  ros::init(argc,argv,"read_path");
  rosbag::Bag bag1;
  rosbag::Bag bag2;
  ros::NodeHandle n;
  int i;
  std_msgs::UInt32 r;
  std::vector<geometry_msgs::Twist> cmdvel_out;


  // Reading rate bag file.

  bag1.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/rate_rec.bag",rosbag::bagmode::Read);
  rosbag::View view1(bag1, rosbag::TopicQuery("rate"));
  
    BOOST_FOREACH(rosbag::MessageInstance const m,view1)
    {
       std_msgs::UInt32::ConstPtr objr=m.instantiate<std_msgs::UInt32>();
       r =*objr;
    }

  ROS_INFO("The rate is %d : ",r.data);

  bag1.close();

  // Reading recorded path bag file. 

  bag2.open("/home/turtlebot/fuerte_workspace/sandbox/knowrobcloud/bagfiles/path_rec.bag",rosbag::bagmode::Read);
  rosbag::View view2(bag2, rosbag::TopicQuery("cmdvel_rec"));

    BOOST_FOREACH(rosbag::MessageInstance const m,view2)
      {
        geometry_msgs::Twist::ConstPtr obj=m.instantiate<geometry_msgs::Twist>();
        cmdvel_out.push_back(*obj);

        ROS_INFO("The velocity is : %f, %f",obj->linear.x,obj->angular.z);
      }

   // Halting robot in the end.
 
   geometry_msgs::Twist obj_end;
   obj_end.linear.x = 0.0;
   obj_end.angular.z = 0.0;
   cmdvel_out.push_back(obj_end);

   bag2.close();
   ros::Rate loop_rate(r.data);

   ros::Publisher cmdvel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel",10);
   i=0;
   while((n.ok()) && (i<cmdvel_out.size()))
   {
      cmdvel_pub.publish(cmdvel_out[i]);
      loop_rate.sleep(); 
      i++;
      
   }

 return 0;

}
