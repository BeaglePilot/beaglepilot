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
    - _initialized is always false in the AP_HAL_Linux. When launched `ArduCopter.elf` the program doesn't output anything. If `_initialized`is forced to `true`the code gets stuck as well (refer https://github.com/diydrones/ardupilot/issues/1027).
    - libraries/*/examples don't compile with the AP_HAL_Linux (make linux) (refer to https://github.com/diydrones/ardupilot/issues/1028) 
    - How are motor pins configured for AP_HAL_Linux?. Can't find it.

- Plans for the next period:
    - Keep coding userspace drivers

    
