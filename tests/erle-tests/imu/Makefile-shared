#
# Makefile for eMPL Linux userland implementation
#

CC = gcc
CFLAGS = -Wall -fsingle-precision-constant -fPIC

# add -DI2C_DEBUG for debugging
DEFS = -DEMPL_TARGET_LINUX -DMPU9150 -DAK8975_SECONDARY

EMPLDIR = eMPL
GLUEDIR = glue
MPUDIR = mpu9150

OBJS = inv_mpu.o \
       inv_mpu_dmp_motion_driver.o \
       linux_glue.o \
       mpu9150.o \
       quaternion.o \
       vector3d.o


all : libimu.so


imu : $(OBJS) imu.o
	$(CC) $(CFLAGS) $(OBJS) imu.o -lm -o imu

imucal : $(OBJS) imucal.o
	$(CC) $(CFLAGS) $(OBJS) imucal.o -lm -o imucal

	
imu.o : imu.c
	$(CC) $(CFLAGS) -I $(EMPLDIR) -I $(GLUEDIR) -I $(MPUDIR) $(DEFS) -c imu.c
	
imucal.o : imucal.c
	$(CC) $(CFLAGS) -I $(EMPLDIR) -I $(GLUEDIR) -I $(MPUDIR) $(DEFS) -c imucal.c

mpu9150.o : $(MPUDIR)/mpu9150.c
	$(CC) $(CFLAGS) $(DEFS) -I $(EMPLDIR) -I $(GLUEDIR) -c $(MPUDIR)/mpu9150.c

quaternion.o : $(MPUDIR)/quaternion.c
	$(CC) $(CFLAGS) $(DEFS) -c $(MPUDIR)/quaternion.c

vector3d.o : $(MPUDIR)/vector3d.c
	$(CC) $(CFLAGS) $(DEFS) -c $(MPUDIR)/vector3d.c

linux_glue.o : $(GLUEDIR)/linux_glue.c
	$(CC) $(CFLAGS) $(DEFS) -I $(EMPLDIR) -I $(GLUEDIR) -c $(GLUEDIR)/linux_glue.c

inv_mpu_dmp_motion_driver.o : $(EMPLDIR)/inv_mpu_dmp_motion_driver.c
	$(CC) $(CFLAGS) $(DEFS) -I $(EMPLDIR) -I $(GLUEDIR) -c $(EMPLDIR)/inv_mpu_dmp_motion_driver.c

inv_mpu.o : $(EMPLDIR)/inv_mpu.c
	$(CC) $(CFLAGS) $(DEFS) -I $(EMPLDIR) -I $(GLUEDIR) -c $(EMPLDIR)/inv_mpu.c


libimu.so: $(OBJS)
	$(CC) -shared -Wl,-soname,libimu.so $^ -o $@

clean:
	rm -f *.o *.so *.so* imu imucal

