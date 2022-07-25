cmake_minimum_required(VERSION 3.12...3.24)

# Needs to be included before the project definition
include(external/pico-sdk/pico_sdk_init.cmake)

project(firmware
	VERSION 0.1.0
	DESCRIPTION "Project description"
	LANGUAGES C CXX ASM
)

# Set versions of C/C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(external/freertos)
add_subdirectory(src)

# Enable UART to allow SWD and disable USB
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)

