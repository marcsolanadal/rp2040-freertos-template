#include "Servo.h"
#include "pico/stdlib.h"

const uint TOP = 20000;
const float DIV_INT = 125.f;

pwm_config
Servo_init(Servo* self)
{
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_wrap(&cfg, TOP - 1);
    pwm_config_set_clkdiv(&cfg, DIV_INT);
    pwm_init(pwm_gpio_to_slice_num(self->signal_pin), &cfg, true);

    gpio_set_function(self->signal_pin, GPIO_FUNC_PWM);

    return cfg;
}

void
Servo_tick(Servo* self)
{
    self->duty_cycle += self->direction;

    pwm_set_gpio_level(self->signal_pin, self->duty_cycle);

    if (self->duty_cycle <= self->range->min ||
        self->duty_cycle >= self->range->max) {
        self->direction *= -1;
    }
}