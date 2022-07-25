add_executable(blinky
    src/blinky.c
)

target_link_libraries(blinky
    pico_stdlib 
    FreeRTOS
    bme280
)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(blinky)