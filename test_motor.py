#!/usr/bin/env python

from motors import Motor
import Adafruit_BBIO.GPIO as GPIO
import time
import os

###############################
##Configure GPIOs, necessary when using the DC Brushed motors
###############################
#GPIO.setup("P8_4", GPIO.OUT) 
#GPIO.output("P8_4", GPIO.HIGH)
#
#GPIO.setup("P8_11", GPIO.OUT)
#GPIO.output("P8_11", GPIO.HIGH)
#
#GPIO.setup("P9_15", GPIO.OUT)
#GPIO.output("P9_15", GPIO.HIGH)
#
#GPIO.setup("P9_23", GPIO.OUT)
#GPIO.output("P9_23", GPIO.HIGH)
###############################

# initial timer
time.sleep(10)

speed = 10

m1 = Motor(1);
m1.setSpeed(speed);
m1.go()

m2 = Motor(2);
m2.setSpeed(speed);
m2.go()

m3 = Motor(3);
m3.setSpeed(speed);
m3.go()

m4 = Motor(4);
m4.setSpeed(speed));
m4.go()

time.sleep(10)

speed = 0

m1.setSpeed(speed);
m1.go()

m2.setSpeed(speed);
m2.go()

m3.setSpeed(speed);
m3.go()

m4.setSpeed(speed(1));
m4.go()

#####
# Shut down the robot
#####
#os.system("shutdown -h now")

