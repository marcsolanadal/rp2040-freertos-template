#ifndef SERVO_H
#define SERVO_H

#include "hardware/pwm.h"

typedef struct DutyRange
{
    uint min;
    uint max;
} DutyRange;

typedef struct Servo
{
    uint signal_pin;
    uint duty_cycle;
    int direction;
    DutyRange* range;
} Servo;

pwm_config
Servo_init(Servo* self);

void
Servo_tick(Servo* self);

#endif