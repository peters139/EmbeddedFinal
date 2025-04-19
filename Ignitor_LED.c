#include "ignitor_led.h"
#include <msp430fr2355.h>

#define IGNITOR_LED_PIN    BIT0    // P2.0

void ignitor_led_init(void) {
    P2DIR |= IGNITOR_LED_PIN;   // configure P2.0 as output
    P2OUT &= ~IGNITOR_LED_PIN;  // start with LED off
}

void ignitor_led_on(void) {
    P2OUT |= IGNITOR_LED_PIN;
}

void ignitor_led_off(void) {
    P2OUT &= ~IGNITOR_LED_PIN;
}

void ignitor_led_toggle(void) {
    P2OUT ^= IGNITOR_LED_PIN;
}
