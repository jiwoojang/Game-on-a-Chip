#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <RTL.h>

#include "MPU9250.h"
#include "type.h"
#include "customTypes.h"
#include "playerMovement.h"
#include "accel.h"
#include "sensor_fusion.h"

int countaccel = 0;
int h =0;
int rollingavg = 0;
float accelerometer[30];

void initializeSpeed(){
	playerSpeed = 40;
}

void changeSpeed(void){
  if (countaccel == 30){
    for (h = 0; h < 30; h++){ 
     rollingavg = rollingavg + accelerometer[h]; 
     // printf("ROLLINGAVG: %f\n", rollingavg); //debug statement to check if rolling average is increasing
    }
    playerSpeed = rollingavg + 2000/30; 
    countaccel = 0;
   //printf("PLAYERSPEED: %d\n", playerSpeed);
  }
}

void pollAccel(void){
    accelerometer[countaccel] = sensor_fusion_getRoll();
    countaccel ++; 
    //printf("ACCELDATA: %f\n",  sensor_fusion_getRoll());
}


