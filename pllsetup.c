#include "stdint.h"
#include "tm4c123gh6pm.h"

#define RCC_XTAL_BITS 0x7C0             // these are the xtal bits in SYSCTL_RCC_R
#define OSCSRC2_BITS 0x70               // oscillitor source bits in SYSCTL_RCC2_R
#define SYSDIV2_BITS 0x1FC00000         // SYSDIV bits incl. SYSDIV LSB (LSB used in DIV400 mode) SYSCTL_RCC2_R
#define MHZ_80 0x1000000                // bit setting for 80MHz
#define MHZ_40 0x2400000                // bit setting for 40MHz
#define MHZ_3 0x1FC00000                // bit setting for 3.125MHz

void pllsetup() {
SYSCTL_RCC_R &= (~RCC_XTAL_BITS);                       // clear bits 10-6 for xtal
SYSCTL_RCC_R |= SYSCTL_RCC_XTAL_16MHZ;                  //define a 16MHz crystal 
SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV;                   //use sysdiv

SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;                   // use RCC2 fields instead of RCC
SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;                   // bypass the PLL while setup - bit to 1
SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;                    // use DIV400 
SYSCTL_RCC2_R &= (~SYSDIV2_BITS);                       // clear sysdiv bits ready to set them
SYSCTL_RCC2_R |= (SYSDIV2_BITS & MHZ_80);                // set SYSDIV2 for required freq

SYSCTL_RCC2_R &= (~OSCSRC2_BITS);                       // clear bits 4 to 6. This also sets main OSC as all bits 0 
SYSCTL_RCC2_R &= (~SYSCTL_RCC2_PWRDN2);               // power up PLL by making the bit 0

while((SYSCTL_RIS_R & 0x00000040)==0){};                // wait for PLLRIS bit
SYSCTL_RCC2_R &= (~SYSCTL_RCC2_BYPASS2);                // remove bypass and use the PLL - bit to 0
}