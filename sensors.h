// sensors.h
#ifndef SENSORS_H
#define SENSORS_H

#include <msp430fr2355.h>
#include <stdint.h>

/** ADC channel mappings for MSP430FR2355 */
#define THERMOCOUPLE_CHANNEL ADCINCH_3  /**< A3: Flame detection thermocouple */
#define THERMISTOR_CHANNEL   ADCINCH_4  /**< A4: Boiler temperature thermistor */
#define POT_CHANNEL          ADCINCH_5  /**< A5: Setpoint potentiometer     */

/** Timeout for ADC conversions */
#define ADC_TIMEOUT          100000U

/**
 * @brief Initialize ADC peripheral and unlock GPIO pins (FRAM). Must be
 *        called before any sensor or ADC read functions.
 */
void initADC(void);

/**
 * @brief Read a raw 12-bit ADC value from the specified channel.
 *        Clears previous channel selection, starts a conversion, and waits
 *        (with timeout) for completion.
 *
 * @param channel  ADCINCH_x macro specifying the input channel
 * @return         12-bit ADC result (0–4095), or 0xFFFF on timeout
 */
uint16_t readADC(uint16_t channel);

/**
 * @brief Read boiler temperature from the thermistor on A4.
 * @return Raw ADC counts (0–4095) or calibrated units if implemented
 */
uint16_t readThermistor(void);

/**
 * @brief Read flame-detection thermocouple on A3 (cold-junction comp optional).
 * @return Raw ADC counts (0–4095) or temperature units
 */
uint16_t readThermocouple(void);

/**
 * @brief Read setpoint value from the potentiometer on A5.
 * @return Raw ADC counts (0–4095)
 */
uint16_t readPot(void);

#endif // SENSORS_H


// sensors.c
#include "sensors.h"

static volatile uint16_t ADCResult   = 0;
static volatile uint8_t  ADCFinished = 0;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    if (ADCIV == ADCIV_ADCIFG) {
        ADCResult   = ADCMEM0;
        ADCFinished = 1;
    }
}

void initADC(void) {
    PM5CTL0 &= ~LOCKLPM5;            // Unlock GPIO on FRAM devices
    // Configure A3, A4, A5 pins
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT3 | BIT4 | BIT5;

    // ADC configuration
    ADCCTL0 = ADCSHT_2 | ADCON;      // Sample-and-hold, ADC on
    ADCCTL1 = ADCSHP;                // Use sampling timer
    ADCCTL2 = ADCRES_2;              // 12-bit resolution
    ADCIE |= ADCIE0;                 // Enable interrupt
    // Preselect default channel
    ADCMCTL0 = THERMOCOUPLE_CHANNEL;
    ADCCTL0 |= ADCENC;
}

static uint16_t readADC_raw(uint16_t channel) {
    ADCCTL0 &= ~ADCENC;              // Disable conversions to change channel
    ADCMCTL0 = channel;              // Select channel
    ADCFinished = 0;
    ADCCTL0 |= ADCENC | ADCSC;       // Start conversion
    uint32_t timeout = ADC_TIMEOUT;
    while (!ADCFinished && --timeout);
    return timeout ? ADCResult : 0xFFFF;
}

uint16_t readADC(uint16_t channel) {
    return readADC_raw(channel);
}

uint16_t readThermistor(void) {
    return readADC_raw(THERMISTOR_CHANNEL);
}

uint16_t readThermocouple(void) {
    return readADC_raw(THERMOCOUPLE_CHANNEL);
}

uint16_t readPot(void) {
    return readADC_raw(POT_CHANNEL);
}
