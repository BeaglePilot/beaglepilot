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
| MPU-9250 (SPI) userspace driver | Working |
| LSM9DS0 (SPI) userspace driver | Coded |
| PRU PWM | Working |
| Realtime Comparison | Working (Done) |
| ROS tests with `mavlink_ros` | Working |
| ROS - ardupilot packages evaluated | Working |
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
    - Evaluated performance of the autopilot with different working rates (param set SCHED_DEBUG 1):
        + 400 Hz: PERF: 3998/4000 8807
        + 100 Hz: PERF: 0/1000 10317
    - Attitude evaluation started. y axis seems inverted. https://groups.google.com/forum/#!topic/drones-discuss/R2u0j-QCUe8
    - ROS-BeaglePilot(ArduPilot) alternatives studied at http://erlerobotics.gitbooks.io/erlerobot/en/mavlink/mavlinkros.html
    - Erle-board compared with HKPilot. Results show that:
        - RAW_IMU:
            + gyro and acel values seem to match expcept the z-axis
            + same axis in both boards
            + BeaglePilot has issues with the acel offsets
        - Attitude
            + rollspeed seems to be good
            + pitchspeed not so different
            + yawspeed, roll, pitch and yaw are different

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
    - (* out-of-gsoc-scope *) Issues with the attitude estimation in BeaglePilot

- Plans for the next period (this is a list of tasks for , roll, pitch and yaw are differentthe author):
    - Look up the attitude issue. Verify the data from various sensors and try bringing up conclussions.
    - tests Sids commit with the scope
    - testing MS5611 kernel driver
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Correct LSM using tridge's comments https://groups.google.com/forum/#!topic/drones-discuss/tIKbvIsWg1o
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the other drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.


Seventh Week
------

- What has been accomplished?:
    - `mavros` compiled. Necessary to uptade to hydro and compile manually mavlink ROS package.
    - IMU values reviewed after patches. Looking better
    - SYS_BOOT pins issue addressed in Erle's board.
    - More progress on the ROS integration side. http://erlerobotics.gitbooks.io/erlerobot/en/mavlink/ros/mavros.html
        From what has been tested so far it seem that `mavros` and `autopilot_bridge` are quite promising. Good reasoning on the decisions made is available at https://groups.google.com/forum/#!searchin/drones-discuss/ROS/drones-discuss/o7Z5UWlpMlQ/54X0cv5oaSAJ. The trend is to push forward a smarter ROS<->mavlink adapter.
    - `mavlink` catkin ROS package .deb generated and pushed to https://github.com/vmayoral/ros-stuff/tree/master/deb

- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) Commit [3c4062a7961a70b6ec46266d265d322ac0b9dd8f](https://github.com/BeaglePilot/ardupilot/commit/3c4062a7961a70b6ec46266d265d322ac0b9dd8f) creates conflicts with the ESCs tested.

- Plans for the next period (this is a list of tasks for , roll, pitch and yaw are differentthe author):
    - (tridge) why MPU6000 is giving erratic data on accels. I suspect a driver bug, or hw fault (eg. bad power to MPU6k). We're going to have to start looking with a scope and analysing the SPI traffic to narrow it down
    - Push forward the LSM driver. Take into account tridge's comments https://groups.google.com/forum/#!topic/drones-discuss/tIKbvIsWg1o
    - tests Sids commit with the scope
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the other drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.

Things to fix/Questions for the meeting:
    ok - "height" messages?. Seem to be bad baro stuff. "set altreadout 0" can do it. Put it in the startup script
    - APM PreARM: RC Not Calibrated (message got when arm throttle)
    - meaning of ATTITUDE values? 
    - what's the deal with the logs?


Eighth Week
------

- What has been accomplished?:
    - Reviewed driver from ST http://www.st.com/web/en/catalog/tools/FM147/CL1818/SC1885?sc=mems-drivers. All of the provided ones are I2C-based. According to tridge the impl can be based on a mixture between lsm303d and l3gd20 but the first one is not implemmented in APM.
    - MPU6K AHRS evaluated https://www.youtube.com/watch?v=QoPwKTos7B4&feature=youtu.be
    - MPU6K further inspected http://erlerobot.com/blog/beaglepilot-comparing-erle-board-apm2/
    - Storage and logs fixed. Refer to commits 0a682383cd23d7b93fefa3ca1584ce989a68320b and posteriors.
    - Support added for MPU9250
    - Problems with MPU6000 narrowed down. It seems the issues are hardware related. Probably some capacitors should be changes in the design.
    - PXF received and set up. 
    - ROS installed in Debian http://erlerobotics.gitbooks.io/erlerobot/en/ros/tutorials/rosinstall.html


- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) Commit [3c4062a7961a70b6ec46266d265d322ac0b9dd8f](https://github.com/BeaglePilot/ardupilot/commit/3c4062a7961a70b6ec46266d265d322ac0b9dd8f) creates conflicts with the ESCs tested.
    - (* out-of-gsoc-scope *) APM2 doesn't compile with BeaglePilot/ardupilot code. Something broke down
    - (* out-of-gsoc-scope *) Issue with the IMU sensor MPU6000. Caps need to be changed according to datasheet.
    - (* out-of-gsoc-scope *) Issue with PWM generation. 


- Plans for the next period (this is a list of tasks for , roll, pitch and yaw are differentthe author):
    - Reinstall all the ROS-ardupilot related packages in Debian.
    - Push forward the LSM driver. Take into account tridge's comments https://groups.google.com/forum/#!topic/drones-discuss/tIKbvIsWg1o. Review the registers configuration.
    - Look at the  lsm303d and l3gd20 drivers in the PX4Firmware tree See https://github.com/diydrones/PX4Firmware
    - orientation fix
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test all the other drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.

Things to fix/Questions for the meeting:

Ninth Week
------

- What has been accomplished?:
    - PWM checked. Works fine after modifications but AP_Motor_tests doesn't work properly.
    - Tested the WHO_AM_I of the different sensors: https://gist.github.com/vmayoral/502da526bd7b81b0f3d6. LSM doesn't seem to respond.
    - Issue detected with MPU9250 with new firmware. Gyros not responding. Tried different bus rates, same result. NOTE: When the low speed is set below 1 GHz the sensor doesn't even seem to respond.
    - Power down issue when connecting/disconnecting batteries. Refer to the issue description
    - Issue with ROS installation in Debian when reproducing http://answers.ros.org/question/186643/ros-debian-in-the-bbb/. Answered in the thread, solution was using a different way of installing the packages than the one described in the official docs.. Answered in the thread, solution was using a different way of installing the packages than the one described in the official docs.
    - ROS installed in Debian. Refer to http://erlerobotics.gitbooks.io/erlerobot/en/ros/tutorials/rosinstall.html


- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) Commit [3c4062a7961a70b6ec46266d265d322ac0b9dd8f](https://github.com/BeaglePilot/ardupilot/commit/3c4062a7961a70b6ec46266d265d322ac0b9dd8f) creates conflicts with the ESCs tested.
    - (* out-of-gsoc-scope *) Issue with the IMU sensor MPU6000. Caps need to be changed according to datasheet.
    - (* out-of-gsoc-scope *) Issue with the IMU sensor MPU9250. Gyros not responding. Seems to be a hardware issue.
    - (* out-of-gsoc-scope *) BBB spuriously shutsdown as if power button is pressed when connecting/disconnecting batteries. Related to http://bugs.elinux.org/issues/85. Can be dealt removing acpid.
    - Issue with the Language in Debian "-bash: warning: setlocale: LC_ALL: cannot change locale (en_GB.utf8)". For now fixed with https://gist.github.com/vmayoral/44d6d9f93ac4504f711b


- Plans for the next period:
    - Look at the  lsm303d and l3gd20 drivers in the PX4Firmware tree See https://github.com/diydrones/PX4Firmware
    - Rework the 9250
    (tridge) i think we should re-work the 9250 driver to use the time based wait_for_sample(), add the dual-pole filtering and try sampling at 1KHz
    (tridge) that will raise the SPI load a lot (by factor of 5x), but should reduce the time spent in wait_for_sample()
    (tridge) to make that work we'll need to change LinuxScheduler::_timer_thread() to not drift in time
    (tridge) right now it just does _microsleep(1000) between calls
    (tridge) it will need to instead have a "next_timer_tick" and sleep the right number of microseconds for that deadline
    (tridge) that will be needed to ensure we don't lose any ticks, and that we average 1kHz
    (tridge) later I think we'll need a thread per SPI bus, with an API to ask for regular transfers
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.

Things to fix/Questions for the meeting:

Tenth Week
------

- What has been accomplished?:
    - Code merged with with ardupilot. From this point and periodically progresses will be merged there.
    - l3gd20 userspace driver coded https://github.com/BeaglePilot/ardupilot/commit/d62cd263cc10d8fb182ae39e44475fd5627a5cb8
    - hardware issues on the PXF notified https://github.com/diydrones/PXF/issues?state=open
    - separate l3gd20 from the traditional AP_InertialSensor line
    - started coding lsm303d


- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) Commit [3c4062a7961a70b6ec46266d265d322ac0b9dd8f](https://github.com/BeaglePilot/ardupilot/commit/3c4062a7961a70b6ec46266d265d322ac0b9dd8f) creates conflicts with the ESCs tested.
    - (* out-of-gsoc-scope *) Issue with the IMU sensor MPU9250. Gyros not responding. Seems to be a hardware issue.
    - (* out-of-gsoc-scope *) BBB spuriously shutsdown as if power button is pressed when connecting/disconnecting batteries. Related to http://bugs.elinux.org/issues/85. Can be dealt removing acpid.
    - (* out-of-gsoc-scope *) Seems that the PXFs capes are in a bad shape so we might need to redo them.


- Plans for the next period:
    - Review l3gd20 and lsm303d implementations. Code the LSM9D on top of these two.
    - Documentation and tutorials.
    - Prepare final material to be submitted.

    - (* out-of-gsoc-scope *) GSOC scope probably won't allow to include these tasks. Still they will be implemented and the project will keep evolving through diydrones/ardupilot repository.
    - Rework the MPU9250
    (tridge) i think we should re-work the 9250 driver to use the time based wait_for_sample(), add the dual-pole filtering and try sampling at 1KHz
    (tridge) that will raise the SPI load a lot (by factor of 5x), but should reduce the time spent in wait_for_sample()
    (tridge) to make that work we'll need to change LinuxScheduler::_timer_thread() to not drift in time
    (tridge) right now it just does _microsleep(1000) between calls
    (tridge) it will need to instead have a "next_timer_tick" and sleep the right number of microseconds for that deadline
    (tridge) that will be needed to ensure we don't lose any ticks, and that we average 1kHz
    (tridge) later I think we'll need a thread per SPI bus, with an API to ask for regular transfers
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.

Things to fix/Questions for the meeting:


Eleventh Week
------

- What has been accomplished?:
    - Finished coding lsm303d
    - Docs starting to shape up at http://erlerobotics.gitbooks.io/erlerobot/en/beaglepilot/BeaglePilot.html


- Issues:
    - (* out-of-gsoc-scope *) RT_PREEMPT kernel and capemgr conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo). The Xenomai kernel doesn't suffer from these errors. For now the RT_PREEMPT issue is left asside to continue with the goals (not within the GSOC goals). The capemgr won't be use in the longer term thereby we skip the issue.
    - (* out-of-gsoc-scope *) Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    -  (* out-of-gsoc-scope *) I2C Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - (* out-of-gsoc-scope *) Issue when used with MAVProxy, probably related to the fact that RCin hasn't been reviewed yet.
    - (* out-of-gsoc-scope *) Commit [3c4062a7961a70b6ec46266d265d322ac0b9dd8f](https://github.com/BeaglePilot/ardupilot/commit/3c4062a7961a70b6ec46266d265d322ac0b9dd8f) creates conflicts with the ESCs tested.
    - (* out-of-gsoc-scope *) Issue with the IMU sensor MPU9250. Gyros not responding. Seems to be a hardware issue.
    - (* out-of-gsoc-scope *) BBB spuriously shutsdown as if power button is pressed when connecting/disconnecting batteries. Related to http://bugs.elinux.org/issues/85. Can be dealt removing acpid.
    - (* out-of-gsoc-scope *) Seems that the PXFs capes are in a bad shape so we might need to redo them.


- Plans for the next period:
    - Documentation and tutorials.
    - Prepare final material to be submitted.

- Out of the scope:
    - (* out-of-gsoc-scope *) GSOC scope probably won't allow to include these tasks. Still they will be implemented and the project will keep evolving through diydrones/ardupilot repository.
    - Rework the MPU9250
    (tridge) i think we should re-work the 9250 driver to use the time based wait_for_sample(), add the dual-pole filtering and try sampling at 1KHz
    (tridge) that will raise the SPI load a lot (by factor of 5x), but should reduce the time spent in wait_for_sample()
    (tridge) to make that work we'll need to change LinuxScheduler::_timer_thread() to not drift in time
    (tridge) right now it just does _microsleep(1000) between calls
    (tridge) it will need to instead have a "next_timer_tick" and sleep the right number of microseconds for that deadline
    (tridge) that will be needed to ensure we don't lose any ticks, and that we average 1kHz
    (tridge) later I think we'll need a thread per SPI bus, with an API to ask for regular transfers
    - Implement in the UART-like TCP sockets the "*" option.
    - Flight tests (play around with RCInput in AP_HAL_Linux, ask Anuj about status)
    - Finish up the I2C driver to accept a bus number. Multi-i2c-aware driver.
    - Make the drivers platform agnostic.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.
