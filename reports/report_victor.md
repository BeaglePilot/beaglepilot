Reports of the Beagle-ROS project:
====================================

Community Bonding (21st April - 19th May 4 weeks):
------

- What has been accomplished?:
    - Infrastructure set up (Wikis, repos, project page, etc.)
    - Userspace driver for the InvenSense MPU-9150 
    - First steps towards the integration of the ArduPilot in the robot Erle (BeagleBone(white)-based)

- Issues:
    - Unanswered questions about the driver's functioning (https://groups.google.com/forum/#!topic/beaglepilot/apdfrT2fS-8)
    - _initialized is always false in the AP_Linux_HAL (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). AP_HAL_Linux_Main.h doesn't seem to be overriding properly. Due to this fact, there's no output.
    - When launched `ArduCopter.elf` the program doesn't output anything. The code gets stucked at https://github.com/BeaglePilot/ardupilot/blob/master/libraries/AP_InertialSensor/AP_InertialSensor.cpp#L187 when j == 5. After a bit more debugging it seems that there's an infinite loop here https://github.com/BeaglePilot/ardupilot/blob/master/libraries/AP_HAL_Linux/UARTDriver.cpp#L263.
    - If _initialized if forced to true. The following output appears, refer to https://gist.github.com/vmayoral/11181873. It seems that the code gets stucked at https://github.com/BeaglePilot/ardupilot/blob/master/libraries/AP_HAL_Linux/Scheduler.cpp#L183.     
    - libraries/*/examples don't compile with the AP_HAL_Linux (make linux) (refer to https://gist.github.com/vmayoral/11181796) 
    - How are motor pins configured for AP_HAL_Linux?. Can't find it.

- Plans for the next period:
    - Keep coding userspace drivers

    
