#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>
#include "bcm2835.h"
#include "I2Cdev.h"
#include "MPU6050.h"

#define MY_PRIORITY (49) /* we use 49 as the PRREMPT_RT use 50
                            as the priority of kernel tasklets
                            and interrupt handler by default */

#define MAX_SAFE_STACK (8*1024) /* The maximum stack size which is
                                   guaranteed safe to access without
                                   faulting */

#define NSEC_PER_SEC    (1000000000) /* The number of nsecs per sec. */

void stack_prefault(void) {

        unsigned char dummy[MAX_SAFE_STACK];

        memset(dummy, 0, MAX_SAFE_STACK);
        return;
}

int main(int argc, char* argv[])
{
        struct timespec t;
        struct sched_param param;
        int interval = 50000; /* 50us*/

        /* Declare ourself as a real time task */

        param.sched_priority = MY_PRIORITY;
        if(sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
                perror("sched_setscheduler failed");
                exit(-1);
        }

        /* Lock memory */

        if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
                perror("mlockall failed");
                exit(-2);
        }

        /* Pre-fault our stack */

        stack_prefault();

        /* Set up externel device */
        printf("MPU6050 3-axis acceleromter example program\n");
        I2Cdev::initialize();
        MPU6050 accelgyro ;
        int16_t ax, ay, az;
        int16_t gx, gy, gz;
        float axf, ayf, azf;
        float gxf, gyf, gzf;
        int16_t accl_scale, gyro_scale;
	accelgyro.resetGyroscopePath();
        accelgyro.resetAccelerometerPath();
        accelgyro.resetTemperaturePath();
        accelgyro.resetI2CMaster();
        accl_scale = accelgyro.getFullScaleAccelRange();
        gyro_scale = accelgyro.getFullScaleGyroRange();
      
        clock_gettime(CLOCK_MONOTONIC ,&t);
        /* start after one second */
        t.tv_sec++;

        if ( accelgyro.testConnection() ) 
          fprintf(stdout,"MPU6050 connection test successful\n") ;
        else {
          fprintf( stderr, "MPU6050 connection test failed! something maybe wrong, continuing anyway though ...\n");
          //return 1;
        }
        while(1) {
                /* wait until next shot */
                clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
                /* do the stuff */
                accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		axf= (( float ) ax  ) / ((float) accl_scale);
		ayf= (( float ) ax  ) / ((float) accl_scale);
		azf= (( float ) ax  ) / ((float) accl_scale);
		gxf= (( float ) ax  ) / ((float) gyro_scale);
		gyf= (( float ) ax  ) / ((float) gyro_scale);
		gzf= (( float ) ax  ) / ((float) gyro_scale);
                fprintf(stdout," %d , % d  \n", ax, accl_scale);
                //fprintf(stdout,"  %.4f \t %.4f \t %.4f \t %.4f \t %.4f \t %.4f\n", axf, ayf, azf, gxf, gyf, gzf);
                fflush(stdout);
                /* calculate next shot */
                t.tv_nsec += interval;
                while (t.tv_nsec >= NSEC_PER_SEC) {
                       t.tv_nsec -= NSEC_PER_SEC;
                        t.tv_sec++;
                }
   }
}
