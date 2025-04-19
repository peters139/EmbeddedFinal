#include <msp430.h>
#include "Ignitor_LED.h"

void ignitor_led_init(void)
{
    // Set P2.0 as output
    P2DIR |= BIT0;
    // Turn off LED initially
    P2OUT &= ~BIT0;
}

void ignitor_led_on(void)
{
    P2OUT |= BIT0;  // Set P2.0 high
}

void ignitor_led_off(void)
{
    P2OUT &= ~BIT0; // Set P2.0 low
}

void ignitor_led_toggle(void)
{
    P2OUT ^= BIT0;  // Toggle P2.0
}
