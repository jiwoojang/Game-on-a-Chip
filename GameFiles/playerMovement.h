// Wrapper for joystick input and player movement

extern int joystickDirection;
extern int joystickPrevDirection;

extern int currentPlayerX;
extern int currentPlayerY;

extern float deltaTime;
extern int playerSpeed;

void getDeltaTime(void);
int movePlayer(void);
void pollJoystick(void);
void initializePlayer(void);

