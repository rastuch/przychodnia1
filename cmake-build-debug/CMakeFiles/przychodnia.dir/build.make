# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\programista\CLionProjects\przychodnia

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/przychodnia.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/przychodnia.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/przychodnia.dir/flags.make

CMakeFiles/przychodnia.dir/main.c.obj: CMakeFiles/przychodnia.dir/flags.make
CMakeFiles/przychodnia.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/przychodnia.dir/main.c.obj"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\przychodnia.dir\main.c.obj   -c C:\Users\programista\CLionProjects\przychodnia\main.c

CMakeFiles/przychodnia.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/przychodnia.dir/main.c.i"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\programista\CLionProjects\przychodnia\main.c > CMakeFiles\przychodnia.dir\main.c.i

CMakeFiles/przychodnia.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/przychodnia.dir/main.c.s"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\programista\CLionProjects\przychodnia\main.c -o CMakeFiles\przychodnia.dir\main.c.s

CMakeFiles/przychodnia.dir/sqlite3.c.obj: CMakeFiles/przychodnia.dir/flags.make
CMakeFiles/przychodnia.dir/sqlite3.c.obj: ../sqlite3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/przychodnia.dir/sqlite3.c.obj"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\przychodnia.dir\sqlite3.c.obj   -c C:\Users\programista\CLionProjects\przychodnia\sqlite3.c

CMakeFiles/przychodnia.dir/sqlite3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/przychodnia.dir/sqlite3.c.i"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\programista\CLionProjects\przychodnia\sqlite3.c > CMakeFiles\przychodnia.dir\sqlite3.c.i

CMakeFiles/przychodnia.dir/sqlite3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/przychodnia.dir/sqlite3.c.s"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\programista\CLionProjects\przychodnia\sqlite3.c -o CMakeFiles\przychodnia.dir\sqlite3.c.s

CMakeFiles/przychodnia.dir/patients.c.obj: CMakeFiles/przychodnia.dir/flags.make
CMakeFiles/przychodnia.dir/patients.c.obj: ../patients.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/przychodnia.dir/patients.c.obj"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\przychodnia.dir\patients.c.obj   -c C:\Users\programista\CLionProjects\przychodnia\patients.c

CMakeFiles/przychodnia.dir/patients.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/przychodnia.dir/patients.c.i"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\programista\CLionProjects\przychodnia\patients.c > CMakeFiles\przychodnia.dir\patients.c.i

CMakeFiles/przychodnia.dir/patients.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/przychodnia.dir/patients.c.s"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\programista\CLionProjects\przychodnia\patients.c -o CMakeFiles\przychodnia.dir\patients.c.s

CMakeFiles/przychodnia.dir/doctors.c.obj: CMakeFiles/przychodnia.dir/flags.make
CMakeFiles/przychodnia.dir/doctors.c.obj: ../doctors.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/przychodnia.dir/doctors.c.obj"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\przychodnia.dir\doctors.c.obj   -c C:\Users\programista\CLionProjects\przychodnia\doctors.c

CMakeFiles/przychodnia.dir/doctors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/przychodnia.dir/doctors.c.i"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\programista\CLionProjects\przychodnia\doctors.c > CMakeFiles\przychodnia.dir\doctors.c.i

CMakeFiles/przychodnia.dir/doctors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/przychodnia.dir/doctors.c.s"
	C:\Users\programista\ggc\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\programista\CLionProjects\przychodnia\doctors.c -o CMakeFiles\przychodnia.dir\doctors.c.s

# Object files for target przychodnia
przychodnia_OBJECTS = \
"CMakeFiles/przychodnia.dir/main.c.obj" \
"CMakeFiles/przychodnia.dir/sqlite3.c.obj" \
"CMakeFiles/przychodnia.dir/patients.c.obj" \
"CMakeFiles/przychodnia.dir/doctors.c.obj"

# External object files for target przychodnia
przychodnia_EXTERNAL_OBJECTS =

przychodnia.exe: CMakeFiles/przychodnia.dir/main.c.obj
przychodnia.exe: CMakeFiles/przychodnia.dir/sqlite3.c.obj
przychodnia.exe: CMakeFiles/przychodnia.dir/patients.c.obj
przychodnia.exe: CMakeFiles/przychodnia.dir/doctors.c.obj
przychodnia.exe: CMakeFiles/przychodnia.dir/build.make
przychodnia.exe: CMakeFiles/przychodnia.dir/linklibs.rsp
przychodnia.exe: CMakeFiles/przychodnia.dir/objects1.rsp
przychodnia.exe: CMakeFiles/przychodnia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable przychodnia.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\przychodnia.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/przychodnia.dir/build: przychodnia.exe

.PHONY : CMakeFiles/przychodnia.dir/build

CMakeFiles/przychodnia.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\przychodnia.dir\cmake_clean.cmake
.PHONY : CMakeFiles/przychodnia.dir/clean

CMakeFiles/przychodnia.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\programista\CLionProjects\przychodnia C:\Users\programista\CLionProjects\przychodnia C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug C:\Users\programista\CLionProjects\przychodnia\cmake-build-debug\CMakeFiles\przychodnia.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/przychodnia.dir/depend

