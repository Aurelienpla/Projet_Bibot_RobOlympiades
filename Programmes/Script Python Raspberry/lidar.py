import rospy
import cv2
import numpy as np
import math
import time
from sensor_msgs.msg import LaserScan

def moyenneDistLine(line):
    somme = 0
    cpt = 0
    for dist in line:
        somme += dist
        cpt += 1
    return somme/cpt
    '''-------------------------fin moyenneDistLine-------------------------'''

def minimumDistLine(line):
    minimum = line[0]
    for dist in line:
        if dist > minimum:
            minimum = dist
    return minimum
    '''-------------------------fin minimumDistLine-------------------------'''

def printLine(line):
    for dist in line:
        print dist
    '''-------------------------fin displayLine-------------------------'''
    
def callback(data):
    angle_ratio = 57.3005093379#114.601018676
    frame = np.zeros((500, 500,3), np.uint8)
    angle = data.angle_min
    data.angle_min = 0
    #print data

    leftLine = []
    rightLine = []

    for r in data.ranges:
        angleDegre = angle*angle_ratio
        #change infinite values to 0
        if math.isinf(r) == True:
            r = 0
        #convert angle and radius to cartesian coordinates
        x = math.trunc((r * 30.0)*math.cos(angle + (-90.0*3.1416/180.0)))
        y = math.trunc((r * 30.0)*math.sin(angle + (-90.0*3.1416/180.0)))
        #print "Distance l'angle ", angleDegre, " = ", r, " metres."
        
        #filtrage de la vision gauche et droite entre 90 et 70 degre
        if angleDegre > 70 and angleDegre < 90 and r != 0:
            rightLine.append(r)
        elif angleDegre > -90 and angleDegre < -70 and r != 0 :
            leftLine.append(r)

        #set the borders (all values outside the defined area should be 0)
        if y > 0 or y < -35 or x<-40 or x>40:
            x=0
            y=0

        angle= angle + data.angle_increment
        #print(data.ranges[810])
        #time.sleep(0.1)
    '''-------------------------fin for-------------------------'''
    
    print "RIGHTLINE"
    printLine(rightLine)
    print "----------------------------------------------------------------------"
    
    print "LEFTLINE"
    printLine(leftLine)
    print "----------------------------------------------------------------------"
    
    minDistLineRight = minimumDistLine(rightLine)
    minDistLineLeft = minimumDistLine(leftLine)
    print "minDistRight", minDistLineRight
    print "minDistLeft", minDistLineLeft
    if minDistLineRight < 0.4:
        print "turnLeft"
    elif minDistLineLeft < 0.4:
        print "turnRight"
    else:
        print "Forward"
    
    #print(data)
    #time.sleep(2)
    #input("Press Enter to continue...")
'''-------------------------fin callback-------------------------'''

def laser_listener():
    rospy.init_node('laser_listener', anonymous=True)
    rospy.Subscriber("/scan", LaserScan,callback)
    rospy.spin()

if __name__ == '__main__':
    laser_listener()
