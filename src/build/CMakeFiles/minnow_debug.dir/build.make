# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cs144/minnow/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs144/minnow/src/build

# Include any dependencies generated for this target.
include CMakeFiles/minnow_debug.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/minnow_debug.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/minnow_debug.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minnow_debug.dir/flags.make

CMakeFiles/minnow_debug.dir/byte_stream.o: CMakeFiles/minnow_debug.dir/flags.make
CMakeFiles/minnow_debug.dir/byte_stream.o: /home/cs144/minnow/src/byte_stream.cc
CMakeFiles/minnow_debug.dir/byte_stream.o: CMakeFiles/minnow_debug.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs144/minnow/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/minnow_debug.dir/byte_stream.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minnow_debug.dir/byte_stream.o -MF CMakeFiles/minnow_debug.dir/byte_stream.o.d -o CMakeFiles/minnow_debug.dir/byte_stream.o -c /home/cs144/minnow/src/byte_stream.cc

CMakeFiles/minnow_debug.dir/byte_stream.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minnow_debug.dir/byte_stream.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs144/minnow/src/byte_stream.cc > CMakeFiles/minnow_debug.dir/byte_stream.i

CMakeFiles/minnow_debug.dir/byte_stream.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minnow_debug.dir/byte_stream.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs144/minnow/src/byte_stream.cc -o CMakeFiles/minnow_debug.dir/byte_stream.s

CMakeFiles/minnow_debug.dir/byte_stream_helpers.o: CMakeFiles/minnow_debug.dir/flags.make
CMakeFiles/minnow_debug.dir/byte_stream_helpers.o: /home/cs144/minnow/src/byte_stream_helpers.cc
CMakeFiles/minnow_debug.dir/byte_stream_helpers.o: CMakeFiles/minnow_debug.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs144/minnow/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/minnow_debug.dir/byte_stream_helpers.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minnow_debug.dir/byte_stream_helpers.o -MF CMakeFiles/minnow_debug.dir/byte_stream_helpers.o.d -o CMakeFiles/minnow_debug.dir/byte_stream_helpers.o -c /home/cs144/minnow/src/byte_stream_helpers.cc

CMakeFiles/minnow_debug.dir/byte_stream_helpers.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minnow_debug.dir/byte_stream_helpers.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs144/minnow/src/byte_stream_helpers.cc > CMakeFiles/minnow_debug.dir/byte_stream_helpers.i

CMakeFiles/minnow_debug.dir/byte_stream_helpers.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minnow_debug.dir/byte_stream_helpers.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs144/minnow/src/byte_stream_helpers.cc -o CMakeFiles/minnow_debug.dir/byte_stream_helpers.s

CMakeFiles/minnow_debug.dir/reassembler.o: CMakeFiles/minnow_debug.dir/flags.make
CMakeFiles/minnow_debug.dir/reassembler.o: /home/cs144/minnow/src/reassembler.cc
CMakeFiles/minnow_debug.dir/reassembler.o: CMakeFiles/minnow_debug.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs144/minnow/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/minnow_debug.dir/reassembler.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minnow_debug.dir/reassembler.o -MF CMakeFiles/minnow_debug.dir/reassembler.o.d -o CMakeFiles/minnow_debug.dir/reassembler.o -c /home/cs144/minnow/src/reassembler.cc

CMakeFiles/minnow_debug.dir/reassembler.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minnow_debug.dir/reassembler.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs144/minnow/src/reassembler.cc > CMakeFiles/minnow_debug.dir/reassembler.i

CMakeFiles/minnow_debug.dir/reassembler.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minnow_debug.dir/reassembler.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs144/minnow/src/reassembler.cc -o CMakeFiles/minnow_debug.dir/reassembler.s

