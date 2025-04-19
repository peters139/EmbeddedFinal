main_valve.h
ifndef MAIN_VALVE_H
define MAIN_VALVE_H

include <stdint.h>
/** P5.0 drives PWM output for servo */
define MAIN_VALVE_PIN    BIT0
void mainValve_init(void);

void mainValve_set(uint8_t position);

endif // MAIN_VALVE_H
