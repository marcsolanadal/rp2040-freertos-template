#include <FreeRTOS.h>
#include <hardware/flash.h>
#include <stdio.h>
#include <task.h>

// TODO: Include all libraries inside the includes folder
#include "../../includes/Flash/Flash.h"
#include "../../includes/Servo/Servo.h"
#include "pico/stdlib.h"
#include "timers.h"
#include "turn.h"

const uint PWM_SIGNAL_PIN = 16;
const uint TIMER_PERIOD_MS = 5; // 14400

TimerHandle_t save_timer = NULL;
TimerHandle_t period_timer = NULL;
DutyRange dr1 = { 1000, 2000 };
Servo s1 = { 16, 1500, 1, &dr1 };
int buf[FLASH_PAGE_SIZE / sizeof(int)]; // One page worth of 32-bit ints
int offset;

void
saveTimerCallback(TimerHandle_t xTimer)
{
    int result = Flash_read(offset);

    printf("buf[0]: %d, buf[1]: %d\n", buf[0], buf[1]);
}

void
periodTimerCallback(TimerHandle_t xTimer)
{
    Servo_tick(&s1);
}

void
turn_task(void* pvParameters)
{
    Servo_init(&s1);

    int buf[FLASH_PAGE_SIZE / sizeof(int)]; // One page worth of 32-bit ints
    buf[0] = 123456; // Put the data into the first four bytes of buf[]
    buf[1] = 5644;

    Flash_stats();
    offset = Flash_write(&buf);
    // int result = Flash_read(offset);

    // printf("buf[0]: %d, buf[1]: %d", buf[0], buf[1]);

    save_timer = xTimerCreate("save timer",
                              2000 / portTICK_PERIOD_MS,
                              pdTRUE,
                              (void*)0,
                              periodTimerCallback);

    if (save_timer == NULL) {
        printf("Could not create save timer");
    } else {
        xTimerStart(save_timer, portMAX_DELAY);
    }

    period_timer = xTimerCreate("period timer",
                                TIMER_PERIOD_MS / portTICK_PERIOD_MS,
                                pdTRUE,
                                (void*)1,
                                periodTimerCallback);

    if (period_timer == NULL) {
        printf("Could not create duty timer");
    } else {
        xTimerStart(period_timer, portMAX_DELAY);
    }

    while (true) { // super-loop
    }
}