# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = D:\my-demo\compilingTheory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\my-demo\compilingTheory\build

# Include any dependencies generated for this target.
include CMakeFiles/lexical.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lexical.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lexical.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lexical.dir/flags.make

CMakeFiles/lexical.dir/main.c.obj: CMakeFiles/lexical.dir/flags.make
CMakeFiles/lexical.dir/main.c.obj: CMakeFiles/lexical.dir/includes_C.rsp
CMakeFiles/lexical.dir/main.c.obj: ../main.c
CMakeFiles/lexical.dir/main.c.obj: CMakeFiles/lexical.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\my-demo\compilingTheory\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lexical.dir/main.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-5~1.0-P\mingw32\bin\I6EEE3~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lexical.dir/main.c.obj -MF CMakeFiles\lexical.dir\main.c.obj.d -o CMakeFiles\lexical.dir\main.c.obj -c D:\my-demo\compilingTheory\main.c

CMakeFiles/lexical.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lexical.dir/main.c.i"
	C:\PROGRA~2\MINGW-~1\I686-5~1.0-P\mingw32\bin\I6EEE3~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\my-demo\compilingTheory\main.c > CMakeFiles\lexical.dir\main.c.i

CMakeFiles/lexical.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lexical.dir/main.c.s"
	C:\PROGRA~2\MINGW-~1\I686-5~1.0-P\mingw32\bin\I6EEE3~1.EXE $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\my-demo\compilingTheory\main.c -o CMakeFiles\lexical.dir\main.c.s

# Object files for target lexical
lexical_OBJECTS = \
"CMakeFiles/lexical.dir/main.c.obj"

# External object files for target lexical
lexical_EXTERNAL_OBJECTS =

lexical.exe: CMakeFiles/lexical.dir/main.c.obj
lexical.exe: CMakeFiles/lexical.dir/build.make
lexical.exe: nfaAnalyzer/libnfaAnalyzer.a
lexical.exe: datastructure/libdatastructure.a
lexical.exe: nfaAnalyzer/libnfaAnalyzer.a
lexical.exe: datastructure/libdatastructure.a
lexical.exe: readfile/libreadfile.a
lexical.exe: CMakeFiles/lexical.dir/linklibs.rsp
lexical.exe: CMakeFiles/lexical.dir/objects1.rsp
lexical.exe: CMakeFiles/lexical.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\my-demo\compilingTheory\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable lexical.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lexical.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lexical.dir/build: lexical.exe
.PHONY : CMakeFiles/lexical.dir/build

CMakeFiles/lexical.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lexical.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lexical.dir/clean

CMakeFiles/lexical.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\my-demo\compilingTheory D:\my-demo\compilingTheory D:\my-demo\compilingTheory\build D:\my-demo\compilingTheory\build D:\my-demo\compilingTheory\build\CMakeFiles\lexical.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lexical.dir/depend
