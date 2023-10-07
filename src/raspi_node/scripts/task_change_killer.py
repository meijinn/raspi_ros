#!/usr/bin/env python
import os
from subprocess import *
from task_change import kill_node

kill_node('ps3_twist_pub')
kill_node('cont_to_cmd_node')
p = Popen(['rosrun','raspi_node','ps3_twist_sub'])
#os._exit(0)
