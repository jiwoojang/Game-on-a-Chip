//Handles collisions with environment objects

#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>

#include "enemyMovement.h"
#include "type.h"
#include "playerMovement.h"
#include "utilities.h"
#include "render.h"

int checkPlayerEnvironmentCollision(int nextX, int nextY, levelBlock* block, int blockNum){
    int count;
    for(count = 0; count < blockNum; count ++){
        if (((abs((block+count)->xMin - nextX) < player.width) || (abs((block+count)->xMax - nextX) < 0)) && ((abs((block+count)->yMin - nextY) < player.height) || (abs((block+count)->yMax - nextY) < 0))){
            //printf("Collision with environment detected!\n");
            return 1; 
        }
    }
    return 0;
}

int checkPlayerEnemyCollision(int nextX, int nextY, enemy* enemy, int enemyCount){
    int count;
    for(count = 0; count < enemyCount; count ++){
        if (((abs((enemy+count)->enemyX - nextX) < player.width) || (abs((enemy+count)->enemyX + (enemy+count)->enemySprite.width - nextX) < 0)) && ((abs((enemy+count)->enemyY - nextY) < player.height) || (abs((enemy+count)->enemyY + (enemy+count)->enemySprite.height - nextY) < 0))){
            //printf("Collision with ENEMEY detected!\n");
            return 1; 
        }
    }
    return 0;
}
