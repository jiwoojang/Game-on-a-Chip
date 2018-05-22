// Where the magic happens 
#include "customTypes.h"

extern int displayWidth;
extern int displayHeight;

extern sprite player;
extern levelBlock testBlocks[18];
extern enemy enemies[3];

void initializeScreen(void);
void renderSpritePosition(int x, int y, sprite* targetSprite);
