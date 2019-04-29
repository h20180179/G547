Gas Sensor ADC USB Device Analog gas sensor implemented as a USB device and values read from ADC module

Function

Gas sensors are used in the industry to detect hazardous leakage of harmful chemical gases or can be used as a fire alarm/detector.


Building Functions are listed below:

To Build all modules at once:  make all

To Build user space code: make user


To Build Kernel module:  make kernel

Clean all object files: make clean


For loading the modules the console commands are listed below:


To load gas_adc in kernel:insmod gas_adc.ko

To unload gas_adc in kernel:rmmod gas_adc



Firmware building and flashing into the microcontroller:

Command to build firmware and generate hex file: make all

Command to flash fuses and hex file: make program

Command to flash the fuse bits: make fuses

Command to flash the hex file: make flash


User application:

Command to build: make all


To start the getting data from gas sensor over usb onto Input Subsystem : sudo ./GasAdc 

Issues faced: Harware was extremely fragile. The hardware worked for some of the time and the other times it didn't. The firmware was also properly flashed.
