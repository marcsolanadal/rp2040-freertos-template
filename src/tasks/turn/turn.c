#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include "timers.h"
#include "turn.h"

const uint PWM_SIGNAL_PIN = 16;
const uint TOP = 20000;
const float DIV_INT = 125.f;
const uint SERVO_MIN_RANGE_SLICE = 1000;
const uint SERVO_MAX_RANGE_SLICE = 2000;
const uint TIMER_PERIOD_MS = 10; // 14400

TimerHandle_t period_timer = NULL;
uint position = 1500;
int direction = 1;

void periodTimerCallback(TimerHandle_t xTimer) {
    position += direction;
    pwm_set_gpio_level(PWM_SIGNAL_PIN, position);

    if (position <= SERVO_MIN_RANGE_SLICE ||
        position >= SERVO_MAX_RANGE_SLICE) {
        direction *= -1;
    }
}

void turn_task(void *pvParameters) {
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_wrap(&cfg, TOP - 1);
    pwm_config_set_clkdiv(&cfg, DIV_INT);
    pwm_init(pwm_gpio_to_slice_num(PWM_SIGNAL_PIN), &cfg, true);

    gpio_set_function(PWM_SIGNAL_PIN, GPIO_FUNC_PWM);

    period_timer =
        xTimerCreate("period timer", TIMER_PERIOD_MS / portTICK_PERIOD_MS,
                     pdTRUE, (void *)0, periodTimerCallback);

    if (period_timer == NULL) {
        printf("Could not create duty timer");
    } else {
        xTimerStart(period_timer, portMAX_DELAY);
    }

    while (true) { // super-loop
    }
}