cmake_minimum_required(VERSION 3.22)
project(lab6_library VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/includes")
set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/includes")
set(LAB5_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab5_lib/includes")
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/lib/lab2_library.lib")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/lib/lab3_library.lib")
elseif(APPLE)
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/lib/lab2_library_mac.a")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/lib/lab3_library_mac.a")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/includes")
endif()

add_library(lab6_library_mac STATIC 
            src/BaseSorter.hpp
            src/BinaryInsertionSorter.hpp
            src/BubbleSorter.hpp
            src/CocktailSorter.hpp
            src/CombSorter.hpp
            src/CountingSorter.hpp
            src/CycleSorter.hpp
            src/DoubleSelectionSorter.hpp
            src/GnomeSorter.hpp
            src/HeapSorter.hpp
            src/InsertionByTreeSorter.hpp
            src/InsertionSorter.hpp
            src/MergeSorter.hpp
            src/OddEvenSorter.hpp
            src/QuickSorter.hpp
            src/RadixSorter.hpp
            src/SelectionSorter.hpp
            src/ShellSorter.hpp)
target_include_directories(lab6_library_mac PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${LAB5_INCLUDE_PATH}" "${SRC}")
target_link_libraries(lab6_library_mac ${LAB2_LIBRARY} ${LAB3_LIBRARY})

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab2_tests PRIVATE /W4)
else()
    #target_compile_options(lab2_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
