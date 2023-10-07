#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <unistd.h>
#include <string.h>

geometry_msgs::Twist cmd_vel;

void cont_callback(const geometry_msgs::Twist& cont_msg){
	cmd_vel.linear.x = cont_msg.linear.x;
	cmd_vel.angular.z = cont_msg.angular.z;
	if(cont_msg.linear.y == 1){
		ros::shutdown();
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "cont_to_cmd_node");
	ros::NodeHandle nh;

	//publish
	ros::Publisher cmd_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 10);
	//	//subscribe
	ros::Subscriber cmd_sub = nh.subscribe("controller", 10, cont_callback);

	ros::Rate loop_rate(100);

	while(ros::ok()){
		printf("\rTurn on. ");
		printf("Please operate.\r");
		fflush(stdout);
		cmd_pub.publish(cmd_vel);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
