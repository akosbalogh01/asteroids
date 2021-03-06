#include "segmentlcd.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_lcd.h"
#include "em_timer.h"
#include "game.h"
#include "interrupt.h"

int main(void) {
	//initialize hardware and software components
	initialize();

	logic program = {0};
	program.status = NEW_GAME;

	while (1) {
		//atomic copy of <IRQ modifiable> global variables, to game descriptor
		//business logic is done entirely based on the game game descriptor structure
		CORE_CRITICAL_SECTION(
			program.params = irq_var;
			irq_var.start = 0;
			irq_var.ragequit = 0;
			irq_var.left = 0;
			irq_var.right = 0;
		)

		switch (program.status) {
		//new game, wait for <Start>
		case NEW_GAME:
			SegmentLCD_Write("NEWGAME");
			if (program.params.start) { //if start was pressed, move to <Running>
				SegmentLCD_AllOff();
				program.status    	 = RUNNING;
				program.level 	  	 = 0;
				program.asteroids[0] = 0;
				program.asteroids[1] = 0;
				program.asteroids[2] = 0;
				program.orientation  = DEFAULT_MOVE_DIRECTION;
				program.spaceship 	 = DEFAULT_SPACESHIP_POSITION;
				program.movecycle 	 = DEFAULT_MOVE_CYCLE;
				program.params.start = 0;
			}
			else break;
			/* no break */

		//level up, initializes and modifies required variables, be it starting a new game, or moving between levels
		case LEVEL_UP:
			program.level++;
			program.movecycle = decrement(program.level, program.movecycle);
			TIMER_TopSet(TIMER0, program.movecycle);
			generate_field(&program);
			flag = 0;
			program.status = RUNNING;
			/* no break */

		//game is running
		case RUNNING:;
			uint8_t i;
			for (i = 0; i < 3; i++) {if (program.asteroids[i] == program.spaceship) break;}
			if (i != 3) {program.status = GAME_OVER; break;}
			SegmentLCD_Number(program.level);

			spaceship_rotate(&program);
			render_level(program.spaceship, program.asteroids);

			if (flag) {	//flag is enabled every time the TIMER0 overflows, maximum of T0 equals to <movecycle>
				switch (spaceship_move(&program)) {
				case  1: program.status = LEVEL_UP;  break;
				case -1: program.status = GAME_OVER; break;
				default: break;
				}

				flag = 0;
			}

			if (program.params.ragequit) {
				program.params.ragequit = 0;
				program.status = GAME_OVER;
			}

			break;
		
		//game over
		case GAME_OVER:
			SegmentLCD_Number(program.level);
			SegmentLCD_Write("RIP");
			if (program.params.start) {
				SegmentLCD_AllOff();
				program.params.start = 0;
				program.status = NEW_GAME;
			}
			break;
		};
	}
	return 0;
}
