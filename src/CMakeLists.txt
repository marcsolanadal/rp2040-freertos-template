add_executable(${PROJECT_NAME}
    blinky.c
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    freertos
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})