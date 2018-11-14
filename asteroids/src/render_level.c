#include "segmentlcd_individual.h"
#include "charmap.h"
#include "game.h"

lowerseg result[SEGMENT_LCD_NUM_OF_LOWER_CHARS];
lowerseg asrmap[] = {{CHARMAP_ASR0}, {CHARMAP_ASR1}, {CHARMAP_ASR2}, {CHARMAP_ASR3}, {CHARMAP_ASR4}};

void render_level(uint8_t spaceship, uint8_t* asteroids) {
	uint8_t i;
	for (i = 0; i < 3; i++) {
		result[(asteroids[i] - (asteroids[i] % 10)) / 10] = asrmap[asteroids[i] % 10];
	}

	result[(spaceship - (spaceship % 10)) / 10].raw |= asrmap[spaceship % 10].raw;

	SegmentLCD_LowerSegments(result);

	for (i = 0; i < SEGMENT_LCD_NUM_OF_LOWER_CHARS; i++) result[i].raw = CHARMAP_NUL;
};
