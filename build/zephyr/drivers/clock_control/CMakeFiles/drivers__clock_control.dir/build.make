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
include zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/flags.make

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/flags.make
zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj: C:/Users/luukv/zephyrproject/zephyr/drivers/clock_control/clock_stm32_ll_common.c
zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj -MF CMakeFiles\drivers__clock_control.dir\clock_stm32_ll_common.c.obj.d -o CMakeFiles\drivers__clock_control.dir\clock_stm32_ll_common.c.obj -c C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control\clock_stm32_ll_common.c

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.i"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control\clock_stm32_ll_common.c > CMakeFiles\drivers__clock_control.dir\clock_stm32_ll_common.c.i

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.s"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control\clock_stm32_ll_common.c -o CMakeFiles\drivers__clock_control.dir\clock_stm32_ll_common.c.s

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/flags.make
zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj: C:/Users/luukv/zephyrproject/zephyr/drivers/clock_control/clock_stm32f0_f3.c
zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj -MF CMakeFiles\drivers__clock_control.dir\clock_stm32f0_f3.c.obj.d -o CMakeFiles\drivers__clock_control.dir\clock_stm32f0_f3.c.obj -c C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control\clock_stm32f0_f3.c

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.i"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control\clock_stm32f0_f3.c > CMakeFiles\drivers__clock_control.dir\clock_stm32f0_f3.c.i

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.s"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && C:\Users\luukv\zephyr-sdk-0.16.1\arm-zephyr-eabi\bin\arm-zephyr-eabi-gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control\clock_stm32f0_f3.c -o CMakeFiles\drivers__clock_control.dir\clock_stm32f0_f3.c.s

# Object files for target drivers__clock_control
drivers__clock_control_OBJECTS = \
"CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj" \
"CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj"

# External object files for target drivers__clock_control
drivers__clock_control_EXTERNAL_OBJECTS =

zephyr/drivers/clock_control/libdrivers__clock_control.a: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32_ll_common.c.obj
zephyr/drivers/clock_control/libdrivers__clock_control.a: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clock_stm32f0_f3.c.obj
zephyr/drivers/clock_control/libdrivers__clock_control.a: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/build.make
zephyr/drivers/clock_control/libdrivers__clock_control.a: zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libdrivers__clock_control.a"
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && $(CMAKE_COMMAND) -P CMakeFiles\drivers__clock_control.dir\cmake_clean_target.cmake
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\drivers__clock_control.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/build: zephyr/drivers/clock_control/libdrivers__clock_control.a
.PHONY : zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/build

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clean:
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control && $(CMAKE_COMMAND) -P CMakeFiles\drivers__clock_control.dir\cmake_clean.cmake
.PHONY : zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/clean

zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom C:\Users\luukv\zephyrproject\zephyr\drivers\clock_control C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\drivers\clock_control\CMakeFiles\drivers__clock_control.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : zephyr/drivers/clock_control/CMakeFiles/drivers__clock_control.dir/depend

