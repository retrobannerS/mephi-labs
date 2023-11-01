cmake_minimum_required(VERSION 3.22)
project(lab4_lib)

set(CMAKE_CXX_STANDARD 23)

add_library(lab4 STATIC trees/N_ary_tree.hpp trees/N_ary_tree.cpp)

set_target_properties(lab4 PROPERTIES LINKER_LANGUAGE CXX)
