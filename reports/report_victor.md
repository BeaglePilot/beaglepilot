Reports of the BeaglePilot project:
====================================

----

**Note: Progress made in the project is being pushed to https://github.com/BeaglePilot/ardupilot and will eventually be merged into the official [ardupilot repository](https://github.com/diydrones/ardupilot)**

----

Overall Progress
------
The following table pictures the status of the goals:

| Goal | Status |
|------|--------|
| MPU-9150 (I2C) userspace driver (extra) | Working |
| MPU-9250 (SPI) userspace driver | Coded |
| LSM9DS0 (SPI) userspace driver | Coded |
| PRU PWM | Working |
| Realtime Comparison | Working (Done) |
| ROS tests with `mavlink_ros` | TBD |
| ROS bridge coded directly in the ArduPilot | TBD |
| IDE Integration | WIP | 
| Security | TBD |

Possible status: `TBD`, `WIP`, `Coded` and `Working`.

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
    - RT_PREEMPT kernel and PRU seem to conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/).
    - How are motor pins configured for AP_HAL_Linux?. Can't find it.
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.
    - hrt_absolute_time is PX4 specific. Check http://api.ning.com/files/hSOUK3FODot8zhNDso2dqdmI8P7ahYVaLApua6fxhIR2z*wHyKdcZbpMy9dQL0lqV7i70-m97kmofvccA-QaddUcAmWDPnD8/drv_hrtv1.c.

- Plans for the next period:
    - Set up a Xenomai-patched Linux kernel and test whether there're issues with it as with the RT_PREEMPT one.
    - Check Andrew's patch with new ideas for I2CDriver.
    - Modify the I2C driver to accept a bus number
    - Share progresses with I2C sensors. Publish material. Wire up the 10 DOF boards received and make some tests.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test the PRU PWM deeply. Study the integrations through the CLI.
    - Test the new DT
    - Test all the drivers
    - Ideas about the new AP_HAL_Linux


First Week
------

- What has been accomplished?:
    - Tested PRU PWM in (not patched) kernel. Working good.
    - Issue between PRU and RT_PREEMPT kernel detected.
    - Re-test MPU9150 driver after modifications. All but the tests picture a slight miss of the timings. This can be further inspected.
    - MPU6000 SPI driver tested through the ardupilot/libraries/AP_InertialSensor/examples/MPU6000 test example. 

- Issues:
    - RT_PREEMPT kernel and PRU seem to conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). 
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.

- Plans for the next period (this is a list of tasks for the author):
    - Code kernel drivers. Start checking the MPU6000. The MS5611 could be started from the BMP085 driver.
    - Modify the I2C driver to accept a bus number
    - Review the RT_PREEMPT issue.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test the new DT (waiting for Anuj)
    - Test all the drivers (needs the DT)
    - Test GPS hardware.
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.
    - Review the possibility of creating a RCOutput code that relies on the eHRPWM instead.


Second Week
------

- What has been accomplished?:
    - I2CDriver updated. 
    - Xenomai kernel and modules deployed. The Xenomai kernel doesn't suffer from the errors that the RT_PREEMPT does.
    - PWM generation using the PRU driver tested. Refer to [this post](http://erlerobot.com/blog/beaglepilot-testing-pwm-pru/).
    - Tested the RCOutput Linux layer. Seem to work fine.
    - RCOuput Software and Hardware tested together. RCOutput works fine. Several SimonK firmware ESCs work perfectly with the AP_Linux_HAL.
    - AP_Motors tested with Erle Robot. Refer to https://www.youtube.com/watch?v=7J2JYUvwl-4.

- Issues:
    - RT_PREEMPT kernel and PRU seem to conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals).
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.
    - Issue with the overlays. PRU and BB-SPI1-SWP-01 conflict.

- Plans for the next period (this is a list of tasks for the author):
    - Fix the old CS select method (MPU6K).
    - Compile vanilla kernel
    - Write down in a post the conclussions from the RT_PREEMPT analysis. Use the information from this post https://groups.google.com/forum/#!topic/beagleboard/gJ_iFT2IwEQ.
    - Modify drivers according to the new GPIO layer. Test them.
    - Code CS according to tridge's comments.
    - Modify the I2C driver to accept a bus number
    - Test the performances using the logs. Refer to https://groups.google.com/forum/#!topic/drones-discuss/7DKcdm0AEPo
    - Review the PREEMPT_RT bug.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Code kernel drivers. Start checking the MPU6000. The MS5611 could be started from the BMP085 driver.
    - Test the new DT (waiting for Anuj)
    - Test all the drivers (needs the DT)
    - Test GPS hardware.
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.
    - Review the possibility of creating a RCOutput code that relies on the eHRPWM instead.


Third Week
------

