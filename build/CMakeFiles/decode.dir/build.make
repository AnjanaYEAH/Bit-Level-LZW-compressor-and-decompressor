# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build

# Include any dependencies generated for this target.
include CMakeFiles/decode.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/decode.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/decode.dir/flags.make

CMakeFiles/decode.dir/src/decode.c.o: CMakeFiles/decode.dir/flags.make
CMakeFiles/decode.dir/src/decode.c.o: ../src/decode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/decode.dir/src/decode.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/decode.dir/src/decode.c.o   -c /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/src/decode.c

CMakeFiles/decode.dir/src/decode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/decode.dir/src/decode.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/src/decode.c > CMakeFiles/decode.dir/src/decode.c.i

CMakeFiles/decode.dir/src/decode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/decode.dir/src/decode.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/src/decode.c -o CMakeFiles/decode.dir/src/decode.c.s

CMakeFiles/decode.dir/src/decode.c.o.requires:

.PHONY : CMakeFiles/decode.dir/src/decode.c.o.requires

CMakeFiles/decode.dir/src/decode.c.o.provides: CMakeFiles/decode.dir/src/decode.c.o.requires
	$(MAKE) -f CMakeFiles/decode.dir/build.make CMakeFiles/decode.dir/src/decode.c.o.provides.build
.PHONY : CMakeFiles/decode.dir/src/decode.c.o.provides

CMakeFiles/decode.dir/src/decode.c.o.provides.build: CMakeFiles/decode.dir/src/decode.c.o


# Object files for target decode
decode_OBJECTS = \
"CMakeFiles/decode.dir/src/decode.c.o"

# External object files for target decode
decode_EXTERNAL_OBJECTS =

decode: CMakeFiles/decode.dir/src/decode.c.o
decode: CMakeFiles/decode.dir/build.make
decode: libgene_encode.a
decode: CMakeFiles/decode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable decode"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/decode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/decode.dir/build: decode

.PHONY : CMakeFiles/decode.dir/build

CMakeFiles/decode.dir/requires: CMakeFiles/decode.dir/src/decode.c.o.requires

.PHONY : CMakeFiles/decode.dir/requires

CMakeFiles/decode.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/decode.dir/cmake_clean.cmake
.PHONY : CMakeFiles/decode.dir/clean

CMakeFiles/decode.dir/depend:
	cd /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build/CMakeFiles/decode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/decode.dir/depend