CMakeFiles/minnow_debug.dir/tcp_receiver.o: CMakeFiles/minnow_debug.dir/flags.make
CMakeFiles/minnow_debug.dir/tcp_receiver.o: /home/cs144/minnow/src/tcp_receiver.cc
CMakeFiles/minnow_debug.dir/tcp_receiver.o: CMakeFiles/minnow_debug.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs144/minnow/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/minnow_debug.dir/tcp_receiver.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minnow_debug.dir/tcp_receiver.o -MF CMakeFiles/minnow_debug.dir/tcp_receiver.o.d -o CMakeFiles/minnow_debug.dir/tcp_receiver.o -c /home/cs144/minnow/src/tcp_receiver.cc

CMakeFiles/minnow_debug.dir/tcp_receiver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minnow_debug.dir/tcp_receiver.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs144/minnow/src/tcp_receiver.cc > CMakeFiles/minnow_debug.dir/tcp_receiver.i

CMakeFiles/minnow_debug.dir/tcp_receiver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minnow_debug.dir/tcp_receiver.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs144/minnow/src/tcp_receiver.cc -o CMakeFiles/minnow_debug.dir/tcp_receiver.s

CMakeFiles/minnow_debug.dir/wrapping_integers.o: CMakeFiles/minnow_debug.dir/flags.make
CMakeFiles/minnow_debug.dir/wrapping_integers.o: /home/cs144/minnow/src/wrapping_integers.cc
CMakeFiles/minnow_debug.dir/wrapping_integers.o: CMakeFiles/minnow_debug.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs144/minnow/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/minnow_debug.dir/wrapping_integers.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/minnow_debug.dir/wrapping_integers.o -MF CMakeFiles/minnow_debug.dir/wrapping_integers.o.d -o CMakeFiles/minnow_debug.dir/wrapping_integers.o -c /home/cs144/minnow/src/wrapping_integers.cc

CMakeFiles/minnow_debug.dir/wrapping_integers.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minnow_debug.dir/wrapping_integers.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs144/minnow/src/wrapping_integers.cc > CMakeFiles/minnow_debug.dir/wrapping_integers.i

CMakeFiles/minnow_debug.dir/wrapping_integers.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minnow_debug.dir/wrapping_integers.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs144/minnow/src/wrapping_integers.cc -o CMakeFiles/minnow_debug.dir/wrapping_integers.s

# Object files for target minnow_debug
minnow_debug_OBJECTS = \
"CMakeFiles/minnow_debug.dir/byte_stream.o" \
"CMakeFiles/minnow_debug.dir/byte_stream_helpers.o" \
"CMakeFiles/minnow_debug.dir/reassembler.o" \
"CMakeFiles/minnow_debug.dir/tcp_receiver.o" \
"CMakeFiles/minnow_debug.dir/wrapping_integers.o"

# External object files for target minnow_debug
minnow_debug_EXTERNAL_OBJECTS =

libminnow_debug.a: CMakeFiles/minnow_debug.dir/byte_stream.o
libminnow_debug.a: CMakeFiles/minnow_debug.dir/byte_stream_helpers.o
libminnow_debug.a: CMakeFiles/minnow_debug.dir/reassembler.o
libminnow_debug.a: CMakeFiles/minnow_debug.dir/tcp_receiver.o
libminnow_debug.a: CMakeFiles/minnow_debug.dir/wrapping_integers.o
libminnow_debug.a: CMakeFiles/minnow_debug.dir/build.make
libminnow_debug.a: CMakeFiles/minnow_debug.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs144/minnow/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libminnow_debug.a"
	$(CMAKE_COMMAND) -P CMakeFiles/minnow_debug.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minnow_debug.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minnow_debug.dir/build: libminnow_debug.a
.PHONY : CMakeFiles/minnow_debug.dir/build

CMakeFiles/minnow_debug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minnow_debug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minnow_debug.dir/clean

CMakeFiles/minnow_debug.dir/depend:
	cd /home/cs144/minnow/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs144/minnow/src /home/cs144/minnow/src /home/cs144/minnow/src/build /home/cs144/minnow/src/build /home/cs144/minnow/src/build/CMakeFiles/minnow_debug.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minnow_debug.dir/depend

