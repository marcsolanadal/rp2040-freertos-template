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
