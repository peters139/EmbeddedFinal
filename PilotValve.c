// main_valve.c
include "main_valve.h"
include <msp430fr2355.h>

// PWM definitions: 20 ms period (50 Hz), pulses between 1 and 2 ms
define PWM_PERIOD_US  (20000U - 1U)
define PWM_MIN_US      1000U
define PWM_MAX_US      2000U

void mainValve_init(void) {
    // Unlock GPIO power-on default high-impedance mode (FRAM)
    PM5CTL0 &= ~LOCKLPM5;

    // Configure P5.0 for Timer_B1 CCR1 output
    P5DIR  |= MAIN_VALVE_PIN;
    P5SEL0 |= MAIN_VALVE_PIN;
    P5SEL1 &= ~MAIN_VALVE_PIN;

    // Timer_B1 setup: SMCLK, up mode, clear TAR
    TB1CTL   = TBSSEL__SMCLK | MC__UP | TBCLR;
    TB1CCR0  = PWM_PERIOD_US;            // Set period (20 ms)
    TB1CCTL1 = OUTMOD_7;                 // Reset/Set on CCR1
    TB1CCR1  = PWM_MIN_US;               // Initialize to minimum pulse
}

void mainValve_set(uint8_t position) {
    // Map 0–255 to 1000–2000 µs pulse width
    uint32_t range = PWM_MAX_US - PWM_MIN_US;
    uint32_t pulse = PWM_MIN_US + (range * position) / 255U;
    TB1CCR1 = (uint16_t)pulse;
}
