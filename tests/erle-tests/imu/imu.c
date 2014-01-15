////////////////////////////////////////////////////////////////////////////
//
//  This file is part of linux-mpu9150
//
//  Copyright (c) 2013 Pansenti, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of 
//  this software and associated documentation files (the "Software"), to deal in 
//  the Software without restriction, including without limitation the rights to use, 
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
//  Software, and to permit persons to whom the Software is furnished to do so, 
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all 
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <errno.h>

#include "mpu9150.h"
#include "linux_glue.h"
#include "local_defaults.h"

int set_cal(int mag, char *cal_file);
void read_loop(unsigned int sample_rate);
void print_fused_euler_angles(mpudata_t *mpu);
void print_fused_quaternion(mpudata_t *mpu);
void print_calibrated_accel(mpudata_t *mpu);
void print_calibrated_mag(mpudata_t *mpu);
void register_sig_handler();
void sigint_handler(int sig);

int read_rawGyro(short* gyroX, short* gyroY, short* gyroZ);
int read_rawAccel(short* accelX, short* accelY, short* accelZ);
int read_rawQuat(long* quat1, long* quat2, long* quat3, long* quat4);
int read_dmpTimestamp(unsigned long* dmpTimestamp);
int read_rawMag(short* magX, short* magY, short* magZ);
int read_magTimestamp(unsigned long* magTimestamp);
int read_calibratedAccel(short* calibratedAccelX, short* calibratedAccelY, short* calibratedAccelZ);
int read_calibratedMag(short* calibratedMagX, short* calibratedMagY, short* calibratedMagZ);
int read_fusedQuat(float* quat1, float* quat2, float* quat3, float* quat4);
int read_fusedEuler(float* fusedX, float* fusedY, float* fusedZ);
int read_lastDMPYaw(float* lastDMPYaw);
int read_lastYaw(float* lastYaw);
//TODO: Eventually substitute this last function for one that makes use of
// a ctypes Structure for mpudata_t
int read_mpudata_t(short* gyroX, short* gyroY, short* gyroZ, short* accelX, short* accelY, short* accelZ,
					long* quat1, long* quat2, long* quat3, long* quat4, unsigned long* dmpTimestamp,
					short* magX, short* magY, short* magZ, unsigned long* magTimestamp, 
					short* calibratedAccelX, short* calibratedAccelY, short* calibratedAccelZ,
					short* calibratedMagX, short* calibratedMagY, short* calibratedMagZ,
					float* quat1, float* quat2, float* quat3, float* quat4, 
					float* fusedX, float* fusedY, float* fusedZ, float* lastDMPYaw, float* lastYaw);


int done;

// ----------------------------------

int read_rawGyro(short* gyroX, short* gyroY, short* gyroZ){
        mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
                /*
                printf("\rX: %d, Y: %d Z: %d        \n",
                        mpu.rawGyro[0],
                        mpu.rawGyro[1],
                        mpu.rawGyro[2]);
                */
                *gyroX = (mpu.rawGyro[VEC3_X]);
                *gyroY = (mpu.rawGyro[VEC3_Y]);
                *gyroZ = (mpu.rawGyro[VEC3_Z]);
                return 0;
        }
        return -1;
}

int read_rawAccel(short* accelX, short* accelY, short* accelZ){
        mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                printf("\rX: %d, Y: %d Z: %d        \n",
                        mpu.rawAccel[0],
                        mpu.rawAccel[1],
                        mpu.rawAccel[2]);
                */
                *accelX = (mpu.rawAccel[VEC3_X]);
                *accelY = (mpu.rawAccel[VEC3_Y]);
                *accelZ = (mpu.rawAccel[VEC3_Z]);
                return 0;
        }
        return -1;
}

int read_rawQuat(long* quat1, long* quat2, long* quat3, long* quat4){
        mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                printf("\rQ1: %d, Q2: %d Q3: %d, Q4: %d  \n",
                        mpu.rawQuat[0],
                        mpu.rawQuat[1],
                        mpu.rawQuat[2],
                        mpu.rawQuat[3]);
                */
                *quat1 = (mpu.rawQuat[QUAT_W]);
                *quat2 = (mpu.rawQuat[QUAT_X]);
                *quat3 = (mpu.rawQuat[QUAT_W]);
                *quat4 = (mpu.rawQuat[QUAT_Z]);

                return 0;
        }
        return -1;
}

int read_dmpTimestamp(unsigned long* dmpTimestamp){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *dmpTimestamp = (mpu.dmpTimestamp);
                return 0;
        }
        return -1;
}

