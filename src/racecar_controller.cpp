#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include <iostream>

const float LINEAR_VEL = 2;
const float ANGULAR_VEL = 2;

geometry_msgs::Twist racecar;
ros::Publisher chatter_pub;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{

  int array_size = msg->ranges.size()-1;
  float left_side = 0, right_side = 0, middle = 0;

  for (int i = 0; i<10; i++) {
    left_side += msg->ranges[i];
    right_side += msg->ranges[array_size-i];
  }
  for (int i = 0; i<5; i++) {
    middle += msg->ranges[array_size/2 -i];
    middle += msg->ranges[array_size/2 +i];
  }

  if (middle >= left_side && middle >= right_side) {
    racecar.linear.x = LINEAR_VEL;
    if (left_side >= right_side)
      racecar.angular.z = -ANGULAR_VEL/2;
    else
      racecar.angular.z = ANGULAR_VEL/2;
  }
  else if (left_side >= right_side) {
    racecar.linear.x = LINEAR_VEL/2;
    racecar.angular.z = -ANGULAR_VEL;
  }
  else {
    racecar.linear.x = LINEAR_VEL/2;
    racecar.angular.z = ANGULAR_VEL;
  }

  chatter_pub.publish(racecar);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "racecar_talker");

  ros::NodeHandle n;
  chatter_pub = n.advertise<geometry_msgs::Twist>("robot/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("robot/base_scan", 1000, chatterCallback);
  ros::Rate loop_rate(10);

  racecar.linear.x = 0;
  racecar.linear.y = 0;
  racecar.linear.z = 0;
  racecar.angular.x = 0;
  racecar.angular.y = 0;
  racecar.angular.z = 0;

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
