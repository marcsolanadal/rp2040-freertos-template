#ifndef TURN_H
#define TURN_H

/*
 * Task in charge of turning the eggs with a servomotor.
 *
 * The task initializes and runs `period_timer`. The timer is in charge of
 * changing the duty-cycle of the PWM and setting the direction.
 *
 * The TOP register in the PWM has 20000 steps and the clock divider is set to
 * 125 so we can get a period of 20ms (50Hz). This is a convenient
 * representation because we can set the duty cycle in terms of µs.
 *
 * I based my calculations on the RP2040 datasheet (page 529). I ignored the
 * DIV_FRAC value and only used DIV_INT.
 *
 * The used servo can travel from:
 *   - 0 degree: 500µs
 *   - 180 degree: 2500µs
 *
 * Note that those are not standard duty cycle values. I don't know if this is
 * just a manufacturer spec or a mistake in my calculations.
 *
 * We want to turn the eggs 45 degree on both directions. The duty cycle will go
 * from 1000µs to 2000µs and by default it will center at 1500µs.
 *
 * We want the eggs to be in the opposite angle every 4h.
 *   delay = (4h * 60min * 60s * 1000ms) / 20000steps = 14700ms
 *
 * In case of power outage we need to maintain the last duty cycle value and
 * start from the stored value. This is done to avoid any disturbance to the
 * eggs and to avoid mechanical stress to the egg holding structure.
 */
void turn_task(void *pvParameters);

#endif