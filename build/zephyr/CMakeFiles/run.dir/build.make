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

# Utility rule file for run.

# Include any custom commands dependencies for this target.
include zephyr/CMakeFiles/run.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/CMakeFiles/run.dir/progress.make

zephyr/CMakeFiles/run:
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && "C:\Program Files\CMake\bin\cmake.exe" -E echo =================================================== "Emulation/Simulation not supported with this board." ===================================================

run: zephyr/CMakeFiles/run
run: zephyr/CMakeFiles/run.dir/build.make
.PHONY : run

# Rule to build all files generated by this target.
zephyr/CMakeFiles/run.dir/build: run
.PHONY : zephyr/CMakeFiles/run.dir/build

zephyr/CMakeFiles/run.dir/clean:
	cd /d C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr && $(CMAKE_COMMAND) -P CMakeFiles\run.dir\cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/run.dir/clean

zephyr/CMakeFiles/run.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom C:\Users\luukv\zephyrproject\zephyr C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\zephyr\CMakeFiles\run.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : zephyr/CMakeFiles/run.dir/depend

