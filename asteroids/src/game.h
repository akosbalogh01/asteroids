#ifndef ASTEROIDS_GAME
#define ASTEROIDS_GAME
#define DEFAULT_MOVE_CYCLE
#define WIDTH 8
#define HEIGHT 3

#include "segmentlcd_individual.h"
typedef SegmentLCD_UpperCharSegments_TypeDef upperseg;
typedef SegmentLCD_LowerCharSegments_TypeDef lowerseg;

typedef enum {NEW_GAME, RUNNING, LEVEL_UP, GAME_OVER} game_status;

typedef struct {
	uint8_t right : 1;
	uint8_t left : 1;
	uint8_t start : 1;
	uint8_t ragequit: 1;
} IRQ_VARIABLES;

typedef struct {
	game_status status;
	uint8_t  level;
	uint8_t  asteroids[3]; //asteroid indexes
	uint8_t  spaceship;	//index of spaceship
	uint8_t	 direction : 2; //
	upperseg numerical[SEGMENT_LCD_NUM_OF_UPPER_CHARS];
	lowerseg alphanumerical[SEGMENT_LCD_NUM_OF_LOWER_CHARS];
} logic;

// D: interrupt function prototypes
// interrupts.c -> #include "game.h"

void render_score(uint8_t);
void render_text_clear();
void render_text_newgame();
void render_text_gameover();

#endif //ASTEROIDS_GAME
