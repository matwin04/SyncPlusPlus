# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/frostie/Projects/SyncPlusPlus

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/frostie/Projects/SyncPlusPlus/build

# Utility rule file for SyncPlusPlus_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/SyncPlusPlus_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SyncPlusPlus_autogen.dir/progress.make

CMakeFiles/SyncPlusPlus_autogen: SyncPlusPlus_autogen/timestamp

SyncPlusPlus_autogen/timestamp: /opt/homebrew/share/qt/libexec/moc
SyncPlusPlus_autogen/timestamp: /opt/homebrew/share/qt/libexec/uic
SyncPlusPlus_autogen/timestamp: CMakeFiles/SyncPlusPlus_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/frostie/Projects/SyncPlusPlus/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target SyncPlusPlus"
	/opt/homebrew/bin/cmake -E cmake_autogen /Users/frostie/Projects/SyncPlusPlus/build/CMakeFiles/SyncPlusPlus_autogen.dir/AutogenInfo.json ""
	/opt/homebrew/bin/cmake -E touch /Users/frostie/Projects/SyncPlusPlus/build/SyncPlusPlus_autogen/timestamp

CMakeFiles/SyncPlusPlus_autogen.dir/codegen:
.PHONY : CMakeFiles/SyncPlusPlus_autogen.dir/codegen

SyncPlusPlus_autogen: CMakeFiles/SyncPlusPlus_autogen
SyncPlusPlus_autogen: SyncPlusPlus_autogen/timestamp
SyncPlusPlus_autogen: CMakeFiles/SyncPlusPlus_autogen.dir/build.make
.PHONY : SyncPlusPlus_autogen

# Rule to build all files generated by this target.
CMakeFiles/SyncPlusPlus_autogen.dir/build: SyncPlusPlus_autogen
.PHONY : CMakeFiles/SyncPlusPlus_autogen.dir/build

CMakeFiles/SyncPlusPlus_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SyncPlusPlus_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SyncPlusPlus_autogen.dir/clean

CMakeFiles/SyncPlusPlus_autogen.dir/depend:
	cd /Users/frostie/Projects/SyncPlusPlus/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/frostie/Projects/SyncPlusPlus /Users/frostie/Projects/SyncPlusPlus /Users/frostie/Projects/SyncPlusPlus/build /Users/frostie/Projects/SyncPlusPlus/build /Users/frostie/Projects/SyncPlusPlus/build/CMakeFiles/SyncPlusPlus_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SyncPlusPlus_autogen.dir/depend

