// rgb_led.c
#include "rgb_led.h"

void rgb_init(void) {
    // Unlock GPIO power-on default high-impedance mode
    PM5CTL0 &= ~LOCKLPM5;

    // Configure P6.0-6.2 for Timer_B2 outputs
    P6DIR  |= RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN;
    P6SEL0 |= RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN;
    P6SEL1 &= ~(RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN);

    // Timer_B2 setup: SMCLK, up mode, clear TAR
    TB2CTL   = TBSSEL__SMCLK | MC__UP | TBCLR;
    TB2CCR0  = RGB_PWM_PERIOD;
    TB2CCTL1 = OUTMOD_7;  // Reset/Set on CCR1
    TB2CCTL2 = OUTMOD_7;  // Reset/Set on CCR2
    TB2CCTL3 = OUTMOD_7;  // Reset/Set on CCR3

    // Initialize duty cycles to 0 (LEDs off)
    TB2CCR1 = 0;
    TB2CCR2 = 0;
    TB2CCR3 = 0;
}

void rgb_set(uint8_t red, uint8_t green, uint8_t blue) {
    TB2CCR1 = red;
    TB2CCR2 = green;
    TB2CCR3 = blue;
}

void rgb_off(void) {
    TB2CCR1 = 0;
    TB2CCR2 = 0;
    TB2CCR3 = 0;
}
