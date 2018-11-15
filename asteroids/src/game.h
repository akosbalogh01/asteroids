#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME
#define DEFAULT_MOVE_CYCLE 10000
#define DEFAULT_MOVE_DIRECTION HORIZONTAL
#define DEFAULT_SPACESHIP_POSITION 4
#define MINIMAL_MOVECYCLE 600
#define WIDTH 8
#define HEIGHT 3
#ifndef NULL
#define NULL 0
#endif

#include "segmentlcd_individual.h"
typedef SegmentLCD_UpperCharSegments_TypeDef upperseg;	//redefinition of Segment data structures, to avoid cluttered code
typedef SegmentLCD_LowerCharSegments_TypeDef lowerseg;

typedef enum {NEW_GAME, RUNNING, LEVEL_UP, GAME_OVER} game_status;	//state machine available states
typedef enum {HORIZONTAL, UP, DOWN} s_ori;	//spaceship available orientations

typedef struct {						//variables modified by global interrupts, enabled for one cycle
	uint8_t right 	: 1;				//enabled when <right> is pressed, serial port R
	uint8_t left 	: 1;				//enabled when <left> is pressed, serial port L
	uint8_t start 	: 1;				//enabled when <start> is pressed, serial port S
	uint8_t ragequit: 1;				//enabled when <ragequit> is pressed, serial port R
} IRQ_VARIABLES;

typedef struct {						//game descriptor data structure
	game_status status;
	IRQ_VARIABLES params;
	int	     level;						//current level
	uint8_t  asteroids[3]; 				//asteroid indexes
	uint8_t  spaceship;					//spaceship index
	s_ori	 orientation; 				//spaceship orientation
	uint16_t movecycle;					//current movecycle (how many cycles between spaceship moving)
} logic;

void initialize();						//initializes hardware components (CHIP, TIMER, UART, LCD)

void spaceship_rotate(logic*);			//rotates spaceship during the next cycle, based on IRQ modified global variables
int  spaceship_move(logic*);			//moves spaceship during the next <move> cycle, -

int  decrement(int, int);				//decrements move cycle, based on level, and previous move cycle
void generate_field(logic*);			//generates asteroid field #todo: do not allow repeated selection of the same segment

void render_score(uint8_t);				//renders level on <upper> segment LCD
void render_text_clear();				//deprecated
void render_text_newgame();				//deprecated
void render_text_gameover();			//deprecated
void render_level(uint8_t, uint8_t*);	//renders spaceship and asteroids

#endif //ASTEROIDS_GAME
