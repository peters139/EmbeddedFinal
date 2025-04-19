#ifndef IGNITOR_LED_H
#define IGNITOR_LED_H

#include <stdint.h>

// Initialize P2.0 as output and turn the LED off
void ignitor_led_init(void);

// Control routines
void ignitor_led_on(void);
void ignitor_led_off(void);
void ignitor_led_toggle(void);

#endif // IGNITOR_LED_H
