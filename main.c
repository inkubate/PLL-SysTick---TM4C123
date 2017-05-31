
#include "tm4c123gh6pm.h"
#include "CR_defin.h"
#include "stdint.h"
#include "pllsetup.h"
#include "delay.h"

int main()

{
  SYSCTL_RCGCGPIO_R = 0x20U; //enable clock to GPIO bank F (clock gating ctl)
  GPIO_PORTF_DIR_R = 0x0EU; //set port direction to output 1,2,3
  GPIO_PORTF_DEN_R = 0x0EU; //set digital enable on pins 1,2,3
  
  pllsetup(); // setup the PLL for desired freq
  
  while(1) {
  //GPIO_PORTF_DATA_R = 0x02U; //GPIO 1 set to '1' and 2,3 set '0'
  //delay(100);
  
  //GPIO_PORTF_DATA_R ^= 0x04U; //GPIO toggle 2 to on
  
  GPIO_PORTF_DATA_R ^= 0x02U; //GPIO toggle 3 on and 2 off
  delay(50);
  
  }
   return 0;
}

