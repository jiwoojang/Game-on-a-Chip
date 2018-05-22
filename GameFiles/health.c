//Source file to support health bar 

#include <lpc17xx.h>
#include "LED.h"
#include "health.h"
#include "utilities.h"

int currentHealth;
const int _maxHealth = 8;		// Adjust this constant as we see fit
unsigned char healthBits;

// Initializes the health counter
void initializeHealth(void){
	LED_setup();
	currentHealth = _maxHealth;
	setHealth(currentHealth);
}

// Reset health to full
void resetHealth(void){
	currentHealth = _maxHealth;
	
	setHealth(currentHealth);
}

// Set health to a specific number
void setHealth(int n) {
	if (n > 0){
		currentHealth = n;
		
		healthBits = power(2,n) - 1;
		
		LED_display(healthBits);
	} else {
		 gameOver = 1; 
	}
}

// Decrement health by a specific amount (subtracts from current health amount)
void decrementHealth(int n){
	setHealth(currentHealth - n);
}

// Return current health
// Note, this is kind of a gross implementation, I was having issues getting globals to be accessible from files that were includeded...
int getCurrentHealth(void){
	return currentHealth;
}
