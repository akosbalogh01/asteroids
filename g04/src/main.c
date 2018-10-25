#include "em_device.h"
#include "em_chip.h"
#include "em_usart.h"
#include "InitDevice.h"

#include <stdint.h>
#include <stdbool.h>
uint8_t volatile   ch;
bool    volatile flag;


UART0_RX_IRQHandler(void) {
   ch = USART_RxDataGet(UART0);
   flag = true;
   //Ack IRQ (automatically)
   //USART_IntClear(UART0, USART_IF_RXDATAV);
}

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  // Init board
  enter_DefaultMode_from_RESET();

  // Send test char
  USART_Tx(UART0, '%');

  // Enable UART0 Rx 'Data Valid' IRQ
  USART_IntEnable(UART0, USART_IF_RXDATAV);

  // Enable UART0 IRQ in MCU (nested vector interrupt controller - NVIC) (btw if more than one interrupt is present in the system, check for IRQ type)
  NVIC_EnableIRQ(UART0_RX_IRQn);

  /* Infinite loop */
  while (1) {

     //USART_Tx(UART0, USART_Rx(UART0) - 'a' + 'A');
     if (flag) {
        USART_Tx(UART0, ch);
        flag = false;
     }
  }
}
