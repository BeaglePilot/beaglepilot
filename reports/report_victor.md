Reports of the Beagle-ROS project:
====================================

Community Bonding (21st April - 19th May 4 weeks):
------

- What has been accomplished?:
    - Infrastructure set up (Wikis, repos, project page, etc.)
    - Driver for the InvenSense MPU-9150
    - First steps towards the integration of the ArduPilot in the robot Erle (BeagleBone(white)-based)

- Issues:
    - Unanswered questions about the driver's functioning (https://groups.google.com/forum/#!topic/beaglepilot/apdfrT2fS-8)
    - _initialized is always false in the AP_Linux_HAL (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). AP_HAL_Linux_Main.h doesn't seem to be overriding properly.
    - libraries/*/examples don't compile with the AP_HAL_Linux (make linux) (refer to https://gist.github.com/vmayoral/11181796) 
    - Ardupilot doesn't seem to get into the CLI mode and the behaviour seems non deterministic (refer to https://gist.github.com/vmayoral/11181873). Some more debugging is needed.

- Plans for the next period:
    - Keep coding userspace drivers

    
