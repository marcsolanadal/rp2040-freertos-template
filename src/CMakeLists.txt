add_executable(${PROJECT_NAME}
    main.c
    includes/Servo/Servo.c
    includes/Flash/Flash.c
    tasks/turn/turn.c
    tasks/sense/sense.c
    tasks/env_control/env_control.c
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    freertos
    hardware_pwm
    hardware_i2c
    hardware_flash
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Enable UART to allow SWD and disable USB
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)