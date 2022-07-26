#include <FreeRTOS.h>
#include <task.h>

#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "turn.h"

/*
 * Based on the rp2040 datasheet (page 524).
 *
 * In a servo 1ms is -90 degrees and 2ms is 90 degrees.
 *      180 slices = 1ms
 *      360 slices = 2ms
 */
void turn_task(void *pvParameters) {
    const uint PWM_SIGNAL_PIN = 15;

    uint brightness_level = 0;
    int direction = 1;

    uint slices = 100;

    // Tell GPIO15 that they're allocated to the PWM
    gpio_set_function(PWM_SIGNAL_PIN, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to PIN 15
    uint slice_num = pwm_gpio_to_slice_num(PWM_SIGNAL_PIN);

    // Set period do 3599 slices. We want to use slice 180 to 360.
    pwm_set_wrap(slice_num, slices - 1);

    pwm_set_chan_level(slice_num, PWM_CHAN_B, brightness_level);

    // Starts PWM
    pwm_set_enabled(slice_num, true);

    while (true) { // super-loop
        pwm_set_chan_level(slice_num, PWM_CHAN_B, brightness_level);
        brightness_level += direction;

        vTaskDelay(10);

        if (brightness_level <= 0 || brightness_level >= slices) {
            direction *= -1;
        }
    }
}