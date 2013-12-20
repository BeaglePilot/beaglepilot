from motors import Motor
import Adafruit_BBIO.GPIO as GPIO
import time

##############################
#Configure GPIOs
GPIO.setup("P8_4", GPIO.OUT) 
GPIO.output("P8_4", GPIO.HIGH)

GPIO.setup("P8_11", GPIO.OUT)
GPIO.output("P8_11", GPIO.HIGH)

GPIO.setup("P9_15", GPIO.OUT)
GPIO.output("P9_15", GPIO.HIGH)

GPIO.setup("P9_23", GPIO.OUT)
GPIO.output("P9_23", GPIO.HIGH)
##############################

speed = 0

m1 = Motor(1);
m1.setSpeed(speed);
m1.go()

m2 = Motor(2);
m2.setSpeed(speed*(-1));
m2.go()

m3 = Motor(3);
m3.setSpeed(speed);
m3.go()

m4 = Motor(4);
m4.setSpeed(speed*(-1));
m4.go()

