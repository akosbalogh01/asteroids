/*	Interrupt weak function redefinitions, other interrupt related function prototypes
 *	Daniel Balogh @ BME-VIK
 *	2018-11-10
 *	v1.0
 */

#ifndef ASTEROIDS_INTERRUPT
#define ASTEROIDS_INTERRUPT

#include "stdbool.h"
#include "game.h"

uint8_t 		volatile ch;
bool    		volatile flag;
uint8_t 		volatile x;
IRQ_VARIABLES 	volatile irq_var;

void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
void UART0_Init(void);
void UART0_RX_IRQHandler(void);

#endif // ASTEROIDS_INTERRUPT
