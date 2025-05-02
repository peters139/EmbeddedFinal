#include <msp430.h>
#include "MainValve.h"

// — adjust these to match your board’s wiring —
#define MAINVALVE_PIN_DIR   P2DIR
#define MAINVALVE_PIN_SEL   P2SEL
#define MAINVALVE_PIN       BIT1   // e.g. P2.1 → TA0.1

// Timer parameters for 50 Hz PWM (20 ms period @ SMCLK=1 MHz)
#define TIMER_PERIOD        20000U
#define SERVO_MIN_PULSE     1000U   // 1 ms pulse → fully closed
#define SERVO_MAX_PULSE     2000U   // 2 ms pulse → fully open

void MainValve_Init(void)
{
    // 1) Stop watchdog
    WDTCTL = WDTPW | WDTHOLD;

    // 2) Configure P2.1 as TA0CCR1 output
    MAINVALVE_PIN_DIR |= MAINVALVE_PIN;  
    MAINVALVE_PIN_SEL |= MAINVALVE_PIN;  

    // 3) Timer_A0 setup: SMCLK @ 1 MHz, Up mode
    TA0CCR0 = TIMER_PERIOD - 1;      // Period = 20 000 ticks
    TA0CCTL1 = OUTMOD_7;             // Reset/Set output mode
    TA0CCR1 = SERVO_MIN_PULSE;       // Start “closed”

    TA0CTL = TASSEL_2 | MC_1 | TACLR; // SMCLK, Up mode, clear TAR
}

void MainValve_Set(uint8_t position)
{
    // Scale 0–255 → 1000–2000 ticks
    uint32_t span = (uint32_t)(SERVO_MAX_PULSE - SERVO_MIN_PULSE);
    uint32_t pulse = SERVO_MIN_PULSE + ((uint32_t)position * span) / 255U;

    // Clamp just in case
    if (pulse >= TIMER_PERIOD) {
        pulse = TIMER_PERIOD - 1;
    }

    TA0CCR1 = (uint16_t)pulse;
}
