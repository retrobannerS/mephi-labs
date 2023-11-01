cmake_minimum_required (VERSION 3.23)
project (lab4 C)

set (CMAKE_C_STANDARD 99)
find_library(LIB readline readline)

add_executable (lab4 main.c rev.c)

target_link_libraries(lab4 LINK_PUBLIC ${LIB})
