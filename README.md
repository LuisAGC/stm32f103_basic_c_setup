# stm32f103_basic_c_setup
A simple setup to compile code for the STM32F103C8 mcu from STMicroelectronics using vs code to edit text

After cloning the code be sure to first download the git submodules using: 
```
git submodule update --init
```
Then use the following commands to build libopencm3:
```
pushd libopencm3
unset CFLAGS && unset CXXFLAGS # This one might not be needed
make
popd
```

Then to build just run make
```
make
```

To clean the directory of the compilation and linking resulting files just do
```
make clean
```

To flash your device (This will only work if you have installed the st-flash utilities on your os)
```
make flash
```
