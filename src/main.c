#include <FreeRTOS.h>
#include <stdio.h>
#include <task.h>

#include "pico/stdlib.h"
#include "tasks/env_control/env_control.h"
#include "tasks/sense/sense.h"
#include "tasks/turn/turn.h"

int main() {
    stdio_init_all();

    xTaskCreate(turn_task, "Turn_Task", 256, NULL, 1, NULL);
    xTaskCreate(sense_task, "Sense_Task", 256, NULL, 1, NULL);
    xTaskCreate(env_control_task, "Env_Control_Task", 256, NULL, 1, NULL);

    vTaskStartScheduler();
}
