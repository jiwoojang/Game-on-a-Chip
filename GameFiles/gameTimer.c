// Header file to keep track of game time
#include <lpc17xx.h>
#include "type.h"
#include "timer.h"
#include "utilities.h"

float deltaTime = 0;
float time = 0;
float prevTime = 0;

float getTimer(void){
	// Convert to regular seconds
	// Note this returns a floating point number in seconds!
	float timeInSeconds = timer_read()/(float)power(10, 6);
	return timeInSeconds;
}

void startTimer(void){
	// Set up and starts timer.
	timer_setup();
    
	time = getTimer();
	prevTime = time;
}

void clockDeltaTime(){
  time = getTimer();
  deltaTime = time - prevTime;
  
  prevTime = time;
}