int read_rawMag(short* magX, short* magY, short* magZ){
        mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *magX = (mpu.rawMag[VEC3_X]);
                *magY = (mpu.rawMag[VEC3_Y]);
                *magZ = (mpu.rawMag[VEC3_Z]);
                return 0;
        }
        return -1;
}

int read_magTimestamp(unsigned long* magTimestamp){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *magTimestamp = (mpu.magTimestamp);
                return 0;
        }
        return -1;
}

int read_calibratedAccel(short* calibratedAccelX, short* calibratedAccelY, short* calibratedAccelZ){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *calibratedAccelX = (mpu.calibratedAccel[VEC3_X]);
                *calibratedAccelY = (mpu.calibratedAccel[VEC3_Y]);
                *calibratedAccelZ = (mpu.calibratedAccel[VEC3_Z]);
                return 0;
        }
        return -1;
}

int read_calibratedMag(short* calibratedMagX, short* calibratedMagY, short* calibratedMagZ){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *calibratedMagX = (mpu.calibratedMag[VEC3_X]);
                *calibratedMagY = (mpu.calibratedMag[VEC3_Y]);
                *calibratedMagZ = (mpu.calibratedMag[VEC3_Z]);
                return 0;
        }
        return -1;
}

int read_fusedQuat(float* fusedQuat1, float* fusedQuat2, float* fusedQuat3, float* fusedQuat4){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *fusedQuat1 = (mpu.fusedQuat[QUAT_W]);
                *fusedQuat2 = (mpu.fusedQuat[QUAT_X]);
                *fusedQuat3 = (mpu.fusedQuat[QUAT_Y]);
                *fusedQuat4 = (mpu.fusedQuat[QUAT_Z]);
                return 0;
        }
        return -1;
}

int read_fusedEuler(float* fusedX, float* fusedY, float* fusedZ){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *fusedX = (mpu.fusedEuler[VEC3_X]* RAD_TO_DEGREE);
                *fusedY = (mpu.fusedEuler[VEC3_Y]* RAD_TO_DEGREE);
                *fusedZ = (mpu.fusedEuler[VEC3_Z]* RAD_TO_DEGREE);
                return 0;
        }
        return -1;
}

int read_lastDMPYaw(float* lastDMPYaw){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *lastDMPYaw = (mpu.lastDMPYaw);
                return 0;
        }
        return -1;
}

int read_lastYaw(float* lastYaw){
       	mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
        		/*
                */
                *lastYaw = (mpu.lastYaw);
                return 0;
        }
        return -1;
}

/* Pass all the parameters */
int read_mpudata_t(short* gyroX, short* gyroY, short* gyroZ, short* accelX, short* accelY, short* accelZ,
					long* quat1, long* quat2, long* quat3, long* quat4, unsigned long* dmpTimestamp,
					short* magX, short* magY, short* magZ, unsigned long* magTimestamp, 
					short* calibratedAccelX, short* calibratedAccelY, short* calibratedAccelZ,
					short* calibratedMagX, short* calibratedMagY, short* calibratedMagZ,
					float* fusedQuat1, float* fusedQuat2, float* fusedQuat3, float* fusedQuat4,
					float* fusedX, float* fusedY, float* fusedZ, float* lastDMPYaw, float* lastYaw){

        mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));
        if (mpu9150_read(&mpu) == 0) {
                /*
                */
                *gyroX = (mpu.rawGyro[VEC3_X]);
                *gyroY = (mpu.rawGyro[VEC3_Y]);
                *gyroZ = (mpu.rawGyro[VEC3_Z]);
                *accelX = (mpu.rawAccel[VEC3_X]);
                *accelY = (mpu.rawAccel[VEC3_Y]);
                *accelZ = (mpu.rawAccel[VEC3_Z]);
                *quat1 = (mpu.rawQuat[QUAT_W]);
                *quat2 = (mpu.rawQuat[QUAT_X]);
                *quat3 = (mpu.rawQuat[QUAT_W]);
                *quat4 = (mpu.rawQuat[QUAT_Z]);
                *dmpTimestamp = (mpu.dmpTimestamp);
                *magX = (mpu.rawMag[VEC3_X]);
                *magY = (mpu.rawMag[VEC3_Y]);
                *magZ = (mpu.rawMag[VEC3_Z]);
                *magTimestamp = (mpu.magTimestamp);
                *calibratedAccelX = (mpu.calibratedAccel[VEC3_X]);
                *calibratedAccelY = (mpu.calibratedAccel[VEC3_Y]);
                *calibratedAccelZ = (mpu.calibratedAccel[VEC3_Z]);
                *calibratedMagX = (mpu.calibratedMag[VEC3_X]);
                *calibratedMagY = (mpu.calibratedMag[VEC3_Y]);
                *calibratedMagZ = (mpu.calibratedMag[VEC3_Z]);
                *fusedQuat1 = (mpu.fusedQuat[QUAT_W]);
                *fusedQuat2 = (mpu.fusedQuat[QUAT_X]);
                *fusedQuat3 = (mpu.fusedQuat[QUAT_Y]);
                *fusedQuat4 = (mpu.fusedQuat[QUAT_Z]);
                *fusedX = (mpu.fusedEuler[VEC3_X]* RAD_TO_DEGREE);
                *fusedY = (mpu.fusedEuler[VEC3_Y]* RAD_TO_DEGREE);
                *fusedZ = (mpu.fusedEuler[VEC3_Z]* RAD_TO_DEGREE);
                *lastDMPYaw = (mpu.lastDMPYaw);
                *lastYaw = (mpu.lastYaw);
                return 0;
        }
        return -1;	
}

