# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/camsonne/Simulation/DDVCS/g4sbsddvs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/camsonne/Simulation/DDVCS/g4sbsddvs/build

# Utility rule file for G4SBS.

CMakeFiles/G4SBS: g4sbs

G4SBS: CMakeFiles/G4SBS
G4SBS: CMakeFiles/G4SBS.dir/build.make
.PHONY : G4SBS

# Rule to build all files generated by this target.
CMakeFiles/G4SBS.dir/build: G4SBS
.PHONY : CMakeFiles/G4SBS.dir/build

CMakeFiles/G4SBS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/G4SBS.dir/cmake_clean.cmake
.PHONY : CMakeFiles/G4SBS.dir/clean

CMakeFiles/G4SBS.dir/depend:
	cd /home/camsonne/Simulation/DDVCS/g4sbsddvs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/camsonne/Simulation/DDVCS/g4sbsddvs /home/camsonne/Simulation/DDVCS/g4sbsddvs /home/camsonne/Simulation/DDVCS/g4sbsddvs/build /home/camsonne/Simulation/DDVCS/g4sbsddvs/build /home/camsonne/Simulation/DDVCS/g4sbsddvs/build/CMakeFiles/G4SBS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/G4SBS.dir/depend

