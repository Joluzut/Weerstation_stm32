.. _this_is_a_reference:

##################################
MicroChip 24LC64 I2C EEPROM Sample
##################################
Date: 2023OCT04
Author: JSC

Description
**************
The example contains:
- main - example to read/write to I2C EEPROM
- driver - driver tailored to microchip. 
 
Though integrated in this example, it can be extracted and created as an independent driver.

Requirements
***************
Microchip's 24LC64 chip connected to I2C bus and powered on.

Wiring
******
The code is tested with a logic analyser, but with no eeprom connected. It operaties on the STM nucleo_f030r8 board.
The sensor operates at 3.3V and uses I2C to communicate with the board.

External Wires:
* Breakout **GND** pin <--> Nucleo **GND** pin
* Breakout **VCC** pin <--> Nucleo **3V3** pin
* Breakout **SDA** pin <--> Nucleo **CN5-D14** pin
* Breakout **SCL** pin <--> Nucleo **CN5-D15** pin

Building and Running
********************
In order to build the sample, connect the board to the computer with a USB cable and enter the following commands:

.. zephyr-app-commands::
   :zephyr-app: samples/storage/eeprom
   :board: nucleo_f030r8
   :goals: build flash
   :compact:

Sample Output
*************
The output can be seen via a terminal emulator (e.g. minicom). Connect the board with a USB cable
to the computer and open /dev/ttyACM0 with the below serial settings:

* Baudrate: 115200
* Parity: None
* Data: 8
* Stop bits: 1

Files
*****
Driver.
The driver supports the generic eeprom (@see: zephyr/drivers/eeprom.h) interface. It uses I2C as bus and must be specified as child node in the devicetree.
- src/eeprom_24lc64.c - implementation code and registration
- src/eeprom_24lc64.h - header, currently empty
- dts/bindings/microchip,24lc64.yaml - devicetree requirements setting. 

Current compatible is microchip,24lc64. The code is currently specific for this type specific. Code is prepared to extend to other microchip i2c eeprom chips. And may extend to other manufacturers as wel.

Test.
- main.c - reading/writing to eeprom over the i2c interface
- boards/nucleo_f030r8.overlay - overlay specifies the microchip i2c eeprom and connection

Boards
******
Developed and partly tested on STM32 nucleo f030r8

Status
******
Tested with: logic analyser
Tested with real 24LC64, with A2, A1 and A0 connected to GND.
main.c contains write and readback of a counting variable.
