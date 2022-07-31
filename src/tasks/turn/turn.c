#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

// TODO: Include all libraries inside the includes folder
#include "../../includes/Servo/Servo.h"
#include "pico/stdlib.h"
#include "timers.h"
#include "turn.h"

const uint PWM_SIGNAL_PIN = 16;
const uint TIMER_PERIOD_MS = 5; // 14400

TimerHandle_t period_timer = NULL;
DutyRange dr1 = { 1000, 2000 };
Servo s1 = { 16, 1500, 1, &dr1 };

void
periodTimerCallback(TimerHandle_t xTimer)
{
    Servo_tick(&s1);
}

void
turn_task(void* pvParameters)
{
    Servo_init(&s1);

    period_timer = xTimerCreate("period timer",
                                TIMER_PERIOD_MS / portTICK_PERIOD_MS,
                                pdTRUE,
                                (void*)0,
                                periodTimerCallback);

    if (period_timer == NULL) {
        printf("Could not create duty timer");
    } else {
        xTimerStart(period_timer, portMAX_DELAY);
    }

    while (true) { // super-loop
    }
}