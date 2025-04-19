#include <msp430.h>
#include "CallforHeat.h"

void CallforHeat_Init(void)
{
    // Set P1.2 as input
    P1DIR &= ~BIT2;

    // Enable pull-up resistor (assuming button press pulls pin LOW)
    P1REN |= BIT2;   // Enable resistor
    P1OUT |= BIT2;   // Configure as pull-up
}

unsigned char CallforHeat_Active(void)
{
    // Return 1 if button is pressed (pin is LOW), else 0
    return !(P1IN & BIT2);
}

