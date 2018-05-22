// Where the magic happens
#include <RTL.h>
#include <lpc17xx.h>
#include <stdio.h>
#include "render.h"
#include "type.h"
#include "GLCD.h"
#include "utilities.h"

#define BG		Black
#define PC		Cyan

OS_MUT renderMutex;

// Player sprite
sprite player;
levelBlock testBlocks[18];
unsigned short testBlockBitmap[3000];


// Display specs
int displayWidth = 320;
int displayHeight = 240;

int count = 0;

void initializeScreen(void) {
  // Set up LCD
  GLCD_Init(); 
  GLCD_Clear(BG); 
	os_mut_init(&renderMutex);
  
  // Initialize data about player
  player.height = 10;
  player.width = 10;
                  
  player.bitmap = playerBitmap;
 
  // Test code for the testBlock item;
  for (count = 0; count < 3000; count ++)
    testBlockBitmap[count] = White;
  
  count = 0;
  // Struct #0
     testBlocks[0].xMin = 40;
     testBlocks[0].yMin = 220;
     testBlocks[0].xMax = 60;
     testBlocks[0].yMax = 240;
    
// Struct #1
     testBlocks[1].xMin = 20;
     testBlocks[1].yMin = 160;
     testBlocks[1].xMax = 40;
     testBlocks[1].yMax = 180;
     
// Struct #2
     testBlocks[2].xMin = 20;
     testBlocks[2].yMin = 80;
     testBlocks[2].xMax = 60;
     testBlocks[2].yMax = 100;
 // Struct #3
     testBlocks[3].xMin = 40;
     testBlocks[3].yMin = 40;
     testBlocks[3].xMax = 60;
     testBlocks[3].yMax = 60;
     
// Struct #4
     testBlocks[4].xMin = 80;
     testBlocks[4].yMin = 180;
     testBlocks[4].xMax = 100;
     testBlocks[4].yMax = 280;
     
// Struct #5
     testBlocks[5].xMin = 140;
     testBlocks[5].yMin = 100;
     testBlocks[5].xMax = 160;
     testBlocks[5].yMax = 180;
     
// Struct #6
     testBlocks[6].xMin = 80;
     testBlocks[6].yMin = 180;
     testBlocks[6].xMax = 100;
     testBlocks[6].yMax = 280;
     
// Struct #7
     testBlocks[7].xMin = 140;
     testBlocks[7].yMin = 100;
     testBlocks[7].xMax = 160;
     testBlocks[7].yMax = 180;
     
// Struct #8
     testBlocks[8].xMin = 100;
     testBlocks[8].yMin = 220;
     testBlocks[8].xMax = 120;
     testBlocks[8].yMax = 240;
     
// Struct #9
     testBlocks[9].xMin = 140;
     testBlocks[9].yMin = 220;
     testBlocks[9].xMax = 160;
     testBlocks[9].yMax = 280;
     
// Struct #10
     testBlocks[10].xMin = 200;
     testBlocks[10].yMin = 220;
     testBlocks[10].xMax = 220;
     testBlocks[10].yMax = 320;
    
// Struct #11
     testBlocks[11].xMin = 200;
     testBlocks[11].yMin = 220;
     testBlocks[11].xMax = 220;
     testBlocks[11].yMax = 240;

// Struct #12
     testBlocks[12].xMin = 200;
     testBlocks[12].yMin = 40;
     testBlocks[12].xMax = 220;
     testBlocks[12].yMax = 260;

// Struct #13
     testBlocks[13].xMin = 260;
     testBlocks[13].yMin = 40;
     testBlocks[13].xMax = 280;
     testBlocks[13].yMax = 60;    
     
 // Struct #14
     testBlocks[14].xMin = 240;
     testBlocks[14].yMin = 100;
     testBlocks[14].xMax = 260;
     testBlocks[14].yMax = 120;	 
	 
// Struct #15
     testBlocks[15].xMin = 260;
     testBlocks[15].yMin = 180;
     testBlocks[15].xMax = 280;
     testBlocks[15].yMax = 280;

// Struct #16
     testBlocks[16].xMin = 240;
     testBlocks[16].yMin = 180;
     testBlocks[16].xMax = 260;
     testBlocks[16].yMax = 200;

// Struct #17
     testBlocks[17].xMin = 260;
     testBlocks[17].yMin = 220;
     testBlocks[17].xMax = 280;
     testBlocks[17].yMax = 240;
  
  for (count = 0; count < 17; count++){
    GLCD_Bitmap(testBlocks[count].xMin, testBlocks[count].yMin, 100, 30, (unsigned char*)testBlockBitmap);
  }
}

void renderSpritePosition(int x, int y, sprite* targetSprite){ 
  // As long as we are not going over the ends of the display,
  if (x <=  displayWidth - targetSprite->width && x >= 0 && y >= 0 && y <= displayHeight - targetSprite->height){
		// Acquire the render lock
    os_mut_wait(&renderMutex, 0xffff);
		
    // Erase the player's last location from the display
    GLCD_Bitmap(targetSprite->lastX, targetSprite->lastY, targetSprite->width, targetSprite->height, (unsigned char*)blankBitmap);
    
    // Render sprite at co-ordinates
    GLCD_Bitmap(x, y, targetSprite->width, targetSprite->height, (unsigned char*)targetSprite->bitmap);
    
		// Release render lock
		os_mut_release(&renderMutex);
		
    // Update the trackers of the player
    targetSprite->lastX = x;
    targetSprite->lastY = y;
  }
  else {
    printf("Error, attempting to render player on invalid co-ordinates\n");
  }
 }
