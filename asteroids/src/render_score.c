#include "segmentlcd_individual.h"
#include "game.h"
#include "charmap.h"

upperseg numbers[] = {{CHARMAP_0}, {CHARMAP_1}, {CHARMAP_2}, {CHARMAP_3}, {CHARMAP_4}, {CHARMAP_5}, {CHARMAP_6}, {CHARMAP_7}, {CHARMAP_8}, {CHARMAP_9}};
upperseg result[SEGMENT_LCD_NUM_OF_UPPER_CHARS];

void render_score(uint8_t level) {
	uint8_t i = 0;
	register uint8_t temp;

	do {
		temp = level % 10;
		result[i] = numbers[temp];
		level -= temp;
		level /= 10;
		i++;
	} while(i < 4);

	SegmentLCD_UpperSegments(result);
};
