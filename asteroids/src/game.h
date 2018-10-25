#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME
#define DEFAULT_MOVE_CYCLE
#define WIDTH 8
#define HEIGHT 3

typedef enum {NEW_GAME, RUNNING, LEVEL_UP, GAME_OVER} game_status;

typedef struct {
	unsigned char right : 1;
	unsigned char left : 1;
	unsigned char start : 1;
	unsigned char ragequit: 1;
} IRQ_VARIABLES;

typedef struct {
	game_status status;
	unsigned char level;
	unsigned char asteroids[3]; //3 indexes of where the asteroids are
	unsigned char spaceship;	//index of spaceship
	unsigned char direction : 2; //
} logic;

// D: interrupt function prototypes
// interrupts.c -> #include "game.h"

// A: render fucntion prototypes


#endif //ASTEROIDS_GAME
