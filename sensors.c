// SENSORS.c

#include "SYSTEM.h"
#include "SENSORS.h"

static volatile uint8_t  ADCFinished = 0;
static volatile uint16_t ADCResult   = 0;

// Internal helper: clear old channel, start conversion, wait with timeout
static uint16_t readADC_ch(uint8_t ch){
  ADCMCTL0 &= ~(ADCINCH_0 | ADCINCH_1 | … | ADCINCH_15);
  ADCMCTL0 |= ADCINCH_0 + ch;
  ADCFinished = 0;
  ADCCTL0 |= ADCENC | ADCSC;
  for(uint32_t t=100000; t && !ADCFinished; --t);
  return ADCResult;
}

void initADC(void){
  PM5CTL0 &= ~LOCKLPM5;            // unlock GPIO
  P1SEL0 |= BIT3|BIT4|BIT5;        // A3–A5
  P1SEL1 |= BIT3|BIT4|BIT5;
  // configure VREF, ADCCTL0/1/2 as before…
}

unsigned int readThermistor(void){
  uint16_t raw = readADC_avg(4);
  // apply Steinhart–Hart here…
  return raw;
}

unsigned int readThermocouple(void){
  uint16_t raw = readADC_avg(3);
  // apply cold‑junction compensation & CJC…
  return raw;
}

unsigned int readPot(void){
  return readADC_avg(5);  
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
  if(ADCIV == ADCIV_ADCIFG){
    ADCResult   = ADCMEM0;
    ADCFinished = 1;
  }
}
