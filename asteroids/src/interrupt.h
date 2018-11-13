/*	Interrupt weak function redefinitions
 *	Daniel Balogh @ BME-VIK
 *	2018-11-10
 *	v1.0
 */

#ifndef ASTEROIDS_INTERRUPT
#define ASTEROIDS_INTERRUPT

#include "em_usart.h"
#include "em_timer.h"

void TIMER0_Init(void);
void TIMER0_IRQHandler(void);
void UART0_Init(void);
void UART0_RX_IRQHandler(void);

#endif // ASTEROIDS_INTERRUPT
