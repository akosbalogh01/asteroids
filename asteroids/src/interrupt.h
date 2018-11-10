/*
 * interrupt.h
 *
 *  Created on: 2018. nov. 10.
 *      Author: User
 */

#ifndef SRC_INTERRUPT_H_
#define SRC_INTERRUPT_H_

#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "em_timer.h"

#include "stdint.h"
#include "stdbool.h"


void TIMER0_Init(void){
	  //ena timer clock but cant count while initialization
	  CMU_ClockEnable(cmuClock_TIMER0,true);
	  TIMER_Enable(TIMER0, false);
	  //init timer0
	  TIMER_Init_TypeDef confTimer=TIMER_INIT_DEFAULT;
	  confTimer.prescale=timerPrescale1024;
	  confTimer.clkSel=timerClkSelHFPerClk;
	  confTimer.mode=timerModeUp;
	  TIMER_Init(TIMER0, &confTimer);
	  //init compare/capture to no action: mode no compare/capture/PWM
	  TIMER_InitCC_TypeDef confCC=TIMER_INITCC_DEFAULT;
	  TIMER_InitCC(TIMER0,0,&confCC);
	  //set top buffer for time period
	  uint32_t Timer0_Top = 0xFFFF;
	  TIMER_TopSet(TIMER0, Timer0_Top);
	  //clear all interrupt flag
	  TIMER_IntClear(TIMER0, _TIMER_IFC_MASK);
	  //enable interrupt only on overflow(timer count up)(disable others)
	  TIMER_IntDisable(TIMER0, _TIMER_IEN_MASK);
	  TIMER_IntEnable(TIMER0, TIMER_IEN_OF);
	  NVIC_EnableIRQ(TIMER0_IRQn);
}
void UART0_Init(void){
	  //ena clock gpio (first!)(without clock cant be modified)
	  CMU_ClockEnable(cmuClock_GPIO, true);
	  //pass uart thru
	  GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 1);
	  //ena uart clock
	  CMU_ClockEnable(cmuClock_UART0, true);
	  //init uart0 baud:11500, frame: 8N1
	  USART_InitAsync_TypeDef conf=USART_INITASYNC_DEFAULT; //van egy default ertek es mi is pont azt szeretnenk egyebkent
		conf.autoCsEnable=0;
		conf.baudrate=115200;
		conf.databits=usartDatabits8; // enum erteke 5 !!! nem 8
		conf.enable= usartEnable;
		conf.mvdis= false; //majority voting disabled: 16x tulmintavetelezesnel a közepsõ 3 bol 2 is eleg-e
		conf.oversampling=usartOVS16;
		conf.parity=usartNoParity;
		conf.prsRxCh= usartPrsRxCh0;//peripheral Reflex System (periferiak egymasnbak tudnak özenni pl: interrapt közvetlen az usartnak szol)
		conf.prsRxEnable  =false;
		conf.refFreq=0; //ha 0 akkor lekeredezi mekkora az orajelfrekvenciaja amit kap az usart
		conf.stopbits=usartStopbits1;
	  USART_InitAsync(UART0, &conf);//azert cim szerint mert nagy a struct es minek masolgasson
	  //megmondjuk hogy a Rx es Tx melyik GPIO pineken legyen - beallitjuk a GPIO I/O-kat, aztan kivalasztjuk hogy mit csatolunk ra
	  GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
	  GPIO_PinModeSet(gpioPortE, 1, gpioModePushPull, 1);
	  // did you just assume my reset?
	  UART0->ROUTE |= (USART_ROUTE_LOCATION_LOC1 | USART_ROUTE_RXPEN | USART_ROUTE_TXPEN);

	  // Send test char
	  USART_Tx(UART0, '%');

	  // Enable UART0 Rx 'Data Valid' IRQ
	  USART_IntEnable(UART0, USART_IF_RXDATAV);
	  // Enable UART0 IRQ in MCU (nested vector interrupt controller - NVIC) (btw if more than one interrupt is present in the system, check for IRQ type)
	  NVIC_EnableIRQ(UART0_RX_IRQn);


}

#endif /* SRC_INTERRUPT_H_ */
