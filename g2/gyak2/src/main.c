#include "em_device.h"
#include "em_chip.h"

#define HFPCE (*(volatile long unsigned int*) (0x400c8000 + 0x044))
#define GPIO_PB_MODEH (*(volatile long unsigned int*) (0x40006000 + 0x02c))
#define GPIO_PB_DIN (*(volatile long unsigned int*) (0x40006000 + 0x040))
#define GPIO_PE_MODEL (*(volatile long unsigned int*) (0x40006000 + 0x094))
#define GPIO_PE_DOUT (*(volatile long unsigned int*) (0x40006000 + 0x09c))
#define lofasz 20000000

int main(void)
{
   long int timer = 0;
  /* Chip errata */
  CHIP_Init();
  HFPCE  |= 1<<13; //GPIO
  GPIO_PB_MODEH |= ((1<<8)|(1<<4));    //pb9 pb10 input mode
  GPIO_PE_MODEL |= ((4<<8)|(4<<12)); // pe2 pe3 pushpull mode

  /* Infinite loop */
  while (1) {
     unsigned long int buttons0 = GPIO_PB_DIN & (1<<9);
     unsigned long int buttons1 = GPIO_PB_DIN & (1<<10);

     unsigned long int temp ;

     if ((++timer == lofasz) && (buttons0 | buttons1)) {

        buttons0 = buttons0 >> 6;
        buttons1 = buttons1 >> 8;

        temp = (~(buttons0 | buttons1));
     }
     else if (!(buttons0 | buttons1)) {
        timer = 0;
        temp = (~(buttons0 | buttons1))>>7;
     }

     GPIO_PE_DOUT = temp & 0b1100 ;  //mask off non-led bits - azért ilyen kicsi a szám mert a többi alapból nulla 1100= ...00001100
   }
}


