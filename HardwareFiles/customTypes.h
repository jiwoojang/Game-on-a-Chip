// Struct for player data
typedef struct {
	int height;
	int width; 
  
  int lastX;
  int lastY;

	unsigned short *bitmap;
} sprite;

typedef struct {
	int enemyX; 
	int enemyY; 
	
	int moveHorizontal;
	
	int direction;
	
	int pingPos;
	int pongPos;
  
	sprite enemySprite;
	
} enemy;

typedef struct {
    uint8_t xMin; 
    uint8_t xMax;
    uint8_t yMin;
    uint8_t yMax;
} levelBlock;
