# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos"

# Include any dependencies generated for this target.
include CMakeFiles/lab1_tests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab1_tests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1_tests.dir/flags.make

CMakeFiles/lab1_tests.dir/main.cpp.o: CMakeFiles/lab1_tests.dir/flags.make
CMakeFiles/lab1_tests.dir/main.cpp.o: /Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3\ semestre/lab1/lab1/main.cpp
CMakeFiles/lab1_tests.dir/main.cpp.o: CMakeFiles/lab1_tests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab1_tests.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab1_tests.dir/main.cpp.o -MF CMakeFiles/lab1_tests.dir/main.cpp.o.d -o CMakeFiles/lab1_tests.dir/main.cpp.o -c "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/main.cpp"

CMakeFiles/lab1_tests.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab1_tests.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/main.cpp" > CMakeFiles/lab1_tests.dir/main.cpp.i

CMakeFiles/lab1_tests.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab1_tests.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/main.cpp" -o CMakeFiles/lab1_tests.dir/main.cpp.s

# Object files for target lab1_tests
lab1_tests_OBJECTS = \
"CMakeFiles/lab1_tests.dir/main.cpp.o"

# External object files for target lab1_tests
lab1_tests_EXTERNAL_OBJECTS =

lab1_tests: CMakeFiles/lab1_tests.dir/main.cpp.o
lab1_tests: CMakeFiles/lab1_tests.dir/build.make
lab1_tests: lib/libgtest.a
lab1_tests: lib/libgtest_main.a
lab1_tests: /Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3\ semestre/lab1/lab1/../../../libs/lab2_lib/lib/lab2_library.a
lab1_tests: /Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3\ semestre/lab1/lab1/../../../libs/lab3_lib/lib/lab3_library_mac.a
lab1_tests: lib/libgtest.a
lab1_tests: CMakeFiles/lab1_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab1_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab1_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1_tests.dir/build: lab1_tests
.PHONY : CMakeFiles/lab1_tests.dir/build

CMakeFiles/lab1_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab1_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab1_tests.dir/clean

CMakeFiles/lab1_tests.dir/depend:
	cd "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1" "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1" "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos" "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos" "/Users/retrobanner/Yandex.Disk.localized/Study/mephi_labs/С++/3 semestre/lab1/lab1/cmake-build-macos/CMakeFiles/lab1_tests.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/lab1_tests.dir/depend

