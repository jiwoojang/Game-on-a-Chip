// Wrapper enemy movement

#include <lpc17xx.h>
#include <stdio.h>
#include <math.h>

#include "render.h"
#include "type.h"
#include "enemyMovement.h"
#include "utilities.h"
#include "gameTimer.h"
#include "collision.h"

// Enemies
enemy enemies[3];

// Number of enemies
const int enemyNum = 3;

// Enemy speed in pixels/second
int enemySpeed = 50;

int enemyDeltaPos;

void initializeEnemies(void) {
    int j;
	
	enemies[0].enemyX = 100; 
	enemies[0].enemyY = 50;
    enemies[0].moveHorizontal = 1;
    enemies[0].pingPos = 50;
    enemies[0].pongPos = 150;
    enemies[0].direction = 1;
	enemies[0].enemySprite.height = 10;
	enemies[0].enemySprite.width = 10;
	enemies[0].enemySprite.bitmap = enemyBitmap;
	
	enemies[1].enemyX = 100; 
	enemies[1].enemyY = 250;
	enemies[1].moveHorizontal = 0;
    enemies[1].pingPos = 0;
    enemies[1].pongPos = 200;
    enemies[1].direction = 1;
	enemies[1].enemySprite.height = 10;
	enemies[1].enemySprite.width = 10;
	enemies[1].enemySprite.bitmap = enemyBitmap;
	
	enemies[2].enemyX = 70; 
	enemies[2].enemyY = 70;
    enemies[2].moveHorizontal = 1;
    enemies[2].pingPos = 70;
    enemies[2].pongPos = 300;
    enemies[2].direction = 1;
	enemies[2].enemySprite.height = 10;
	enemies[2].enemySprite.width = 10;
	enemies[2].enemySprite.bitmap = enemyBitmap;
  
	
	for(j = 0; j < enemyNum; j ++){
		renderSpritePosition(enemies[j].enemyX, enemies[j].enemyY, &enemies[j].enemySprite);
	}
}

int moveEnemies(void){
  
  int nextX, nextY, c;
  
  enemyDeltaPos = ceil(((float)enemySpeed * deltaTime));
  
  for (c = 0; c < enemyNum; c ++) {
    if (enemies[c].moveHorizontal){
      nextX = enemies[c].enemyX + enemies[c].direction * enemyDeltaPos;
      nextY = enemies[c].enemyY;
      
      if (nextX >= enemies[c].pongPos || nextX <= enemies[c].pingPos){
				enemies[c].direction *= -1;
				
				if (nextX >= enemies[c].pongPos)
					nextX = enemies[c].pongPos;
				else if (nextX <= enemies[c].pingPos)
					nextX = enemies[c].pingPos;
			}
        
    } else {
      nextY = enemies[c].enemyY + enemies[c].direction * enemyDeltaPos;
      nextX = enemies[c].enemyX;
      
      if (nextY >= enemies[c].pongPos || nextY <= enemies[c].pingPos){
        enemies[c].direction *= -1;
				
				if (nextY >= enemies[c].pongPos)
					nextY = enemies[c].pongPos;
				if (nextY <= enemies[c].pingPos)
					nextY = enemies[c].pingPos;
			}
    }
      
      renderSpritePosition(nextX, nextY, &enemies[c].enemySprite);
    
      enemies[c].enemyX = nextX;
      enemies[c].enemyY = nextY;
    
    // printf("enemyDeltaPos: %d Delta Time: %f\n", enemyDeltaPos, deltaTime);
     //printf("Enemy %d moving to position: %d, %d, in direction %d\n", c, nextX, nextY, enemies[c].direction);

  }
  
  return 0;
}
