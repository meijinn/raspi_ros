#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16MultiArray.h>

std_msgs::UInt16MultiArray servo;

void cont_Callback(const std_msgs::UInt16MultiArray& cmd_msg)
{
    servo.data[0] = cmd_msg.data[0];
    servo.data[1] = cmd_msg.data[1];

    printf("\rSteering:%d ",cmd_msg.data[0]);
    printf("Throttle:%d ",cmd_msg.data[1]);
    fflush(stdout);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "vel_pub_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("controller", 10, cont_Callback);

    ros::Publisher servo_pub = nh.advertise<std_msgs::UInt16MultiArray>("servo", 10);
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
