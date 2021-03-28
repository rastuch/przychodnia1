cmake_minimum_required(VERSION 3.17)
project(przychodnia C)

set(CMAKE_C_STANDARD 99)

add_executable(przychodnia main.c sqlite3.c sqlite3.h patients.c patients.h doctors.c doctors.h)