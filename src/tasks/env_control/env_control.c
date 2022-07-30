#include <FreeRTOS.h>
#include <queue.h>
#include <stdio.h>
#include <task.h>

#include "env_control.h"
#include "pico/stdlib.h"

const uint LED_PIN = 25;

void env_control_task(void *message_queue) {
    // uint uIReceivedValue;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(1000);
        gpio_put(LED_PIN, 0);
        vTaskDelay(1000);

        // xQueueReceive(message_queue, &uIReceivedValue, portMAX_DELAY);
    }
}