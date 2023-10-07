#!/usr/bin/env python

import os
import rospy
from geometry_msgs.msg import Twist
from subprocess import *

def callback(cont_msg):
    #if cont_msg.linear.y == 1:
    #    kill_node('cont_to_cmd_node')
    if cont_msg.linear.z == 1:
        call(['rosrun','raspi_node','ps3_twist_sub'])

def kill_node(nodename): 
	p2=Popen(['rosnode','list'],stdout=PIPE) 
	p2.wait() 
	nodelist=p2.communicate() 
	nd=nodelist[0] 
	nd=nd.split("\n") 
	for i in range(len(nd)): 
		tmp=nd[i] 
		ind=tmp.find(nodename) 
		if ind==1: 
			call(['rosnode','kill',nd[i]]) 
			break 

def task_change():
    rospy.init_node('task_change')
    rospy.Subscriber('controller', Twist, callback)
    rospy.spin()

if __name__ == '__main__':
    task_change()
