/*	development comments:
 * 	render_score: 	it's possible the digit indexing is the other way around, than what is currently implemented,
 * 				  	but i had no means of testing it (digit0 is on the left, or on the right?)
 *	render_text_*:	the same question applies to any text rendering functions
 *	render*:		turns out, every rendering function needs confirmation, regarding digit index order
 */

#include "segmentlcd.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_chip.h"
#include "em_timer.h"
#include "em_lcd.h"
#include "game.h"
#include "interrupt.h"

int main(void) {
	CHIP_Init();
	SegmentLCD_Init(false);
	TIMER0_Init();
	UART0_Init();

	logic program = {0};
	program.status = NEW_GAME;

	TIMER_Enable(TIMER0, true);

	while (1) {
		CORE_CRITICAL_SECTION(
			program.params = irq_var;
			irq_var.start = 0;
			irq_var.ragequit = 0;
			irq_var.left = 0;
			irq_var.right = 0;
		)

		switch (program.status) {
		case NEW_GAME:
			SegmentLCD_Write("NEWGAME");
			if (program.params.start) {
				SegmentLCD_AllOff();
				program.status    	 = RUNNING;
				program.level 	  	 = NULL;
				program.asteroids[0] = 0;
				program.asteroids[1] = 0;
				program.asteroids[2] = 0;
				program.direction 	 = DEFAULT_MOVE_DIRECTION;
				program.spaceship 	 = DEFAULT_SPACESHIP_POSITION;
				program.movecycle 	 = DEFAULT_MOVE_CYCLE;
				program.params.start = 0;
			}
			else break;
			/* no break */

		case LEVEL_UP:
			program.level++;
			program.movecycle = decrement(program.level, program.movecycle);
			TIMER_TopSet(TIMER0, program.movecycle);
			generate_field(&program);
			/* no break */

		case RUNNING:;
			uint8_t i;
			SegmentLCD_Number(program.level);

			render_level(program.spaceship, program.asteroids);
			spaceship_rotate(&program);

			if (flag) {
				switch (spaceship_move(&program)) {
				case 1: program.status = LEVEL_UP;
						break;
				case -1: program.status = GAME_OVER;
						 break;
				default: break;
				}
			}

			for (i = 0; program.status == RUNNING && i < 3; i++) if (program.spaceship == program.asteroids[i]) break;
			if (i != 3 || program.params.ragequit) {
				program.params.ragequit = 0;
				program.status = GAME_OVER;
			}

			break;

		case GAME_OVER:
			SegmentLCD_Number(program.level);
			SegmentLCD_Write("RIP");
			if (program.params.start) {
				SegmentLCD_AllOff();
				program.params.start = 0;
				program.status = NEW_GAME;
			}
			break;

		default: //nagyon nagy a baj
			break;
		};
	}
	return 0;
}
