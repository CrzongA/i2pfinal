# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/leon/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.6682.181/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/leon/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.6682.181/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/finalproject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/finalproject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/finalproject.dir/flags.make

CMakeFiles/finalproject.dir/src/main.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/finalproject.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/main.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/main.c

CMakeFiles/finalproject.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/main.c > CMakeFiles/finalproject.dir/src/main.c.i

CMakeFiles/finalproject.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/main.c -o CMakeFiles/finalproject.dir/src/main.c.s

CMakeFiles/finalproject.dir/src/game.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/game.c.o: ../src/game.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/finalproject.dir/src/game.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/game.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/game.c

CMakeFiles/finalproject.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/game.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/game.c > CMakeFiles/finalproject.dir/src/game.c.i

CMakeFiles/finalproject.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/game.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/game.c -o CMakeFiles/finalproject.dir/src/game.c.s

CMakeFiles/finalproject.dir/src/scene_menu.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/scene_menu.c.o: ../src/scene_menu.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/finalproject.dir/src/scene_menu.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/scene_menu.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_menu.c

CMakeFiles/finalproject.dir/src/scene_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/scene_menu.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_menu.c > CMakeFiles/finalproject.dir/src/scene_menu.c.i

CMakeFiles/finalproject.dir/src/scene_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/scene_menu.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_menu.c -o CMakeFiles/finalproject.dir/src/scene_menu.c.s

CMakeFiles/finalproject.dir/src/scene_settings.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/scene_settings.c.o: ../src/scene_settings.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/finalproject.dir/src/scene_settings.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/scene_settings.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_settings.c

CMakeFiles/finalproject.dir/src/scene_settings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/scene_settings.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_settings.c > CMakeFiles/finalproject.dir/src/scene_settings.c.i

CMakeFiles/finalproject.dir/src/scene_settings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/scene_settings.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_settings.c -o CMakeFiles/finalproject.dir/src/scene_settings.c.s

CMakeFiles/finalproject.dir/src/scene_start.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/scene_start.c.o: ../src/scene_start.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/finalproject.dir/src/scene_start.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/scene_start.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_start.c

CMakeFiles/finalproject.dir/src/scene_start.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/scene_start.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_start.c > CMakeFiles/finalproject.dir/src/scene_start.c.i

CMakeFiles/finalproject.dir/src/scene_start.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/scene_start.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_start.c -o CMakeFiles/finalproject.dir/src/scene_start.c.s

CMakeFiles/finalproject.dir/src/scene_gameover.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/scene_gameover.c.o: ../src/scene_gameover.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/finalproject.dir/src/scene_gameover.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/scene_gameover.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_gameover.c

CMakeFiles/finalproject.dir/src/scene_gameover.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/scene_gameover.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_gameover.c > CMakeFiles/finalproject.dir/src/scene_gameover.c.i

CMakeFiles/finalproject.dir/src/scene_gameover.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/scene_gameover.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/scene_gameover.c -o CMakeFiles/finalproject.dir/src/scene_gameover.c.s

CMakeFiles/finalproject.dir/src/shared.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/shared.c.o: ../src/shared.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/finalproject.dir/src/shared.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/shared.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/shared.c

CMakeFiles/finalproject.dir/src/shared.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/shared.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/shared.c > CMakeFiles/finalproject.dir/src/shared.c.i

CMakeFiles/finalproject.dir/src/shared.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/shared.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/shared.c -o CMakeFiles/finalproject.dir/src/shared.c.s

CMakeFiles/finalproject.dir/src/utility.c.o: CMakeFiles/finalproject.dir/flags.make
CMakeFiles/finalproject.dir/src/utility.c.o: ../src/utility.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/finalproject.dir/src/utility.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/finalproject.dir/src/utility.c.o   -c /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/utility.c

CMakeFiles/finalproject.dir/src/utility.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/finalproject.dir/src/utility.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/utility.c > CMakeFiles/finalproject.dir/src/utility.c.i

CMakeFiles/finalproject.dir/src/utility.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/finalproject.dir/src/utility.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/src/utility.c -o CMakeFiles/finalproject.dir/src/utility.c.s

# Object files for target finalproject
finalproject_OBJECTS = \
"CMakeFiles/finalproject.dir/src/main.c.o" \
"CMakeFiles/finalproject.dir/src/game.c.o" \
"CMakeFiles/finalproject.dir/src/scene_menu.c.o" \
"CMakeFiles/finalproject.dir/src/scene_settings.c.o" \
"CMakeFiles/finalproject.dir/src/scene_start.c.o" \
"CMakeFiles/finalproject.dir/src/scene_gameover.c.o" \
"CMakeFiles/finalproject.dir/src/shared.c.o" \
"CMakeFiles/finalproject.dir/src/utility.c.o"

# External object files for target finalproject
finalproject_EXTERNAL_OBJECTS =

../finalproject: CMakeFiles/finalproject.dir/src/main.c.o
../finalproject: CMakeFiles/finalproject.dir/src/game.c.o
../finalproject: CMakeFiles/finalproject.dir/src/scene_menu.c.o
../finalproject: CMakeFiles/finalproject.dir/src/scene_settings.c.o
../finalproject: CMakeFiles/finalproject.dir/src/scene_start.c.o
../finalproject: CMakeFiles/finalproject.dir/src/scene_gameover.c.o
../finalproject: CMakeFiles/finalproject.dir/src/shared.c.o
../finalproject: CMakeFiles/finalproject.dir/src/utility.c.o
../finalproject: CMakeFiles/finalproject.dir/build.make
../finalproject: CMakeFiles/finalproject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable ../finalproject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/finalproject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/finalproject.dir/build: ../finalproject

.PHONY : CMakeFiles/finalproject.dir/build

CMakeFiles/finalproject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/finalproject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/finalproject.dir/clean

CMakeFiles/finalproject.dir/depend:
	cd /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug /media/leon/4442AE2F42AE25A022/LEONLAH/NTHU/109-semA/IntroToProgramming/finalproject_clean/project/cmake-build-debug/CMakeFiles/finalproject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/finalproject.dir/depend

