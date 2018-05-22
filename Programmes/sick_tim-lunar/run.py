import rospy
import cv2
import numpy as np
import math
import os
import serial
import time
from sensor_msgs.msg import LaserScan

motor1 = 0
motor2 = 0

def startUp():
	#both motors to 1000 speed
	for index in range(0, 100):
		incMotor1(10)
		incMotor2(10)

def incMotor1(data):
	global motor1
	motor1 += data
	if motor1 >= 2047:
		motor1 = 2000
	ser.write('M1: %d\r\n' % motor1)
	#print('M1: %d\r\n' % motor1)
def decMotor1(data):
	global motor1
	motor1 -= data
	if motor1 <= -2047:
		motor1 = -2000
	ser.write("M1: %d\r\n" % motor1)
	#print('M1: %d\r\n' % motor1)
def incMotor2(data):
	global motor2
	motor2 += 10
	if motor2 >= 2047:
		motor2 = 2000
	ser.write("M2: %d\r\n" % motor2)
	#print("M2: %d\r\n" % motor2)
def decMotor2(data):
	global motor2
	motor2 -= data
	if motor2 <= -2047:
        	motor2 = -2000
	ser.write("M2: %d\r\n" % motor2)
	#print("M2: %d\r\n" % motor2)

def obstacleDetection(angle, dist):
	#right side
	if angle < 90 and angle > 70 and dist < 0.4:
		#decMotor1(10)
		#incMotor2(10)
		return "Right"
	if angle < 70 and angle > 30 and dist < 0.4:
		decMotor1(20)
		incMotor2(20)
		return "Right"
	if angle < 30 and angle > 0 and dist < 0.4:
		decMotor1(30)
		incMotor2(30)
		return "Right'''
	#left side
	if angle < 0 and angle > -30 and dist < 0.4:
		incMotor1(30)
		decMotor2(30)
		return "Left"
	if angle < -50 and angle > -70 and dist < 0.4:
		decMotor1(20)
		incMotor2(20)
		return "Left"
	if angle < -70 and angle > -90 and dist < 0.4:
		#decMotor1(10)
		#incMotor2(10)
		return "Left"

def callback(data):
	angle_ratio = 57.3005093379#ratio ~= 135/2.356
	frame = np.zeros((500, 500,3), np.uint8)
	angle = data.angle_max * angle_ratio
	index = 0
	for r in data.ranges:
		dist = data.ranges[index]
		if math.isinf(r) != True and math.isinf(dist) != True:
			side = obstacleDetection(angle, dist)
			if side == "Left" or side == "Right":
				print angle, "/", dist
				break
			else:
				print "\n"

			#increment to next angle and index
			angle = angle - data.angle_increment * angle_ratio
			index += 1
		else:
			angle = angle - data.angle_increment * angle_ratio
			index += 1

	#print data.ranges[0], " metres a l'angle ", data.angle_max * angle_ratio

'''-------------------------fin callback-------------------------'''

def laser_listener():
	rospy.init_node('laser_listener', anonymous=True)
	rospy.Subscriber("/scan", LaserScan,callback)
	rospy.spin()

if __name__ == '__main__':
	ser = serial.Serial("/dev/serial0", 9600, writeTimeout = 0)
	time.sleep(2)
	startUp()
	laser_listener()
