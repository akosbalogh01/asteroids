#include "segmentlcd_individual.h"
#include "charmap.h"
#include "game.h"

lowerseg result[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

void render_text_newgame() {
	result[0] = CHARMAP_N;
	result[1] = CHARMAP_E;
	result[2] = CHARMAP_W;
	result[3] = CHARMAP_G;
	result[4] = CHARMAP_A;
	result[5] = CHARMAP_M;
	result[6] = CHARMAP_E;

	SegmentLCD_LowerSegments(result);
};

void render_text_gameover() {
	result[0] = CHARMAP_R;
	result[1] = CHARMAP_I;
	result[2] = CHARMAP_P;
	result[3] = CHARMAP_NUL;
	result[4] = CHARMAP_NUL;
	result[5] = CHARMAP_NUL;
	result[6] = CHARMAP_NUL;

	SegmentLCD_LowerSegments(result);
};

void render_text_clear() {
	for (uint8_t i = 0; i < 7; i++) {
		result[i] = CHARMAP_NUL;
	}

	SegmentLCD_LowerSegments(result);
};
