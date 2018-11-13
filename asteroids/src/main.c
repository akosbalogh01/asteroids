/*	development comments:
 * 	render_score: 	it's possible the digit indexing is the other way around, than what is currently implemented,
 * 				  	but i had no means of testing it (digit0 is on the left, or on the right?)
 *	render_text_*:	the same question applies to any text rendering functions
 *	render*:		turns out, every rendering function needs confirmation, regarding digit index order
 */

#include "em_chip.h"
#include "game.h"
#include "interrupt.h"

int main(void) {
	CHIP_Init();
	TIMER0_Init();
	UART0_Init();

	logic program = {0};
	program.status = NEW_GAME;

  	TIMER_Enable(TIMER0,true); //start interrupt timer

	while (1) {
		//copy status parameters, atomic copy
		switch (program.status) {
		case NEW_GAME:
			render_text_newgame();
			if (program.params.start) {
				program.status    	 = RUNNING;
				program.level 	  	 = NULL;
				program.asteroids[0] = 0;
				program.asteroids[1] = 0;
				program.asteroids[2] = 0;
				program.direction 	 = DEFAULT_MOVE_DIRECTION;
				program.spaceship 	 = DEFAULT_SPACESHIP_POSITION;
				program.movecycle 	 = DEFAULT_MOVE_CYCLE;
			}
			else break;
			/* no break */

		case LEVEL_UP:
			program.movecycle = decrement(program.level, program.movecycle);
			generate_field(&program);
			/* no break */

		case RUNNING:
			render_level(program.spaceship, program.asteroids);
			render_score(program.level);
			//timer

			uint8_t i;
			for (i = 0; i < 3; i++) if (program.spaceship == program.asteroids[i]) break;
			if (i != 3 || program.params.ragequit) {program.status = GAME_OVER; break;}

			//move spaceship
			//if last segments, and still alive, LEVEL_UP
			break;

		case GAME_OVER:
			render_score(program.level);
			render_text_gameover();
			if (program.params.start) program.status = NEW_GAME;
			break;

		default: //nagyon nagy a baj
			break;
		};
	}

	return 0;
}
