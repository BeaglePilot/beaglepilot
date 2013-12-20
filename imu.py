# -*- encoding: utf-8 -*-
'''
                                          
 _____     _        _____     _       _   
|   __|___| |___   | __  |___| |_ ___| |_ 
|   __|  _| | -_|  |    -| . | . | . |  _|
|_____|_| |_|___|  |__|__|___|___|___|_|  
                                          
@author: Víctor Mayoral Vilches <victor@erlerobot.com>
@description: python interface with the IMU
'''
from ctypes import *
#from time import clock

# array class
Vector3d_t = 3*c_float
# array class
Quaternion_t = 4*c_float

# struct with C types
class Mpudata_t(Structure):
         _fields_ = [("rawGyro", c_short*3),
                     ("rawAccel", c_short*3),
                     ("rawQuat", c_long*4),
                     ("dmpTimestamp", c_ulong),
                     ("rawMag", c_short*4),
                     ("magTimestamp", c_ulong),
                     ("calibratedAccel", c_short*4),
                     ("calibratedMag", c_short*4),
                     ("fusedQuat", 4*c_float),
                     ("fusedEuler", 3*c_float),
                     ("lastDMPYaw", c_float),
                     ("lastYaw", c_float)
                    ]


class IMU:
    """ Interface with the Inertial Measurement Unit. 
    
    The IMU consists of an InvenSense 9-axis MPU-9150. This sensor provides
    readings from 3 accelerometers, 3 magnetometers and 3 gyroscopes.
    Furthermore, the module has a DMP (Digital Motion Processor) integrated
    that makes the calculations necessary to provide filtered outputs.
    """
    def __init__(self):
        #TODO Set I2C interface, make sure that calibrations files are available and make some readings
        # through ctypes.
        self.lib = CDLL("./imu/libimu.so")
        self.i2c_bus = 2
        self.lib.mpu9150_set_debug(0) # 1
        self.sample_rate = 50 # 50 Hz
        self.yaw_mix_factor = 3

        # initialize the IMU
        res = self.lib.mpu9150_init(self.i2c_bus, self.sample_rate, self.yaw_mix_factor)
        if res:
            Exception("Error when initializing the IMU!")
        # set calibration files
        res = self.lib.set_cal(0, "./imu/accelcal.txt")
        if res != 0:
            Exception("Error while calibration: accelcal.txt")
        res = self.lib.set_cal(0, "./imu/magcal.txt")
        if res != 0:
            Exception("Error while calibration: magcal.txt")


    """ Reads the raw gyro data from the sensor.
            pass a "timing = 1" parameter to measure the time for the measurement.
        @return  gyroX, gyroY, gyroZ
    """
    def read_rawGyro(self, timing = 0):    
        if timing:
            start = clock()
        while 1:
                # Parameters to be passed by reference
                x = c_short(0)
                y = c_short(0)
                z = c_short(0)
                function = self.lib.read_rawGyro
                function.argtypes = [POINTER(c_float), POINTER(c_float), POINTER(c_float)]
                res = function(byref(x), byref(y), byref(z)) 
                if res == 0:
                        time_s = clock() - start
                        print time_s
                        return x.value, y.value, z.value
    
    """ Reads fused euler angles
            pass a "timing = 1" parameter to measure the time for the measurement.
        @return  eulerX, eulerY, eulerZ (degrees)
    """
    def read_fusedEuler(self, timing = 0):    
        if timing:
            start = clock()
        while 1:
                # DMP fused euler angles
                fusedX = c_float(0)
                fusedY = c_float(0)
                fusedZ = c_float(0)
                function = self.lib.read_fusedEuler
                function.argtypes = [POINTER(c_short), POINTER(c_short), POINTER(c_short)]
                res = function(byref(x), byref(y), byref(z)) 
                if res == 0:
                        if timing:
                            time_s = clock() - start
                            print time_s
                        return x.value, y.value, z.value




    """ Reads all the IMU sensor information and stores it into a Mpudata_t.
            pass a "timing = 1" parameter to measure the time for the measurement.

            TODO: Eventually substitute this way of getting data for a ctypes direct cast
    """
    def read_mpudata_t(self, timing = 0):    
        if timing:
            start = clock()
        while 1:
                # Parameters to be passed by reference
                # Raw gyro values
                gyroX = c_short(0)
                gyroY = c_short(0)
                gyroZ = c_short(0)
                # Raw accel values
                accelX = c_short(0)
                accelY = c_short(0)
                accelZ = c_short(0)
                # Raw quaternion values
                quat1 = c_long(0)
                quat2 = c_long(0)
                quat3 = c_long(0)
                quat4 = c_long(0)
                # DMP timestamp
                dmpTimestamp = c_ulong(0)                
                # Raw accel values
                magX = c_short(0)
                magY = c_short(0)
                magZ = c_short(0)
                # magnetometer timestamp
                magTimestamp = c_ulong(0)
                # Calibrated accelerometer values
                calibratedAccelX = c_short(0)
                calibratedAccelY = c_short(0)
                calibratedAccelZ = c_short(0)
                # Calibrated magnetometer values
                calibratedMagX = c_short(0)
                calibratedMagY = c_short(0)
                calibratedMagZ = c_short(0)
                # DMP fused quaternions
                fusedQuat1 = c_float(0)
                fusedQuat2 = c_float(0)
                fusedQuat3 = c_float(0)
                fusedQuat4 = c_float(0)
                # DMP fused euler angles
                fusedX = c_float(0)
                fusedY = c_float(0)
                fusedZ = c_float(0)
                # Last DMP Yaw
                lastDMPYaw = c_float(0)
                # Last Yaw
                lastYaw = c_float(0)

                function = self.lib.read_mpudata_t
                function.argtypes = [POINTER(c_short), POINTER(c_short), POINTER(c_short),
                                    POINTER(c_short), POINTER(c_short), POINTER(c_short),
                                    POINTER(c_long), POINTER(c_long), POINTER(c_long), POINTER(c_long),
                                    POINTER(c_ulong),POINTER(c_short), POINTER(c_short), POINTER(c_short),
                                    POINTER(c_ulong),POINTER(c_short), POINTER(c_short), POINTER(c_short),
                                    POINTER(c_short), POINTER(c_short), POINTER(c_short),
                                    POINTER(c_float), POINTER(c_float), POINTER(c_float), POINTER(c_float),
                                    POINTER(c_float), POINTER(c_float), POINTER(c_float),
                                    POINTER(c_float), POINTER(c_float)]

                res = function(byref(gyroX), byref(gyroY), byref(gyroZ),
                                byref(accelX), byref(accelY), byref(accelZ),
                                byref(quat1), byref(quat2), byref(quat3), byref(quat4),
                                byref(dmpTimestamp), byref(magX), byref(magY), byref(magZ), 
                                byref(magTimestamp), byref(calibratedAccelX), byref(calibratedAccelY), byref(calibratedAccelZ), 
                                byref(calibratedMagX), byref(calibratedMagY), byref(calibratedMagZ),
                                byref(fusedQuat1), byref(fusedQuat2), byref(fusedQuat3), byref(fusedQuat4),
                                byref(fusedX), byref(fusedY), byref(fusedZ), byref(lastDMPYaw), byref(lastYaw))

                if res == 0:
                        if timing:
                            time_s = clock() - start
                            print time_s
                        # Construct an instance of Mpudata_t
                        mpudata_t = Mpudata_t(rawGyro = (c_short*3)(*[gyroX.value, gyroY.value, gyroZ.value]),
                                                rawAccel = (c_short*3)(*[accelX.value, accelY.value, accelZ.value]),
                                                rawQuat = (c_long*3)(*[quat1.value, quat2.value, quat3.value,, quat4.value]),
                                                dmpTimestamp = (c_ulong)(dmpTimestamp.value),
                                                rawMag = (c_short*3)(*[magX.value, magY.value, magZ.value]),
                                                magTimestamp = (c_ulong)(magTimestamp.value),
                                                calibratedAccel = (c_float*3)(*[calibratedAccelX.value, calibratedAccelY.value, calibratedAccelZ.value]),
                                                calibratedMag = (c_float*3)(*[calibratedMagX.value, calibratedMagY.value, calibratedMagZ.value]),
                                                fusedQuat = (c_float*4)(*[fusedQuat1.value, fusedQuat2.value, fusedQuat3.value, fusedQuat4.value]),
                                                fusedEuler = (c_float*3)(*[fusedX.value, fusedY.value, fusedZ.value]),
                                                lastDMPYaw = (c_float)(lastDMPYaw),
                                                lastDMPYaw = (c_float)(lastYaw)

                                            )                            
                        return mpudata_t



"""
imu = IMU()
gyrox, gyroy, gyroz = imu.read_rawGyro()
print gyrox
print gyroy
print gyroz
"""



