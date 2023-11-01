cmake_minimum_required (VERSION 3.24)
project (lab1 C)

set (CMAKE_C_STANDARD 99)

add_executable (lab1 main.c ringinfo.c ringinfo.h types/INT.c types/INT.h types/REAL.c types/REAL.h types/COMPLEX.c types/COMPLEX.h Square_Matrix.c Square_Matrix.h Errors.h Errors.c)
