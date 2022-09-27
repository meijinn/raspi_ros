#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt8MultiArray.h>

std_msgs::UInt8MultiArray servo;

void cont_Callback(const std_msgs::UInt8MultiArray& cmd_msg)
{
    servo.data[0] = cmd_msg.data[0];
    servo.data[1] = cmd_msg.data[1];

    if(servo.data[0] == 0 && servo.data[1] == 0){
        servo.data[0] == 90;
        servo.data[1] == 92;
    }

    ROS_INFO("steering:%d",servo.data[0]);
    ROS_INFO("throttle:%d",servo.data[1]);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vel_pub_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("controller", 10, cont_Callback);

    ros::Publisher servo_pub = nh.advertise<std_msgs::UInt8MultiArray>("servo", 10);
    ros::Rate loop_rate(100);

    while(ros::ok())
    {
        servo.data.resize(2);
        servo_pub.publish(servo);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}