cmake_minimum_required (VERSION 3.23)
project (Prog2 C)

set (CMAKE_C_STANDARD 99)
find_library(LIB readline readline)

add_executable (Prog2 main.c mystring.c rev.c myreadline.c)
add_executable(2 komarov.c)

target_link_libraries(2 LINK_PUBLIC ${LIB})