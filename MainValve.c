#include "MainValve.h"

#define PWM_PERIOD 20000            // 20ms period for 50Hz (in Timer ticks)
#define MIN_PULSE 1000              // 1ms pulse width
#define MAX_PULSE 2000              // 2ms pulse width

/**
 * @brief Initialize Timer_A0 CCR1 output on P5.0 for PWM
 */
void MainValve_Init(void) {
    // Configure P5.0 as Timer_A0.1 output
    P5DIR |= BIT0;                  // Set P5.0 as output
    P5SEL0 |= BIT0;                 // Select primary module function
    P5SEL1 &= ~BIT0;

    // Timer_B0 configuration
    TA0CCR0 = PWM_PERIOD - 1;       // Set period for 50Hz
    TA0CCTL1 = OUTMOD_7;            // Reset/Set output mode
    TA0CCR1 = MIN_PULSE;            // Default to minimum (valve closed)
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR; // SMCLK, up mode, clear TAR
}

/**
 * @brief Set the main valve position via PWM duty cycle
 * @param position 0-255
 */
void MainValve_Set(uint8_t position) {
    // Map 0-255 to pulse width range MIN_PULSE to MAX_PULSE
    uint32_t pulse = MIN_PULSE + ((uint32_t)position * (MAX_PULSE - MIN_PULSE)) / 255;
    TA0CCR1 = pulse;
}
