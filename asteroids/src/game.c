#include <stdlib.h>
#include "segmentlcd.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_chip.h"
#include "em_timer.h"
#include "em_lcd.h"
#include "game.h"
#include "interrupt.h"

int decrement(int level, int cycle) {
	return (cycle - (level * 50) > MINIMAL_MOVECYCLE) ? cycle -= level * 50 : cycle;
};

void initialize() {
	CHIP_Init();
	SegmentLCD_Init(false);
	TIMER0_Init();
	UART0_Init();

	TIMER_Enable(TIMER0, true);
}

void generate_field(logic* program) {
	srand(TIMER_CounterGet (TIMER0));

	uint8_t i, temp;
	for (i = 0; i < 3; i++) {
		program->asteroids[i] = 0;
		temp = rand() % 5;
		program->asteroids[i] += temp;
		temp = rand() % 6;
		program->asteroids[i] += ((1 + temp) * 10);
	}
};

void spaceship_rotate(logic* program) {
	register uint8_t temp = program->spaceship % 5;
	register uint8_t dec  = (program->spaceship - temp) / 10;

	if (program->params.left && temp != 3) {
		switch (temp) {
		case 0:	program->spaceship = dec + 2; break;
		case 1: program->spaceship = dec + 2; break;
		case 2: program->spaceship = dec + 4; break;
		case 4: program->spaceship = dec + 3; break;
		default: break;
		};
		program->params.left = 0;
		return;
	}

	if (program->params.right && temp != 2) {
		switch (temp) {
		case 0: program->spaceship = dec + 3; break;
		case 1: program->spaceship = dec + 3; break;
		case 3: program->spaceship = dec + 4; break;
		case 4: program->spaceship = dec + 2; break;
		default: break;
		};

		program->params.right = 0;
		return;
	}
}

int spaceship_move(logic* program) {
	register uint8_t temp = program->spaceship % 5;
	register uint8_t dec  = (program->spaceship - temp) / 10;

	switch (temp) {
	case 0: program->spaceship = ((dec + 1) * 10) + 0; break;
	case 1: program->spaceship = ((dec + 1) * 10) + 1; break;
	case 2: break;
	case 3: break;
	case 4: program->spaceship = ((dec + 1) * 10) + 4; break;
	case 5: break;
	default: break;
	}

	if (dec >= 6) {
		program->spaceship = temp;
		return 1;
	}

	return 0;
}








































