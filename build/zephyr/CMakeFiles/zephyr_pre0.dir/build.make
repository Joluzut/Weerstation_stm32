# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build

# Include any dependencies generated for this target.
include zephyr/CMakeFiles/zephyr_pre0.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include zephyr/CMakeFiles/zephyr_pre0.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/CMakeFiles/zephyr_pre0.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/CMakeFiles/zephyr_pre0.dir/flags.make

zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj: zephyr/CMakeFiles/zephyr_pre0.dir/flags.make
zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj: C:/Users/luukv/zephyrproject/zephyr/misc/empty_file.c
zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj: zephyr/CMakeFiles/zephyr_pre0.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj -MF CMakeFiles\zephyr_pre0.dir\misc\empty_file.c.obj.d -o CMakeFiles\zephyr_pre0.dir\misc\empty_file.c.obj -c C:\Users\luukv\zephyrproject\zephyr\misc\empty_file.c

zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.i"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\luukv\zephyrproject\zephyr\misc\empty_file.c > CMakeFiles\zephyr_pre0.dir\misc\empty_file.c.i

zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.s"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\luukv\zephyrproject\zephyr\misc\empty_file.c -o CMakeFiles\zephyr_pre0.dir\misc\empty_file.c.s

# Object files for target zephyr_pre0
zephyr_pre0_OBJECTS = \
"CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj"

# External object files for target zephyr_pre0
zephyr_pre0_EXTERNAL_OBJECTS =

zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/zephyr_pre0.dir/misc/empty_file.c.obj
zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/zephyr_pre0.dir/build.make
zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/offsets.dir/arch/arm/core/offsets/offsets.c.obj
zephyr/zephyr_pre0.elf: zephyr/linker_zephyr_pre0.cmd
zephyr/zephyr_pre0.elf: app/libapp.a
zephyr/zephyr_pre0.elf: zephyr/libzephyr.a
zephyr/zephyr_pre0.elf: zephyr/arch/common/libarch__common.a
zephyr/zephyr_pre0.elf: zephyr/arch/arch/arm/core/aarch32/libarch__arm__core__aarch32.a
zephyr/zephyr_pre0.elf: zephyr/arch/arch/arm/core/aarch32/cortex_m/libarch__arm__core__aarch32__cortex_m.a
zephyr/zephyr_pre0.elf: zephyr/lib/libc/minimal/liblib__libc__minimal.a
zephyr/zephyr_pre0.elf: zephyr/lib/libc/common/liblib__libc__common.a
zephyr/zephyr_pre0.elf: zephyr/drivers/interrupt_controller/libdrivers__interrupt_controller.a
zephyr/zephyr_pre0.elf: zephyr/drivers/adc/libdrivers__adc.a
zephyr/zephyr_pre0.elf: zephyr/drivers/clock_control/libdrivers__clock_control.a
zephyr/zephyr_pre0.elf: zephyr/drivers/console/libdrivers__console.a
zephyr/zephyr_pre0.elf: zephyr/drivers/gpio/libdrivers__gpio.a
zephyr/zephyr_pre0.elf: zephyr/drivers/i2c/libdrivers__i2c.a
zephyr/zephyr_pre0.elf: zephyr/drivers/pinctrl/libdrivers__pinctrl.a
zephyr/zephyr_pre0.elf: zephyr/drivers/reset/libdrivers__reset.a
zephyr/zephyr_pre0.elf: zephyr/drivers/sensor/bme280/libdrivers__sensor__bme280.a
zephyr/zephyr_pre0.elf: zephyr/drivers/sensor/stm32_temp/libdrivers__sensor__stm32_temp.a
zephyr/zephyr_pre0.elf: zephyr/drivers/sensor/stm32_vref/libdrivers__sensor__stm32_vref.a
zephyr/zephyr_pre0.elf: zephyr/drivers/serial/libdrivers__serial.a
zephyr/zephyr_pre0.elf: zephyr/drivers/timer/libdrivers__timer.a
zephyr/zephyr_pre0.elf: zephyr/drivers/rtc/libdrivers__rtc.a
zephyr/zephyr_pre0.elf: modules/stm32/stm32cube/lib..__modules__hal__stm32__stm32cube.a
zephyr/zephyr_pre0.elf: zephyr/kernel/libkernel.a
zephyr/zephyr_pre0.elf: zephyr/arch/common/libisr_tables.a
zephyr/zephyr_pre0.elf: zephyr/linker_zephyr_pre0.cmd
zephyr/zephyr_pre0.elf: zephyr/CMakeFiles/zephyr_pre0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zephyr_pre0.elf"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\zephyr_pre0.dir\link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold "Logical command for additional byproducts on target: zephyr_pre0"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && "C:\Program Files\CMake\bin\cmake.exe" -E true

# Rule to build all files generated by this target.
zephyr/CMakeFiles/zephyr_pre0.dir/build: zephyr/zephyr_pre0.elf
.PHONY : zephyr/CMakeFiles/zephyr_pre0.dir/build

zephyr/CMakeFiles/zephyr_pre0.dir/clean:
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && $(CMAKE_COMMAND) -P CMakeFiles\zephyr_pre0.dir\cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/zephyr_pre0.dir/clean

zephyr/CMakeFiles/zephyr_pre0.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom C:\Users\luukv\zephyrproject\zephyr C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\CMakeFiles\zephyr_pre0.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : zephyr/CMakeFiles/zephyr_pre0.dir/depend

