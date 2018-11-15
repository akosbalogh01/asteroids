/*
 * Interrupt related function implementations
 * Daniel Balogh @ BME-VIK
 * 2018-11-10
 */

#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_timer.h"

#include "stdint.h"
#include "stdbool.h"

#include "interrupt.h"
#include "game.h"

void TIMER0_Init(void) {
	  CMU_ClockEnable(cmuClock_TIMER0,true);		//enable external clock
	  TIMER_Enable(TIMER0, false);					//enable timer
	  TIMER_Init_TypeDef confT=TIMER_INIT_DEFAULT;	//timer configuration variable
	  confT.prescale=timerPrescale1024;
	  confT.clkSel=timerClkSelHFPerClk;
	  confT.mode=timerModeUp;
	  TIMER_Init(TIMER0, &confT);					//initialize timer
	  TIMER_InitCC_TypeDef confCC=TIMER_INITCC_DEFAULT;
	  TIMER_InitCC(TIMER0,0,&confCC);
	  TIMER_TopSet(TIMER0, DEFAULT_MOVE_CYCLE); 	//timer maximum
	  TIMER_IntClear(TIMER0, _TIMER_IFC_MASK);		//clear all interrupt flags
	  TIMER_IntDisable(TIMER0, _TIMER_IEN_MASK);	//disable all timer interrupts
	  TIMER_IntEnable(TIMER0, TIMER_IEN_OF);		//enable timer overflow interrupt
	  NVIC_EnableIRQ(TIMER0_IRQn);
}

void UART0_Init(void) {
	  CMU_ClockEnable(cmuClock_GPIO, true);					//enable GPIO clock
	  GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 1); 	//enable UART passthrough
	  CMU_ClockEnable(cmuClock_UART0, true);				//enable UART clock

	  USART_InitAsync_TypeDef conf=USART_INITASYNC_DEFAULT; //configure UART0: baud - 11500, frame - 8N1
		conf.autoCsEnable = 0;
		conf.baudrate = 115200;
		conf.databits = usartDatabits8;
		conf.enable = usartEnable;
		conf.mvdis = false;
		conf.oversampling = usartOVS16;
		conf.parity = usartNoParity;
		conf.prsRxCh = usartPrsRxCh0;
		conf.prsRxEnable = false;
		conf.refFreq = 0;
		conf.stopbits = usartStopbits1;
	  USART_InitAsync(UART0, &conf);						//initizalize UART0, with the above config
	  GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);	//assign GPIO pins to Rx and Tx
	  GPIO_PinModeSet(gpioPortE, 1, gpioModePushPull, 1);
	  UART0->ROUTE |= (USART_ROUTE_LOCATION_LOC1 | USART_ROUTE_RXPEN | USART_ROUTE_TXPEN);

	  USART_Tx(UART0, '%');									//send text character

	  USART_IntEnable(UART0, USART_IF_RXDATAV);				// Enable UART0 Rx 'Data Valid' IRQ
	  NVIC_EnableIRQ(UART0_RX_IRQn);						// Enable UART0 IRQ in MCU (nested vector interrupt controller - NVIC)
}

void UART0_RX_IRQHandler(void) {
   ch = USART_RxDataGet(UART0); //acknowledge IRQ (automatically)
   switch (ch){
   case 'j' : irq_var.right 	= 1; irq_var.left  = 0; break;
   case 'b' : irq_var.left  	= 1; irq_var.right = 0; break;
   case 's' : irq_var.start 	= 1; break;
   case 'r' : irq_var.ragequit  = 1; break;
   default: break;
   }

   USART_Tx(UART0, ch);
   ch = 0;
}

void TIMER0_IRQHandler(void) {
	TIMER_IntClear(TIMER0, TIMER_IF_OF);
	USART_Tx(UART0, '.');
	flag = true;
}
