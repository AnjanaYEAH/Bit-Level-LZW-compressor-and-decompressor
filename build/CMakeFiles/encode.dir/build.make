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
include CMakeFiles/encode.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/encode.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/encode.dir/flags.make

CMakeFiles/encode.dir/src/encode.c.o: CMakeFiles/encode.dir/flags.make
CMakeFiles/encode.dir/src/encode.c.o: ../src/encode.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/encode.dir/src/encode.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/encode.dir/src/encode.c.o   -c /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/src/encode.c

CMakeFiles/encode.dir/src/encode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/encode.dir/src/encode.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/src/encode.c > CMakeFiles/encode.dir/src/encode.c.i

CMakeFiles/encode.dir/src/encode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/encode.dir/src/encode.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/src/encode.c -o CMakeFiles/encode.dir/src/encode.c.s

CMakeFiles/encode.dir/src/encode.c.o.requires:

.PHONY : CMakeFiles/encode.dir/src/encode.c.o.requires

CMakeFiles/encode.dir/src/encode.c.o.provides: CMakeFiles/encode.dir/src/encode.c.o.requires
	$(MAKE) -f CMakeFiles/encode.dir/build.make CMakeFiles/encode.dir/src/encode.c.o.provides.build
.PHONY : CMakeFiles/encode.dir/src/encode.c.o.provides

CMakeFiles/encode.dir/src/encode.c.o.provides.build: CMakeFiles/encode.dir/src/encode.c.o


# Object files for target encode
encode_OBJECTS = \
"CMakeFiles/encode.dir/src/encode.c.o"

# External object files for target encode
encode_EXTERNAL_OBJECTS =

encode: CMakeFiles/encode.dir/src/encode.c.o
encode: CMakeFiles/encode.dir/build.make
encode: libgene_encode.a
encode: CMakeFiles/encode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable encode"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/encode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/encode.dir/build: encode

.PHONY : CMakeFiles/encode.dir/build

CMakeFiles/encode.dir/requires: CMakeFiles/encode.dir/src/encode.c.o.requires

.PHONY : CMakeFiles/encode.dir/requires

CMakeFiles/encode.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/encode.dir/cmake_clean.cmake
.PHONY : CMakeFiles/encode.dir/clean

CMakeFiles/encode.dir/depend:
	cd /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build /home/anjana/Documents/cw3-cs0019-bit-lzw-AnjanaYEAH-master/build/CMakeFiles/encode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/encode.dir/depend

