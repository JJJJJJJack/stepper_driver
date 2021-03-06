// Created 03-12-2018
// xiang.he@utah.edu
// For research only
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "std_msgs/Float64.h"
#include <wiringPi.h>

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace std;

std::string exec(const char* cmd) {
  char buffer[128];
  std::string result = "";
  FILE* pipe = popen(cmd, "r");
  if (!pipe) throw std::runtime_error("popen() failed!");
  try {
    while (fgets(buffer, sizeof buffer, pipe) != NULL){
      result += buffer;
    }
  } catch (...) {
    pclose(pipe);
    throw;
  }
  pclose(pipe);
  return result;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "stepper_driver");
  ros::NodeHandle n;
  //Publish topics
  //ros::Publisher pub_att = n.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_attitude/attitude",100);
  //ros::Publisher pub_thr = n.advertise<std_msgs::Float64>("mavros/setpoint_attitude/att_throttle", 100);
  //Subscribe topics
  //ros::Subscriber sub_position = n.subscribe("mavros/local_position/pose", 1000, x_position_Callback);
  system("echo 512 > /sys/devices/platform/pwm-ctrl/duty0");
  system("echo 4000 > /sys/devices/platform/pwm-ctrl/freq0");
  system("echo 1 > /sys/devices/platform/pwm-ctrl/enable0");
  
  ros::Rate loop_rate(100);
  int count = 1;
  ros::Time last_request = ros::Time::now();
  //wiringPiSetup();
  //wiringPiSetupSys();
  //pinMode(236, INPUT) ;
  while(ros::ok()){
    // Do the work
    ros::spinOnce();
    count++;
    if(count%100 == 0){
      cerr<<".";
      string result = exec("gpio read 4");//digitalRead(236);
      cout<<"Reading port 236:"<<stoi(result)<<endl;
    }
    loop_rate.sleep();
  } 
  return 0;
  system("echo 0 > /sys/devices/platform/pwm-ctrl/enable0");
}
