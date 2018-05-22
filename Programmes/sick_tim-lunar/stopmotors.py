from Tkinter import *
import os
import serial
import time

root = Tk()
motor1 = 0
motor2 = 0
print('1')
ser = serial.Serial("/dev/serial0", 9600, writeTimeout = 0)
print('2')
time.sleep(2)


print('3')
ser.write("M1: 0\r\n")
ser.write("M2: 0\r\n")
print('4')