// ----------------------------------

void usage(char *argv_0)
{
	printf("\nUsage: %s [options]\n", argv_0);
	printf("  -b <i2c-bus>          The I2C bus number where the IMU is. The default is 1 to use /dev/i2c-1.\n");
	printf("  -s <sample-rate>      The IMU sample rate in Hz. Range 2-50, default 10.\n");
	printf("  -y <yaw-mix-factor>   Effect of mag yaw on fused yaw data.\n");
	printf("                           0 = gyro only\n");
	printf("                           1 = mag only\n");
	printf("                           > 1 scaled mag adjustment of gyro data\n");
	printf("                           The default is 4.\n");
	printf("  -a <accelcal file>    Path to accelerometer calibration file. Default is ./accelcal.txt\n");
	printf("  -m <magcal file>      Path to mag calibration file. Default is ./magcal.txt\n");
	printf("  -v                    Verbose messages\n");
	printf("  -h                    Show this help\n");

	printf("\nExample: %s -b3 -s20 -y10\n\n", argv_0);
	
	exit(1);
}

int main(int argc, char **argv)
{
	int opt, len;
	int i2c_bus = DEFAULT_I2C_BUS;
	int sample_rate = DEFAULT_SAMPLE_RATE_HZ;
	int yaw_mix_factor = DEFAULT_YAW_MIX_FACTOR;
	int verbose = 0;
	char *mag_cal_file = NULL;
	char *accel_cal_file = NULL;

	while ((opt = getopt(argc, argv, "b:s:y:a:m:vh")) != -1) {
		switch (opt) {
		case 'b':
			i2c_bus = strtoul(optarg, NULL, 0);
			
			if (errno == EINVAL)
				usage(argv[0]);
			
			if (i2c_bus < MIN_I2C_BUS || i2c_bus > MAX_I2C_BUS)
				usage(argv[0]);

			break;
		
		case 's':
			sample_rate = strtoul(optarg, NULL, 0);
			
			if (errno == EINVAL)
				usage(argv[0]);
			
			if (sample_rate < MIN_SAMPLE_RATE || sample_rate > MAX_SAMPLE_RATE)
				usage(argv[0]);

			break;

		case 'y':
			yaw_mix_factor = strtoul(optarg, NULL, 0);
			
			if (errno == EINVAL)
				usage(argv[0]);
			
			if (yaw_mix_factor < 0 || yaw_mix_factor > 100)
				usage(argv[0]);

			break;

		case 'a':
			len = 1 + strlen(optarg);

			accel_cal_file = (char *)malloc(len);

			if (!accel_cal_file) {
				perror("malloc");
				exit(1);
			}

			strcpy(accel_cal_file, optarg);
			break;

		case 'm':
			len = 1 + strlen(optarg);

			mag_cal_file = (char *)malloc(len);

			if (!mag_cal_file) {
				perror("malloc");
				exit(1);
			}

			strcpy(mag_cal_file, optarg);
			break;

		case 'v':
			verbose = 1;
			break;

		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	register_sig_handler();

	mpu9150_set_debug(verbose);

	if (mpu9150_init(i2c_bus, sample_rate, yaw_mix_factor))
		exit(1);

	set_cal(0, accel_cal_file);
	set_cal(1, mag_cal_file);

	if (accel_cal_file)
		free(accel_cal_file);

	if (mag_cal_file)
		free(mag_cal_file);

	read_loop(sample_rate);

	mpu9150_exit();

	return 0;
}

void read_loop(unsigned int sample_rate)
{
	unsigned long loop_delay;
	mpudata_t mpu;

	memset(&mpu, 0, sizeof(mpudata_t));

	if (sample_rate == 0)
		return;

	loop_delay = (1000 / sample_rate) - 2;

	printf("\nEntering read loop (ctrl-c to exit)\n\n");

	linux_delay_ms(loop_delay);

	while (!done) {
		if (mpu9150_read(&mpu) == 0) {
			print_fused_euler_angles(&mpu);
			// printf_fused_quaternions(&mpu);
			// print_calibrated_accel(&mpu);
			// print_calibrated_mag(&mpu);
		}

		linux_delay_ms(loop_delay);
	}

	printf("\n\n");
}

int read_rawGyro(short* rawGyro){
	mpudata_t mpu;
	memset(&mpu, 0, sizeof(mpudata_t));
	if (mpu9150_read(&mpu) == 0) {
		rawGyro = mpu.rawGyro;
		return 0;
	}
	return -1;
}

void print_fused_euler_angles(mpudata_t *mpu)
{
	printf("\rX: %0.0f Y: %0.0f Z: %0.0f        ",
			mpu->fusedEuler[VEC3_X] * RAD_TO_DEGREE, 
			mpu->fusedEuler[VEC3_Y] * RAD_TO_DEGREE, 
			mpu->fusedEuler[VEC3_Z] * RAD_TO_DEGREE);

	fflush(stdout);
}

void print_fused_quaternions(mpudata_t *mpu)
{
	printf("\rW: %0.2f X: %0.2f Y: %0.2f Z: %0.2f        ",
			mpu->fusedQuat[QUAT_W],
			mpu->fusedQuat[QUAT_X],
			mpu->fusedQuat[QUAT_Y],
			mpu->fusedQuat[QUAT_Z]);

	fflush(stdout);
}

void print_calibrated_accel(mpudata_t *mpu)
{
	printf("\rX: %05d Y: %05d Z: %05d        ",
			mpu->calibratedAccel[VEC3_X], 
			mpu->calibratedAccel[VEC3_Y], 
			mpu->calibratedAccel[VEC3_Z]);

	fflush(stdout);
}

void print_calibrated_mag(mpudata_t *mpu)
{
	printf("\rX: %03d Y: %03d Z: %03d        ",
			mpu->calibratedMag[VEC3_X], 
			mpu->calibratedMag[VEC3_Y], 
			mpu->calibratedMag[VEC3_Z]);

	fflush(stdout);
}

int set_cal(int mag, char *cal_file)
{
	int i;
	FILE *f;
	char buff[32];
	long val[6];
	caldata_t cal;

	if (cal_file) {
		f = fopen(cal_file, "r");
		
		if (!f) {
			perror("open(<cal-file>)");
			return -1;
		}
	}
	else {
		if (mag) {
			f = fopen("./magcal.txt", "r");
		
			if (!f) {
				printf("Default magcal.txt not found\n");
				return 0;
			}
		}
		else {
			f = fopen("./accelcal.txt", "r");
		
			if (!f) {
				printf("Default accelcal.txt not found\n");
				return 0;
			}
		}		
	}

	memset(buff, 0, sizeof(buff));
	
	for (i = 0; i < 6; i++) {
		if (!fgets(buff, 20, f)) {
			printf("Not enough lines in calibration file\n");
			break;
		}

		val[i] = atoi(buff);

		if (val[i] == 0) {
			printf("Invalid cal value: %s\n", buff);
			break;
		}
	}

	fclose(f);

	if (i != 6) 
		return -1;

	cal.offset[0] = (short)((val[0] + val[1]) / 2);
	cal.offset[1] = (short)((val[2] + val[3]) / 2);
	cal.offset[2] = (short)((val[4] + val[5]) / 2);

	cal.range[0] = (short)(val[1] - cal.offset[0]);
	cal.range[1] = (short)(val[3] - cal.offset[1]);
	cal.range[2] = (short)(val[5] - cal.offset[2]);
	
	if (mag) 
		mpu9150_set_mag_cal(&cal);
	else 
		mpu9150_set_accel_cal(&cal);

	return 0;
}

void register_sig_handler()
{
	struct sigaction sia;

	bzero(&sia, sizeof sia);
	sia.sa_handler = sigint_handler;

	if (sigaction(SIGINT, &sia, NULL) < 0) {
		perror("sigaction(SIGINT)");
		exit(1);
	} 
}

void sigint_handler(int sig)
{
	done = 1;
}
