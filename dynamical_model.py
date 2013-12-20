# -*- encoding: utf-8 -*-
'''
                                          
 _____     _        _____     _       _   
|   __|___| |___   | __  |___| |_ ___| |_ 
|   __|  _| | -_|  |    -| . | . | . |  _|
|_____|_| |_|___|  |__|__|___|___|___|_|  
                                          
@author: Víctor Mayoral Vilches <victor@erlerobot.com>
@description: This class implements the dynamical model of a quadrotor. 
It does so following the dynamical model studied at the Master Thesis "Design, 
implementation and ﬂight test of indoor navigation and control system for a 
quadrotor UAV"
(http://www.st.ewi.tudelft.nl/~koen/in4073/Resources/MSc_thesis_X-UFO.pdf)
'''
import math
import numpy as np

class Dynamical_Model:
    def __init__(self): 
        # general paramters
        self.g = 9.806 # Gravity constant [m s^-2 ]
        self.rho = 1.293 # Air density [kg m^-3]
        self.nu = 1.8e-5 # Air viscosity at 20 degrees Celsius [Pa s]

        # quadrotor parameters
        self.P = 4 # number of propellers
        self.L = 29.9974e-3 # Arm length [m]
        self.Vol = 0.00281784516 # Volume [m3] (((86.36*86.36)/1000) * 
        self.m = 60e-3 # quadrotor mass [kg]
        self.h = 17e-3 # Vertical distance between CoG and propellers plan [m]                         #                  (8*29.99/1000) * (1.5748/1000))       
        self.b = 3.13e-5 # thrush factor in hover [N s^2]
        self.d = 7.5e-7 # drag factor in hover [N m s^2]
        self.W_prop = (self.m * self.g)/self.P # weight of the quadrotor per propeller [N]
        self.Omega_H = math.sqrt(self.W_prop/self.b) # propeller speed at hover

        # propellers
        self.N = 2 # Number of blades per propeller
        self.R = 32.5e-3 # Propeller radius [m]
        self.A = math.pi*math.pow(self.R, 2)# Propeller disk area [m^2]
        self.c = 0.0394 # Chord [m]
        self.theta_0 = 0.2618 # Pitch of incidence [rad]
        self.theta_tw = 0.045 # Twist pitch [rad]
        self.sigma = self.N * self.c/(math.pi * self.R) # Solidity ratio (rotor fill ratio) [rad^-1]
        self.a = 5.7 # Lift slope
        self.C_d = 0.052 # Airfoil drag coefficient
        self.A_c = 0.005 # Helicopter center hub area [m^2]
        # Longitudinal drag coefficients
        self.Cx = 1.32
        self.Cy = 1.32
        self.Cz = 1.32

        # Inertia components [kg m^2]
        self.Ixx = 6.228e-3
        self.Iyy = 6.228e-3
        self.Izz = 1.121e-2

        # motor parameters
        # TODO complete the motor parameters
        self.k_m = #TODO # torque constant
        self.tau = #TODO # motor time constant
        self.eta = #TODO # motor efficiency
        self.Omega_0 = #TODO # point of linearization of the rotor speeds
        self.r = 4 # Reduction ratio
        self.J_t = 6.0100e-5 # Rotor inertia [kg m^2]

        # matrix for calculating the motor voltages form the control inputs
        self.m = np.matrix( ((1/(4*self.b),0, 1/(2*self.b), -1/(4*self.b)), 
                        (1/(4*self.b),-1/(2*self.b), 0, 1/(4*self.b)), 
                        (1/(4*self.b),0, -1/(2*self.b), -1/(4*self.b)), 
                        (1/(4*self.b),1/(2*self.b), 0 ,  1/(4*self.b))) )



    """ Compute the motor voltages from the control inputs. Keep in mind when
        passing parameters the following correspondences.
            - U1: thrust
            - U2: roll
            - U3: pitch
            - U4: yaw

        @returns: u=[u_m1, u_m2, u_m3, u_m3], motor voltages
    """
    def motor_inversion(thrust, roll, pitch, yaw):
        # the control inputs
        U = np.array( ((thrush, roll, pitch, yaw)) )
        # the motor voltages
        u = self.k_m * self.tau ((1/self.tau + 2*self.d*self.Omega_0/(self.eta*np.pow(self.r,3)*self.J_t))*np.sqrt(np.dot(self.m,U))- self.d*np.pow(self.Omega_0,3)/(self.eta*np.pow(self.r,3)*self.J_t))
        return u



