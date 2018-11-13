#include "em_device.h"
#include "em_chip.h"
#include "game.h"
#include "interrupt.h"


#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_timer.h"
#include "interrupt.h"

uint8_t volatile   ch;
bool    volatile flag;
uint8_t volatile x;

void UART0_RX_IRQHandler(void) {
   ch = USART_RxDataGet(UART0);
   flag = true;
   //Ack IRQ (automatically)
   //USART_IntClear(UART0, USART_IF_RXDATAV);
}
void TIMER0_IRQHandler(void) {
	TIMER_IntClear(TIMER0,TIMER_IF_OF);
	//k�ldj�nk ki karaktert hogy l�ssuk működni
	if(x>=10){
		x=0;
		USART_Tx(UART0, '0');
	}
	x++;
}
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
	/*Timer0 init*/
	TIMER0_Init();
	/*Uart0 init*/
	UART0_Init();

	//ezzel lehet elkezdeni a számolást az interrupthoz
  	TIMER_Enable(TIMER0,true);


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
			break;
		};
	}

	return 0;
}
