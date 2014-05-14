Reports of the BeaglePilot project:
====================================

----

**Note: Progress made in the project is being pushed to https://github.com/BeaglePilot/ardupilot and will eventually be merged into the official [ardupilot repository](https://github.com/diydrones/ardupilot)**

----

Community Bonding (21st April - 19th May 4 weeks):
------

- What has been accomplished?:
    - Infrastructure set up (Wikis, repos, project page, etc.)
    - [Initial video](https://www.youtube.com/watch?v=-giV6Xr8RtY) launched.
    - Userspace I2C driver for the InvenSense MPU-9150 
    - First steps towards the integration of the ArduPilot in the robot Erle (BeagleBone(white)-based). HAL_BOARD_ERLE created.
    - libraries/*/examples do compile now with the AP_HAL_Linux (make linux). Necessary to add the missing libraries.
    - Deadlock in `setup()` (initially _initialized variable discussion) addressed. Refer to https://github.com/BeaglePilot/ardupilot/commit/5189810651a2d0dd8d262ef30db404311c7829ce
    - InvenSense MPU-9150 driver working if [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db) is applied
    - InvenSense MPU-9250 SPI userspace driver coded
    - ST Microelectronics LSM9DS0 SPI userspace driver coded
    - All drivers compile together with the ardupilot code

- Issues:
    - How are motor pins configured for AP_HAL_Linux?. Can't find it.
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.

- Plans for the next period:
    - Go through Andrew's comments on the drivers coded so far.
    - Rebase the code according to the last verson of ardupilot.
    - Share progresses with I2C sensors. Publish material.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test the PRU PWM deeply. Study the integrations through the CLI.
    - Test the new DT
    - Test all the drivers
