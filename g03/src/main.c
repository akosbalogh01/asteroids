#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
/* :d
#define
#define
#define
#define
#define
#define
#define
#define
*/

#define HFPCE (*(volatile long unsigned int*) (0x400c8000 + 0x044))
#define GPIO_PB_MODEH (*(volatile long unsigned int*) (0x40006000 + 0x02c))
#define GPIO_PE_MODEL (*(volatile long unsigned int*) (0x40006000 + 0x094))
#define GPIO_PB_DIN (*(volatile long unsigned int*) (0x40006000 + 0x040))

int main(void)
{
  /* Chip errata */
  CHIP_Init();
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
  conf.mvdis= false; //majority voting disabled: 16x tulmintavetelezesnel a közepső 3 bol 2 is eleg-e
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

  //USART_Tx(UART0, '[');

  HFPCE  |= 1<<13; //GPIO
  GPIO_PB_MODEH |= ((1<<8)|(1<<4));    //pb9 pb10 input mode
  GPIO_PE_MODEL |= ((4<<8)|(4<<12)); // pe2 pe3 pushpull mode

  /* Infinite loop */
  while (1) {
     unsigned long int buttons0 = GPIO_PB_DIN & (1<<9);
     unsigned long int buttons1 = GPIO_PB_DIN & (1<<10);

     if (!buttons0)
           USART_Tx(UART0, '+');
     else if (!buttons1)
           USART_Tx(UART0, '-');
  }
}
