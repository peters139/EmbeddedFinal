#ifndef MAIN_H
#define MAIN_H


#include <msp430fr2355.h>

#include <msp430.h>

#include "SYSTEM.h"

#include <intrinsics.h>


extern volatile uint8_t FLAME_EXTINGUISHED;


int main(void);
void rgbinit(void);
void mainValve_Init(void);
void setIgnitor(void);
void turnOnPilotValve(void);
void turnOffIgnitor(void);
void turnOffPilotValve(void);
void turnOffMainValve(void);
void Wait2Seconds(void);
uint8_t CallForHeat(void);
uint8_t checkFlame(void);
int     readBoilerTemp(void);

#endif /* MAIN_H */
