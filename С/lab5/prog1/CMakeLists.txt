cmake_minimum_required (VERSION 3.24)
project (prog C)

set (CMAKE_C_STANDARD 99)

add_executable (prog main.c options.c met.c sorts.c)
