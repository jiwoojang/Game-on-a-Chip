// Header file to keep track of game time

// For smoothing movement
extern float deltaTime;
extern float time;
extern float prevTime;

void startTimer(void);
float getTimer(void); 
void clockDeltaTime(void);

