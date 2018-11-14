#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME
#define DEFAULT_MOVE_CYCLE 10000
#define DEFAULT_MOVE_DIRECTION 1
#define DEFAULT_SPACESHIP_POSITION 4
#define MINIMAL_MOVECYCLE 600
#define WIDTH 8
#define HEIGHT 3
#ifndef NULL
#define NULL 0
#endif

#include "segmentlcd_individual.h"
typedef SegmentLCD_UpperCharSegments_TypeDef upperseg;
typedef SegmentLCD_LowerCharSegments_TypeDef lowerseg;

typedef enum {NEW_GAME, RUNNING, LEVEL_UP, GAME_OVER} game_status;

typedef struct {
	uint8_t right 	: 1;
	uint8_t left 	: 1;
	uint8_t start 	: 1;
	uint8_t ragequit: 1;
} IRQ_VARIABLES;

typedef struct {
	game_status status;
	IRQ_VARIABLES params;
	int	     level;
	uint8_t  asteroids[3]; 	//asteroid indexes
	uint8_t  spaceship;		//spaceship index
	uint8_t	 orientation; 	//spaceship orientation
	uint16_t movecycle;
} logic;

void initialize();

void spaceship_rotate(logic*);
int  spaceship_move(logic*);

int  decrement(int, int);
void generate_field(logic*);

void render_score(uint8_t);
void render_text_clear();
void render_text_newgame();
void render_text_gameover();
void render_level(uint8_t, uint8_t*);

#endif //ASTEROIDS_GAME
