// Wrapper for joystick input and player movement

#include <lpc17xx.h>
#include <stdio.h>
#include <math.h>

#include "type.h"
#include "render.h"
#include "playerMovement.h"
#include "enemyMovement.h"
#include "joystick.h"
#include "utilities.h"
#include "gameTimer.h"
#include "collision.h"
#include "health.h"

// Joystick trackers: 
// -3 = idle
//  0 = Up
//  1 = Right
//  2 = Down
//  3 = Left
int joystickDirection = -3;
int joystickPrevDirection = -3;

// Initial player position
int initialPlayerX = 0; 
int initialPlayerY = 0; 

// Current player position
int currentPlayerX; 
int currentPlayerY;

int nextPlayerX;
int nextPlayerY;

// Player speed in pixels/second
int playerSpeed = 80;

int playerDeltaPos = 0;

int collidedWithEnemy = 0;

void initializePlayer(void) {
  renderSpritePosition(initialPlayerX, initialPlayerY, &player);
  
  currentPlayerX = initialPlayerX; 
  currentPlayerY = initialPlayerY;
}

int movePlayer(void){
  
  playerDeltaPos = ceil(((float)playerSpeed * deltaTime));
    
  if(joystickDirection == 0) {
		// Move up
    if (currentPlayerY - playerDeltaPos > 0)
      nextPlayerY = currentPlayerY - playerDeltaPos; 
    else
      nextPlayerY = 0;

  } else if (joystickDirection == 1) {
        // Move Right   
    if (currentPlayerX + playerDeltaPos < displayWidth - player.width)
      nextPlayerX = currentPlayerX + playerDeltaPos; 
    else
      nextPlayerX = displayWidth - player.width;

  } else if (joystickDirection == 2) {
        // Move down
    if (currentPlayerY + playerDeltaPos < displayHeight - player.height)
      nextPlayerY = currentPlayerY + playerDeltaPos;
    else 
      nextPlayerY = displayHeight - player.height;

  } else if (joystickDirection == 3){
        // Move left
    if (currentPlayerX - playerDeltaPos > 0)
      nextPlayerX = currentPlayerX - playerDeltaPos;
    else
      nextPlayerX = 0;
  }
  // Check Collisions
  if (!collidedWithEnemy){
		if (checkPlayerEnemyCollision(nextPlayerX, nextPlayerY, enemies, 3)){
			decrementHealth(4);
			collidedWithEnemy = 1;
		}
	}  else {
		if (!checkPlayerEnemyCollision(nextPlayerX, nextPlayerY, enemies, 3))
			collidedWithEnemy = 0;
	}
  // Render the player if need be
    if (!checkPlayerEnvironmentCollision(nextPlayerX, nextPlayerY, testBlocks, 17)){
        currentPlayerX = nextPlayerX; 
        currentPlayerY = nextPlayerY; 
        
        renderSpritePosition(currentPlayerX, currentPlayerY, &player);
    }
  
	return 0;
}

void pollJoystick(void){
	//Read the joystick
	uint32_t direction = joystick_read();
	
	// Verify input
	if (direction != joystickPrevDirection){
		// Cache prev direction
		joystickPrevDirection = direction;
		
		// Set the value accordingly
		joystickDirection = log2Number(direction) - 3;
	}
}
