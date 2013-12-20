# eMPL

This is the Invensense Embedded MotionDriver v5.1 downloadable from the
Invensense site.


The code is taken from this directory of the extracted SDK

        Embedded_MotionDriver_5.1/core/driver/eMPL


The changes are minor to only 3 of the files as shown by the diff below

        scott@hex:~/linux-mpu9150$ diff -cs eMPL-orig eMPL

        Files eMPL-orig/dmpKey.h and eMPL/dmpKey.h are identical

        Files eMPL-orig/dmpmap.h and eMPL/dmpmap.h are identical

        diff -cs eMPL-orig/inv_mpu.c eMPL/inv_mpu.c
        *** eMPL-orig/inv_mpu.c	2013-04-05 07:39:08.846417371 -0400
        --- eMPL/inv_mpu.c	2013-04-02 11:14:06.438537201 -0400
        ***************
        *** 101,106 ****
        --- 101,108 ----
          /* UC3 is a 32-bit processor, so abs and labs are equivalent. */
          #define labs        abs
          #define fabs(x)     (((x)>0)?(x):-(x))
        + #elif defined EMPL_TARGET_LINUX
        + #include "linux_glue.h"
          #else
          #error  Gyro driver is missing the system layer implementations.
          #endif

        diff -cs eMPL-orig/inv_mpu_dmp_motion_driver.c eMPL/inv_mpu_dmp_motion_driver.c
        *** eMPL-orig/inv_mpu_dmp_motion_driver.c	2013-04-05 07:39:08.846417371 -0400
        --- eMPL/inv_mpu_dmp_motion_driver.c	2013-04-02 11:14:06.442537201 -0400
        ***************
        *** 62,67 ****
        --- 62,70 ----
          #define log_i       MPL_LOGI
          #define log_e       MPL_LOGE
          
        + #elif defined EMPL_TARGET_LINUX
        + #include "linux_glue.h"
        + 
          #else
          #error  Gyro driver is missing the system layer implementations.
          #endif

        Files eMPL-orig/inv_mpu_dmp_motion_driver.h and eMPL/inv_mpu_dmp_motion_driver.h are identical

        diff -cs eMPL-orig/inv_mpu.h eMPL/inv_mpu.h
        *** eMPL-orig/inv_mpu.h	2013-04-05 07:39:08.846417371 -0400
        --- eMPL/inv_mpu.h	2013-04-02 11:14:06.438537201 -0400
        ***************
        *** 38,43 ****
        --- 38,45 ----
              unsigned long pin;
              void (*cb)(volatile void*);
              void *arg;
        + #elif defined EMPL_TARGET_LINUX
        + 	unsigned int pin;
          #endif
          };

