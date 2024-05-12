# BME280 for uni

Code was written on linux, so you need to change a couple of things if you wanna use it on windows

## TODO
fix timers

To setup 

```shell
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/arm-gcc-toolchain.cmake
```

To build 
```shell
ninja -C build
```

To program
```shell
ninja -C build program
```
