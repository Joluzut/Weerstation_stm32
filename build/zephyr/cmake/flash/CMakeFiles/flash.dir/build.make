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

# Utility rule file for flash.

# Include any custom commands dependencies for this target.
include zephyr/cmake/flash/CMakeFiles/flash.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/cmake/flash/CMakeFiles/flash.dir/progress.make

zephyr/cmake/flash/CMakeFiles/flash:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Flashing nucleo_f030r8"
	"C:\Program Files\CMake\bin\cmake.exe" -DTARGET=flash -DDEPENDENCIES="" -P C:/Users/luukv/zephyrproject/zephyr/cmake/flash/check_runner_dependencies.cmake
	"C:\Program Files\CMake\bin\cmake.exe" -E env C:/Python311/python.exe -m west flash

flash: zephyr/cmake/flash/CMakeFiles/flash
flash: zephyr/cmake/flash/CMakeFiles/flash.dir/build.make
.PHONY : flash

# Rule to build all files generated by this target.
zephyr/cmake/flash/CMakeFiles/flash.dir/build: flash
.PHONY : zephyr/cmake/flash/CMakeFiles/flash.dir/build

zephyr/cmake/flash/CMakeFiles/flash.dir/clean:
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\cmake\flash && $(CMAKE_COMMAND) -P CMakeFiles\flash.dir\cmake_clean.cmake
.PHONY : zephyr/cmake/flash/CMakeFiles/flash.dir/clean

zephyr/cmake/flash/CMakeFiles/flash.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom C:\Users\luukv\zephyrproject\zephyr\cmake\flash C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\cmake\flash C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\cmake\flash\CMakeFiles\flash.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : zephyr/cmake/flash/CMakeFiles/flash.dir/depend

