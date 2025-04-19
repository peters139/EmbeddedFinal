#include <msp430.h>

// Initializes P2.5 as output for the pilot valve (solenoid)
void PilotValve_Init(void) {
    P2DIR |= BIT5;    // Set P2.5 as output
    P2OUT &= ~BIT5;   // Initialize to LOW (valve off)
}

// Turns the pilot valve ON (sets pin high)
void PilotValve_On(void) {
    P2OUT |= BIT5;
}

// Turns the pilot valve OFF (sets pin low)
void PilotValve_Off(void) {
    P2OUT &= ~BIT5;
}

