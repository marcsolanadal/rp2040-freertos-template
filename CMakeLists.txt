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

