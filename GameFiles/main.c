// Main file for the game
#include <RTL.h>
#include <lpc17xx.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "MPU9250.h"
#include "type.h"
#include "health.h"
#include "utilities.h"
#include "gameTimer.h"
#include "delay.h"
#include "render.h"
#include "playerMovement.h"
#include "enemyMovement.h"
#include "accel.h"
#include "sensor_fusion.h"
#include "led.h"

OS_MUT mutex;

int startAccel = 0;

__task void frameTimer(){
	startTimer();
  while(1){
    clockDeltaTime();
		
    os_tsk_pass();
  }
}
__task void updateLoop() {
  while(1){
    pollJoystick();
    
    os_tsk_pass();
  }
}

__task void renderEnemies(){
  while(1){
    moveEnemies();
    
    os_tsk_pass();
  }
}

__task void renderPlayer(){
  while(1){
    movePlayer();
    
    os_tsk_pass();
  }
}

__task void readSensor(){
		
	while(1) {
		//os_mut_wait(&mutex, 0xffff);
		
		//printf("Acquired mutex\n");

		MPU9250_read_gyro();
		MPU9250_read_acc();
		MPU9250_read_mag();
                
		//printf("ACCELDATA: %f %f %f %f %f %f %f %f %f \n",MPU9250_gyro_data[0],MPU9250_gyro_data[1],MPU9250_gyro_data[2], MPU9250_accel_data[0],MPU9250_accel_data[1],MPU9250_accel_data[2],MPU9250_mag_data[0],MPU9250_mag_data[1],MPU9250_mag_data[2]);
        
		//os_mut_release(&mutex);
		
		//printf("Mutex Released\n");
    os_tsk_pass();
				// Make sure mag reading is valid
	}
}

__task void sensorFusion(){
	while(1){
		//os_mut_wait(&mutex, 0xffff);
		sensor_fusion_update(MPU9250_gyro_data[0],	MPU9250_gyro_data[1],		MPU9250_gyro_data[2],
												 MPU9250_accel_data[0],	MPU9250_accel_data[1],	MPU9250_accel_data[2],
											 MPU9250_mag_data[0],		MPU9250_mag_data[1],		MPU9250_mag_data[2]);
		//os_mut_release(&mutex);
		os_tsk_pass();
	}
}

__task void updateSpeed(){
  while(1){
    pollAccel();
    changeSpeed();

    os_tsk_pass();
  } 
}

__task void readPotentiometer(){
	//Note: all initializations done in main
    unsigned int timer = 0; 
    
    while (1) {
      //set conversion bit to on
      LPC_ADC->ADCR |= (0x1 << 24); 
      
     //wait for conversion to finish
     while ((LPC_ADC->ADGDR & 0x8000) == 0 && timer < 10 ){
        timer = timer + 1; 
        };
        
     timer = 0; 
 
     //print results
     //printf("Potentiometer output: %d\n", (LPC_ADC->ADGDR >> 4) & 0xFFF); 
				
		playerSpeed = 40 + ((LPC_ADC->ADGDR >> 4) & 0xFFF)/(float)10;
				
				printf("Player Speed: %d\n", playerSpeed);
     os_dly_wait(10);   
    }
}

__task void startTask(){
  // Initialize mutex for sensor polling and fusion
  //os_mut_init(&mutex);  
    
  //Initialize IMU
  //MPU9250_init(1,1);
    
  //Initialize Sensor Fusion
  //sensor_fusion_init(); 
  //sensor_fusion_begin(256.0); 
  
  // Initializes LEDs.
	LED_setup();
	
	// Verify Comms
	//LED_display(MPU9250_whoami());
  
	//os_tsk_create(readSensor,1);
  //os_tsk_create(sensorFusion,1);
	
	printf("Initializing other parameters\n");
	
  initializeSpeed();
  initializeScreen();
  initializeHealth();
  initializePlayer();
  initializeEnemies();

	// Clear proper bits for PINSEL
	LPC_PINCON->PINSEL1 &= ~(0x03<<18);
	LPC_PINCON->PINSEL1 |= (0x01<<18);
	
	// Power on!
	LPC_SC->PCONP |= (1 << 12);
	
	LPC_ADC->ADCR = (1<<2)|		//select AD0.2pin
									(4<<8)|		//ADC clock is 25MHz/5
									(1<<21);	//enable ADC
	
	printf("creating other tasks\n");
	
	os_tsk_create(readPotentiometer,1);
	
	os_tsk_create(frameTimer,1);
  //os_tsk_create(updateSpeed,1); 
  os_tsk_create(updateLoop,1);
  os_tsk_create(renderPlayer,1);
  os_tsk_create(renderEnemies,1);
  
	while(1){		
		os_tsk_pass();
	}
}

int main (void) {
  
  printf("--Start--\n");
  
  os_sys_init(startTask); 
}
