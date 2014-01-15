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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "mpu9150.h"
#include "linux_glue.h"
#include "local_defaults.h"

void read_loop(unsigned int sample_rate);
void print_accel(mpudata_t *mpu);
void print_mag(mpudata_t *mpu);
void write_cal();
void register_sig_handler();
void sigint_handler(int sig);

int done;
short minVal[3];
short maxVal[3];
char calFile[512];
int mag_mode;

void usage(char *argv_0)
{
	printf("\nUsage: %s <-a | -m> [options]\n", argv_0);
	printf("  -b <i2c-bus>          The I2C bus number where the IMU is. The default is 1 for /dev/i2c-1.\n");
	printf("  -s <sample-rate>      The IMU sample rate in Hz. Range 2-50, default 10.\n");
	printf("  -a                    Accelerometer calibration\n");
    printf("  -m                    Magnetometer calibration\n");
    printf("                        Accel and mag modes are mutually exclusive, but one must be chosen.\n");
	printf("  -f <cal-file>         Where to save the calibration file. Default ./<mode>cal.txt\n");
	printf("  -h                    Show this help\n");

	printf("\nExample: %s -b3 -s20 -a\n\n", argv_0);
	
	exit(1);
}

int main(int argc, char **argv)
{
	int opt;
	int i2c_bus = DEFAULT_I2C_BUS;
	int sample_rate = DEFAULT_SAMPLE_RATE_HZ;
	
	mag_mode = -1;

	memset(calFile, 0, sizeof(calFile));

	while ((opt = getopt(argc, argv, "b:s:y:amh")) != -1) {
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
			if (strlen(optarg) >= sizeof(calFile)) {
				printf("Choose a shorter path for the cal file\n");
				usage(argv[0]);
			}

			strcpy(calFile, optarg);
			break;

		case 'a':
			if (mag_mode != -1)
				usage(argv[0]);

			mag_mode = 0;
			break;

		case 'm':
			if (mag_mode != -1)
				usage(argv[0]);

			mag_mode = 1;
			break;
		
		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	if (mag_mode == -1)
		usage(argv[0]);

	register_sig_handler();

	if (mpu9150_init(i2c_bus, sample_rate, 0))
		exit(1);

	read_loop(sample_rate);

	if (strlen(calFile) == 0) {
		if (mag_mode)
			strcpy(calFile, "magcal.txt");
		else
			strcpy(calFile, "accelcal.txt");
	}

	write_cal();

	mpu9150_exit();

	return 0;
}

void read_loop(unsigned int sample_rate)
{
	int i, change;
	unsigned long loop_delay;
	mpudata_t mpu;

	if (sample_rate == 0)
		return;

	memset(&mpu, 0, sizeof(mpudata_t));

	for (i = 0; i < 3; i++) {
		minVal[i] = 0x7fff;
		maxVal[i] = 0x8000;
	}

	loop_delay = (1000 / sample_rate) - 2;

	printf("\nEntering read loop (ctrl-c to exit)\n\n");

	linux_delay_ms(loop_delay);

	while (!done) {
		change = 0;

		if (mag_mode) {
			if (mpu9150_read_mag(&mpu) == 0) {
				for (i = 0; i < 3; i++) {
					if (mpu.rawMag[i] < minVal[i]) {
						minVal[i] = mpu.rawMag[i];
						change = 1;
					}
				
					if (mpu.rawMag[i] > maxVal[i]) {
						maxVal[i] = mpu.rawMag[i];
						change = 1;
					}
				}
			}
		}
		else {
			if (mpu9150_read_dmp(&mpu) == 0) {
				for (i = 0; i < 3; i++) {
					if (mpu.rawAccel[i] < minVal[i]) {
						minVal[i] = mpu.rawAccel[i];
						change = 1;
					}
				
					if (mpu.rawAccel[i] > maxVal[i]) {
						maxVal[i] = mpu.rawAccel[i];
						change = 1;
					}
				}
			}
		}
		
		if (change) {
			if (mag_mode)
				print_mag(&mpu);
			else
				print_accel(&mpu);
		}

		linux_delay_ms(loop_delay);
	}

	printf("\n\n");
}

void print_accel(mpudata_t *mpu)
{
	printf("\rX %d|%d|%d    Y %d|%d|%d    Z %d|%d|%d             ",
			minVal[0], mpu->rawAccel[0], maxVal[0], 
			minVal[1], mpu->rawAccel[1], maxVal[1],
			minVal[2], mpu->rawAccel[2], maxVal[2]);

	fflush(stdout);
}

void print_mag(mpudata_t *mpu)
{
	printf("\rX %d|%d|%d    Y %d|%d|%d    Z %d|%d|%d             ",
			minVal[0], mpu->rawMag[0], maxVal[0], 
			minVal[1], mpu->rawMag[1], maxVal[1],
			minVal[2], mpu->rawMag[2], maxVal[2]);

	fflush(stdout);
}

void write_cal()
{
	int i, fd;
	char buff[32];

	fd = open(calFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	if (fd < 0) {
		perror("open(calFile)");
		return;
	}

	for (i = 0; i < 3; i++) {
			sprintf(buff, "%d\n%d\n", minVal[i], maxVal[i]);
			write(fd, buff, strlen(buff));
	}

	close(fd);
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
