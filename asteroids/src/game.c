#include <stdlib.h>
#include "em_timer.h"
#include "game.h"

int decrement(int level, int cycle) {
	return cycle = cycle - level * 100;
};

void generate_field(logic* program) {
	srand(TIMER_CounterGet (TIMER0));

	uint8_t i, temp;
	for (i = 0; i < 3; i++) {
		temp = rand() % 6;
		program->asteroids[i] += temp;
		temp = rand() % 6;
		program->asteroids[i] += (1 + temp) * 10;
	}
};

void spaceship_rotate(logic* program) {
	register uint8_t temp = program->spaceship % 6;
	register uint8_t dec  = (program->spaceship - temp) / 10;

	if (program->params.left && temp != 3) {
		switch (temp) {
		case 0:	program->spaceship = dec + 2; break;
		case 1: program->spaceship = dec + 2; break;
		case 2: program->spaceship = dec + 4; break;
		case 4: program->spaceship = dec + 3; break;
		case 5: program->spaceship = dec + 4; break;
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
		case 5: program->spaceship = dec + 4; break;
		default: break;
		};

		program->params.right = 0;
		return;
	}
}

int spaceship_move(logic* program) {

	return 0;
}
