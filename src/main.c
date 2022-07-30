#include <FreeRTOS.h>
#include <queue.h>
#include <stdio.h>
#include <task.h>

#include "pico/stdlib.h"
#include "tasks/env_control/env_control.h"
#include "tasks/sense/sense.h"
#include "tasks/turn/turn.h"

// const uint LED_PIN = 25;

int main(void) {
    stdio_init_all();

    // Board turned on indicator
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    // gpio_put(LED_PIN, 1);

    xTaskCreate(turn_task, "Turn_Task", 256, NULL, 1, NULL);
    // xTaskCreate(sense_task, "Sense_Task", 256, NULL, 1, NULL);
    xTaskCreate(env_control_task, "Env_Control_Task", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}
