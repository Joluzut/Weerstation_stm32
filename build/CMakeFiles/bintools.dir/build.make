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

# Utility rule file for bintools.

# Include any custom commands dependencies for this target.
include CMakeFiles/bintools.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bintools.dir/progress.make

bintools: CMakeFiles/bintools.dir/build.make
.PHONY : bintools

# Rule to build all files generated by this target.
CMakeFiles/bintools.dir/build: bintools
.PHONY : CMakeFiles/bintools.dir/build

CMakeFiles/bintools.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bintools.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bintools.dir/clean

CMakeFiles/bintools.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build C:\Users\luukv\zephyrproject\zephyr\samples\sensor\eeprom\build\CMakeFiles\bintools.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/bintools.dir/depend

