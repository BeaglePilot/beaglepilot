# -*- encoding: utf-8 -*-
'''
                                          
 _____     _        _____     _       _   
|   __|___| |___   | __  |___| |_ ___| |_ 
|   __|  _| | -_|  |    -| . | . | . |  _|
|_____|_| |_|___|  |__|__|___|___|___|_|  
                                          
@author: Víctor Mayoral Vilches <victor@erlerobot.com>
@description: Interface with the DC motors.
'''
import Adafruit_BBIO.PWM as PWM    
"""
This class is assuming that last version of Adafruit_BBIO 
(https://github.com/adafruit/adafruit-beaglebone-io-python) been installed. 
This version assumes that duties 0(off)-100(on).
To upgrade run:
   sudo pip install --upgrade Adafruit_BBIO 
"""

class Motor:
    """ @brief Class for interfacing with the motors.

        The class controls the motors speed using the sysfs PWM provided
        by Adafruit_BBIO.
        The duty should be provided in the range (0,100) and the speed
        in this range. The hardware is preset to satisfy the robot needs (two motors CW and two CCW)
        
        @warning in previous versions the range (-100,100) was accepted. New code just accepts
        values in the (0,100).
        @note the hardware is installed in a way that the motors rotating direction is the one needed
        (e.g.: 1,3 CW and 2,4 CCW)
    """ 
    def __init__(self, motor_number=1, max_speed=100, min_speed=0):
        self.speed = 0;        
        # self.motor_pins_list = [["P9_14", "P9_16"], 
        #                     ["P8_19", "P8_13"],
        #                     ["P9_22", "P9_21"],
        #                     ["P9_42", "P9_28"]]        
        self.motor_pins_list = ["P9_14", "P9_16" 
                            "P9_22", "P9_21"]
        if (motor_number > 4) or (motor_number < 1):
            raise Exception("Motor number provided out of bounds! ([1-4])")
        self.motor_number = motor_number # 1, 2, 3 or 4
        self.max_speed= max_speed
        self.min_speed= min_speed
        self.frequency = 2000
        self.motor_pin = self.motor_pins_list[self.motor_number - 1]
        #perform PWM initialization        
        # DC Brushed motors
        # self.duty_IN1 = 0 # duty input 1 of the motor controller IC 
        # self.duty_IN2 = 0 
        # PWM.start(self.motor_pin[0], self.duty_IN1, self.frequency)
        # PWM.start(self.motor_pin[1], self.duty_IN2, self.frequency)        
        # DC Brushless motors
        self.duty = 0
        PWM.start(self.motor_pin), self.duty, self.frequency)

    def setSpeed(self, speed):
        """ @brief Set the duties according to the speed attribute for the DC Brushed motors

            @warning Not to be used with the brushless configuration
        """        
        if speed<=self.max_speed or speed>=self.min_speed:
            if speed > 0:
                self.duty_IN1 = abs(speed)
                self.duty_IN2 = 0
            else:
                self.duty_IN1 = 0
                self.duty_IN2 = abs(speed)            
        else:
            raise Exception("Speed provided not in the [-100,100] range!")

    def setSpeedBrushless(self, speed):
        """ @brief Set the duties according to the speed attribute for the DC Brushless motors            
        """
        if speed<=self.max_speed or speed>=self.min_speed:
            self.duty = speed
        else:
            raise Exception("Speed provided not in the [%s,%s] range!" % self.min_speed, self.max_speed)



    """ update the motor PWM according to the class duty attributes
    """
    def go(self):
        # DC Brushed motors
        # PWM.set_duty_cycle(self.motor_pin[0],self.duty_IN1)
        # PWM.set_duty_cycle(self.motor_pin[1],self.duty_IN2)
        # DC Brushless motors
        PWM.set_duty_cycle(self.motor_pin, self.duty)

