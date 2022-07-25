# RP2040 template using freeRTOS

I've added the submodules of the hardare and sensors I will likely use in the future:
- rp2040 sdk
- freeRTOS

To download the git submodules use:

```bash
$ git submodule update --recursive
```

Those commands can be used from the root of the project. No need move to the `build` folder.

```bash
$ cmake -S . -B build
$ cmake --build build
$ ./flash.sh
```

## We may need to initialize the submodules of the SDK

CMake Warning at extern/pico-sdk/src/rp2_common/tinyusb/CMakeLists.txt:10 (message):
  TinyUSB submodule has not been initialized; USB support will be unavailable

  hint: try 'git submodule update --init' from your SDK directory
  (/home/corretjola/pico/c/rp2040-template/extern/pico-sdk).

## IdleMemory.c

Not including the file results in the following error:

```
/usr/lib/gcc/arm-none-eabi/8.3.1/../../../arm-none-eabi/bin/ld: ../external/freertos/libfreertos.a(tasks.c.obj): in function `vTaskStartScheduler':
tasks.c:(.text+0x970): undefined reference to `vApplicationGetIdleTaskMemory'
/usr/lib/gcc/arm-none-eabi/8.3.1/../../../arm-none-eabi/bin/ld: ../external/freertos/libfreertos.a(timers.c.obj): in function `xTimerCreateTimerTask':
timers.c:(.text+0x31e): undefined reference to `vApplicationGetTimerTaskMemory'
collect2: error: ld returned 1 exit status
gmake[2]: *** [src/CMakeFiles/firmware.dir/build.make:692: src/firmware.elf] Error 1
gmake[1]: *** [CMakeFiles/Makefile2:1873: src/CMakeFiles/firmware.dir/all] Error 2
gmake: *** [Makefile:103: all] Error 2
```