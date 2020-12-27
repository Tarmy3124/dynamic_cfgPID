#include <ros/ros.h>
#include <iostream>
#include "std_msgs/String.h"
#include "carMsgs/pid.h"
#include <dynamic_reconfigure/server.h>
#include "dynamic_cfgPID/roscarConfig.h"
carMsgs::pid msg;
bool changeflag=false;
void callback(dynamic_cfgPID::roscarConfig &config)
{
  ROS_INFO("Reconfigure Request: %d %f %s %s %d %f %f %f",
           config.int_param,
           config.double_param,
           config.str_param.c_str(),
           config.bool_param?"True":"False",
           config.size,
           config.kp_param,
           config.ki_param,
           config.kd_param);
  msg.k1_p=config.kp_param;
  msg.k1_i=config.ki_param;
  msg.k1_d=config.kd_param;
  changeflag=true;

}

int main(int argc, char **argv) {
  ros::init(argc, argv, "roscar");
  ros::NodeHandle n;
  ros::Publisher pid_pub = n.advertise<carMsgs::pid>("pid_float", 1000);
  //为这个进程的节点创建一个句柄。第一个创建的NodeHandle会为节点进行初始化，最后一个销毁的NodeHandle会清理节点使用的所有资源。
  ros::Rate loop_rate(50);
  dynamic_reconfigure::Server<dynamic_cfgPID::roscarConfig> server;
  dynamic_reconfigure::Server<dynamic_cfgPID::roscarConfig>::CallbackType f;

  f = boost::bind(&callback, _1); //绑定回调函数
  server.setCallback(f); //为服务器设置回调函数， 节点程序运行时会调用一次回调函数来输出当前的参数配置情况
while(ros::ok())
{
  
  ros::spinOnce(); //服务器循环监听重配置请求，当服务器收到重配置请求的时候，就会自动调用回调函数
  if(changeflag){
  pid_pub.publish(msg);
  changeflag=false;
  }
  loop_rate.sleep();
 // return 0;
}
}

