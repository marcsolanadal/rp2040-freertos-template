#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define I2C_PORT i2c0

static int addr = 0x76;

void bme280_init(void) {
    sleep_ms(2000); // boot up delay for sensor
    uint8_t reg = 0xD0;
    uint8_t chipID[1];
    i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, addr, chipID, 1, false);

    if (chipID[0] != 0x60) {
        printf("Chip ID not correct\n");
    } else {
        printf("BME280 connected as a slave!\n");
    }
}

void i2c_configure(void) {
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(17, GPIO_FUNC_I2C);
    gpio_pull_up(17);
    gpio_set_function(16, GPIO_FUNC_I2C);
    gpio_pull_up(16);
}

int main() {
    stdio_init_all();
    i2c_configure();
    bme280_init();
}
