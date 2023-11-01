cmake_minimum_required (VERSION 3.24)
project (prog2 C)

set (CMAKE_C_STANDARD 99)

add_executable (prog2 main.c options.c sorts.c gen.c)
add_executable(trash main2.c options.c sorts.c gen.c)