- What has been accomplished?:
    - Preliminary RT tests with rt-tests (http://git.kernel.org/pub/scm/linux/kernel/git/clrkwllms/rt-tests.git/) available [here](http://git.kernel.org/pub/scm/linux/kernel/git/clrkwllms/rt-tests.git/).
    - Enable and check CS scripts created. Available [here](https://gist.github.com/vmayoral/5b5fe683bacecdc710f7).
    - Video showing two working tests with the SPI sensors https://www.youtube.com/watch?v=sXsauhNKwdc.
    - SPI CS capabilities implemmented in the ardupilot AP_HAL_Linux layer.
    - Video picturing the chip select (CS) capabilities integrated in BeaglePilot https://www.youtube.com/watch?v=W70Erro1A5Y&feature=youtu.be
    - Tests with MPU6000 kernel module https://groups.google.com/forum/#!topic/drones-discuss/CiVyGNVFqsE. 
    - Real-Time evaluation with 4 kernels. Results published http://erlerobot.com/blog/beaglepilot-cyclictests-different-kernels/.
    - Issue with the overlays fixed by Sid. 

- Issues:
    - RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.
    - SPI Barometer and IMU run fine separately. When used together with ArduCopter the Baro crashes. Refer to https://groups.google.com/forum/#!topic/drones-discuss/pokYZT4wYvs.

- Plans for the next period (this is a list of tasks for the author):
    - Go through Tridge and Roberto's comments for the MS5611.
    - Look at the SPI MS5611 behaviour with ArduCopter.
    - Flight tests
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the drivers
    - Test GPS hardware.
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.
    - Review the possibility of creating a RCOutput code that relies on the eHRPWM instead.

Fourth Week
------

- What has been accomplished?:
    - SPIDriver updated
    - ardupilot code now working :). https://www.youtube.com/watch?v=duaSfuF_QbA&feature=youtu.be
    - First tests with MAVProxy https://gist.github.com/vmayoral/d48f94b2f5bcc6289b99
    - MAVProxy interfaced with the BeagleBone http://diydrones.com/profiles/blogs/beaglepilot-mavproxy-connection-now-working.
    - Tested new PRU PWM method via mmap with ESCs and motors.
    - Added FRAM to the SPIDriver.
    - Coded UART-like TCP sockets. Needs still some debugging.

- Issues:
    - RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.
    - For some reason ArduCopter CLI works great when launched at ttyO4 while not in ttyO5. Probably some hardware related issue


- Plans for the next period (this is a list of tasks for the author):
    - mavlink_ros
    - Set up SITL in the BBB
    - Flight tests
    - Correct LSM using tridge's comments https://groups.google.com/forum/#!topic/drones-discuss/tIKbvIsWg1o
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the drivers
    - Test GPS hardware.
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.
    - Review the possibility of creating a RCOutput code that relies on the eHRPWM instead.

Fifth Week
------

- What has been accomplished?:
    - UART-like TCP sockets coded.
    - MAVLink introduction http://erlerobotics.gitbooks.io/erlerobot/en/mavlink.html.
    - MAVProxy introduction http://erlerobotics.gitbooks.io/erlerobot/en/mavproxy.html.
    - ROS short-reminder http://erlerobotics.gitbooks.io/erlerobot/en/rostutorials.html
    - ROS integrations different methods installed http://erlerobotics.gitbooks.io/erlerobot/en/mavlinkros.html
        - `mavlink_ros`
        - `autopilot_bridge`
        - `mavros`
        - `roscopter`


- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) ArduPlane makes the board gets stucked. A lot of messages with:
            RCOutput: PWM Write Failed!
            RCOutput: PWM Write Failed!
            RCOutput: PWM Write Failed!
            ...
    - (* out-of-gsoc-scope *) UART-like TCP sockets https://www.youtube.com/watch?v=fuiyHRnx2LU
    - (* out-of-gsoc-scope *) var SERVO_OUTPUT_RAW always with the same value

- Plans for the next period (this is a list of tasks for the author):
    - Evaluate and compare the different ROS integration mechanisms (mavlink_ros, autopilot_bridge, mavros)
    - Review SERVO_OUTPUT_RAW, RCInput and RCOutput.
    - testing MS5611 kernel driver
    - Data from http://uav.tridgell.net/BeaglePilot grab the csv
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Correct LSM using tridge's comments https://groups.google.com/forum/#!topic/drones-discuss/tIKbvIsWg1o
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the other drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.

Sixth Week
------

- What has been accomplished?:
    - Joined a group effort to create a ROS Micro Air Vehicle Joint Standard API https://docs.google.com/document/d/11ZwqL-NcykNdWGy9333ETJoiNyxBO6z2f9NIVAfcTFo/edit?usp=sharing
    - SYS_BOOT pins of the PXF evaluated. An eventual option could be to remove two of the level translators (the ones taking care of generating ch5-13 from the PRU and UART4 and UART5.
    - UART-like TCP sockets finally fixed. Refer to https://github.com/BeaglePilot/ardupilot/commit/26476dc14832d2c89110ae79d68d2884b5ed97b0
    - Corrections to UARTDriver



- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) ArduPlane makes the board gets stucked. A lot of messages with:
            RCOutput: PWM Write Failed!
            RCOutput: PWM Write Failed!
            RCOutput: PWM Write Failed!
    - (* out-of-gsoc-scope *) var SERVO_OUTPUT_RAW always with the same value
    - (* out-of-gsoc-scope *) Serial connection (through ttyO*) doesn't work the first time (e.g. if arducopter started from ttyO4 and mavproxy from ttyO5, first time doesn't work, weird characters appeared. If the connection is launched the other way arducopter ttyO5 and mavproxy from ttyO4 then it works). Needs to be further inspected.
    - (* out-of-gsoc-scope *) SYS_BOOT pins of the BBB conflict with PixFire Hawk Cape design

- Plans for the next period (this is a list of tasks for the author):
    - Evaluate and compare the different ROS integration mechanisms (mavlink_ros, autopilot_bridge, mavros)
    - Review SERVO_OUTPUT_RAW, RCInput and RCOutput.
    - testing MS5611 kernel driver
    - Data from http://uav.tridgell.net/BeaglePilot grab the csv
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Correct LSM using tridge's comments https://groups.google.com/forum/#!topic/drones-discuss/tIKbvIsWg1o
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the other drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.

Questions for the meeting:
    - "height" messages?
    - LOOP speed in param?
