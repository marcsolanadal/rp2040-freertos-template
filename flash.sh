#! /bin/bash

openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "program build/src/firmware.elf verify reset exit"
