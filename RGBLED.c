#include "msp430fr2355.h"
#include <msp430.h>

void RGB_Init(){
    P6DIR |= BIT0 | BIT1 | BIT2;                     // P6.0 and P6.1 and P6.2 output
    P6SEL0 |= BIT0 | BIT1 |BIT2;                    // P6.0 and P6.1 and P6.2 options select
    
    TB3CCR0 = 1000-1;                         // PWM Period
    TB3CCTL1 = OUTMOD_3;                      // CCR1 reset/set
    TB3CCR1 = 750;                            // CCR1 PWM duty cycle
    TB3CCTL2 = OUTMOD_3;                      // CCR2 reset/set
    TB3CCR2 = 250;                            // CCR2 PWM duty cycle
    TB3CCTL3 = OUTMOD_3;                      // CCR3 reset/set
    TB3CCR3 = 100;                             // CCR3 PWM duty cycle
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;  // SMCLK, up mode, clear TBR
}


//change RGBLED takes in 0-255 and produces the correct duty cycle
void changeRGBLED(char Red, char Green, cha Blue){
    TB3CCR1 = Blue <<2; //Set Blue duty cycle
    TB3CCR2 = Green <<2 //Set Green duty cycle
    TB3CCR3 = Red <<2 // Set Red duty cycle
}
