// rgb_led.h
#ifndef RGB_LED_H
#define RGB_LED_H

#include <stdint.h>
#include <msp430fr2355.h>

/** Pin mappings for RGB LED on MSP430FR2355 using P6.0-P6.2 */
#define RGB_RED_PIN    BIT0    /**< P6.0 -> TB2CCR1 */
#define RGB_GREEN_PIN  BIT1    /**< P6.1 -> TB2CCR2 */
#define RGB_BLUE_PIN   BIT2    /**< P6.2 -> TB2CCR3 */

/** PWM period for 8-bit brightness control */
#define RGB_PWM_PERIOD 255U    /**< CCR0 -> 256 steps */

/**
 * @brief Initialize Timer_B2 and GPIO for RGB LED PWM.
 *        Sets up a 256-step PWM on TB2CCR1-3 at SMCLK in up mode.
 */
void rgb_init(void);

/**
 * @brief Set the brightness of each RGB channel.
 *
 * @param red   Brightness 0–255 for red channel
 * @param green Brightness 0–255 for green channel
 * @param blue  Brightness 0–255 for blue channel
 */
void rgb_set(uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief Turn off all RGB LED channels.
 */
void rgb_off(void);

#endif // RGB_LED_H


// rgb_led.c
#include "rgb_led.h"
