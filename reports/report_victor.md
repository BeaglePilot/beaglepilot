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
| PRU PWM | WIP |
| Realtime Comparison | TBD |
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


May 19th - May 25th
------

- What has been accomplished?:
    - Tested PRU PWM in (not patched) kernel. Working good.
    - Issue between PRU and RT_PREEMPT kernel detected.
    - Re-test MPU9150 driver after modifications. All but the tests picture a slight miss of the timings. This can be further inspected.

- Issues:
    - RT_PREEMPT kernel and PRU seem to conflict. Documented [here](http://erlerobot.com/blog/beaglepilot-stone-road-pru-rt_preempt-patch/). Dicussion about this topic [here](https://groups.google.com/forum/#!topic/beaglepilot/7DKcdm0AEPo).
    - Issue with the MPU9150 sensor driver. Refer to [this fix](https://github.com/BeaglePilot/ardupilot/commit/400f71226e0828d2ea285a469b566e25b8b5a7db).
    - Barometer MS5611 not detected. Seems like a hardware/design issue. Present both in the robot Erle and the PXF. 
    - Issue with the GCS parameters (refer to https://groups.google.com/forum/#!topic/beaglepilot/dQlxse11JNI). There's also the UARTDriver to be checked.

- Plans for the next period:
    - Set up a Xenomai-patched Linux kernel and test whether there're issues with it as with the RT_PREEMPT one.
    - Review the possibility of creating a RCOutput code that relies on the eHRPWM instead.
    - Check Andrew's patch with new ideas for I2CDriver.
    - Modify the I2C driver to accept a bus number
    - Share progresses with I2C sensors. Publish material. Wire up the 10 DOF boards received and make some tests.
    - Code AP_InertialSensor/AP_InertialSensor_Linux.cpp driver which acts as a front end for multiple hardware drivers
    - Test the new DT (waiting for Anuj)
    - Test all the drivers (needs the DT)
    - Ideas about the new AP_HAL_Linux (using dedicted threads for each SPI, etc.). Discuss in more detail with @tridge.
