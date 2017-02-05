#include <stdio.h>
#include <math.h>
#include "bcm2835.h"
#include "I2Cdev.h"
#include "MPU6050.h"

int main(int argc, char **argv) {
  printf("MPU6050 3-axis acceleromter example program\n");
  I2Cdev::initialize();
  MPU6050 accelgyro ;
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  if ( accelgyro.testConnection() ) 
    printf("MPU6050 connection test successful\n") ;
  else {
    fprintf( stderr, "MPU6050 connection test failed! something maybe wrong, continuing anyway though ...\n");
    return 1;
  }
  accelgyro.initialize();
  printf("\n");
  printf("  ax \t ay \t az \t gx \t gy \t gz:\n");
  while (true) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
printf("  %d \t %d \t %d \t %d \t %d \t %d\r", ax, ay, az, gx, gy, gz);
fflush(stdout);
    bcm2835_delay(100);
  }
  return 1; 
}
