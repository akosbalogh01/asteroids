#include "em_device.h"
#include "em_chip.h"
#include "game.h"

/* D:
 * interrupts + copy
 * timer
 * A:
 * rendering
 * field gen
 */

//render_spaceship();
//render_asteroids();
//generate_map();

int main(void) {
	logic program = {0};
	program.status = NEW_GAME;
	/* Chip errata */
	CHIP_Init();

	while (1) {
		//copy status parameters, atomic copy
		switch (program.status) {
		case NEW_GAME:
			//render new game screen
			//if buttonpressed - request status params - move to RUNNING
			//conditional break;
		case LEVEL_UP:
			//decrement move cycle time
			//generate new asteroid field
			//no break;
		case RUNNING:
			//render everything
				//render spaceship
				//render asteroids
				//render score
			//timer
			//move spaceship
			//collision detection
			//if last segments, and still alive, LEVEL_UP
			//if collided or ragequit, move to GAME_OVER
			break;
		case GAME_OVER:
			//render game over screen with flashing decimal points!
			//reset status variables
			//if buttonpressed - request status params - move to NEW_GAME
			break;
		default: //nagyon nagy a baj
		};
	}

	return 0;
}
