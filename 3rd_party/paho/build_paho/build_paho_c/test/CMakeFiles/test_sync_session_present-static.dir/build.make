# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c

# Include any dependencies generated for this target.
include test/CMakeFiles/test_sync_session_present-static.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_sync_session_present-static.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_sync_session_present-static.dir/flags.make

test/CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.o: test/CMakeFiles/test_sync_session_present-static.dir/flags.make
test/CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.o: /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master/test/test_sync_session_present.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object test/CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.o"
	cd /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.o   -c /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master/test/test_sync_session_present.c

test/CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.i"
	cd /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master/test/test_sync_session_present.c > CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.i

test/CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.s"
	cd /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master/test/test_sync_session_present.c -o CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.s

# Object files for target test_sync_session_present-static
test_sync_session_present__static_OBJECTS = \
"CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.o"

# External object files for target test_sync_session_present-static
test_sync_session_present__static_EXTERNAL_OBJECTS =

test/test_sync_session_present-static: test/CMakeFiles/test_sync_session_present-static.dir/test_sync_session_present.c.o
test/test_sync_session_present-static: test/CMakeFiles/test_sync_session_present-static.dir/build.make
test/test_sync_session_present-static: src/libpaho-mqtt3c.a
test/test_sync_session_present-static: test/CMakeFiles/test_sync_session_present-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_sync_session_present-static"
	cd /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_sync_session_present-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_sync_session_present-static.dir/build: test/test_sync_session_present-static

.PHONY : test/CMakeFiles/test_sync_session_present-static.dir/build

test/CMakeFiles/test_sync_session_present-static.dir/clean:
	cd /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test && $(CMAKE_COMMAND) -P CMakeFiles/test_sync_session_present-static.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_sync_session_present-static.dir/clean

test/CMakeFiles/test_sync_session_present-static.dir/depend:
	cd /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/paho.mqtt.c-master/test /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test /home/egoreli/Prog/dust-uv_2021_09_29/external_libs/paho/build_paho/build_paho_c/test/CMakeFiles/test_sync_session_present-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_sync_session_present-static.dir/depend
