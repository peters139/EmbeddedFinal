#define RGB_PORT        P6
#define RGB_RED_PIN     BIT0    /**< TB2CCR1 on P6.0 */
#define RGB_GREEN_PIN   BIT1    /**< TB2CCR2 on P6.1 */
#define RGB_BLUE_PIN    BIT2    /**< TB2CCR3 on P6.2 */

#define RGB_PWM_PERIOD  255U

void rgb_init(void) {
    // 1. GPIO setup: enable TB2 PWM function on P6.0–P6.2
    RGB_PORT->DIR  |= RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN;
    RGB_PORT->SEL0 |= RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN;
    RGB_PORT->SEL1 &= ~(RGB_RED_PIN | RGB_GREEN_PIN | RGB_BLUE_PIN);

    // 2. Timer setup: use SMCLK, up‑mode, clear timer
    TB2CCR0 = RGB_PWM_PERIOD;
    TB2CTL  = TBSSEL__SMCLK | MC__UP | TBCLR;

    // 3. PWM mode: configure CCR1–CCR3 for Reset/Set (OUTMOD_7)
    TB2CCTL1 = OUTMOD_7; // red
    TB2CCTL2 = OUTMOD_7; // green
    TB2CCTL3 = OUTMOD_7; // blue

    // 4. Ensure LEDs start off
    rgb_off();
}

void rgb_set(uint8_t red, uint8_t green, uint8_t blue) {
    TB2CCR1 = red;    // Duty cycle for red channel
    TB2CCR2 = green;  // Duty cycle for green channel
    TB2CCR3 = blue;   // Duty cycle for blue channel
}

static inline void rgb_off(void) {
    rgb_set(0, 0, 0);
}

