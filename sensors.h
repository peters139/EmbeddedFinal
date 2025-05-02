#define THERMOCOUPLE_CHANNEL ADCINCH_3  /**< A3: flame thermocouple */
#define THERMISTOR_CHANNEL   ADCINCH_4  /**< A4: boiler temperature */
#define POT_CHANNEL          ADCINCH_5  /**< A5: setpoint potentiometer */

#define ADC_TIMEOUT          100000U    /**< loop count before giving up */

void     initADC(void);
uint16_t readADC(uint16_t channel);

uint16_t readThermistor(void);
uint16_t readThermocouple(void);
uint16_t readPot(void);

static volatile uint16_t ADCResult   = 0;
static volatile uint8_t  ADCFinished = 0;

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    if (ADCIV == ADCIV_ADCIFG) {
        ADCResult   = ADCMEM0;   // grab the 12‑bit result
        ADCFinished = 1;         // signal completion
    }
}

void initADC(void) {
    PM5CTL0 &= ~LOCKLPM5;            // Unlock GPIO on FRAM MSP430FR2355

    // Configure analog function on P1.3, P1.4, P1.5
    P1SEL0 |= BIT3 | BIT4 | BIT5;
    P1SEL1 |= BIT3 | BIT4 | BIT5;

    // ADC core settings
    ADCCTL0 = ADCSHT_2 | ADCON;      // sample-and-hold time, turn ADC on
    ADCCTL1 = ADCSHP;                // use the internal sampling timer
    ADCCTL2 = ADCRES_2;              // 12-bit resolution
    ADCIE  |= ADCIE0;                // enable ADC interrupt

    // Pick a default channel so ADC is enabled
    ADCMCTL0 = THERMOCOUPLE_CHANNEL;
    ADCCTL0 |= ADCENC;               // enable conversions
}

static uint16_t readADC_raw(uint16_t channel) {
    ADCCTL0 &= ~ADCENC;               // disable conversions to switch channel
    ADCMCTL0  = channel;             // choose new input
    ADCFinished = 0;                 // clear the done flag
    ADCCTL0  |= ADCENC | ADCSC;      // enable & start conversion

    uint32_t timeout = ADC_TIMEOUT;
    while (!ADCFinished && --timeout);  // spin until done or timeout

    return timeout ? ADCResult : 0xFFFF;
}

uint16_t readADC(uint16_t channel) {
    return readADC_raw(channel);
}

uint16_t readThermistor(void) {
    return readADC_raw(THERMISTOR_CHANNEL);
}
// …and similarly for thermocouple and pot

uint16_t flame = readThermocouple();
uint16_t temp  = readThermistor();
uint16_t setpt = readPot();
