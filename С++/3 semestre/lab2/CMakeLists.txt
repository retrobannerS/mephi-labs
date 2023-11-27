cmake_minimum_required(VERSION 3.22)
project(lab1 VERSION 0.0.1 LANGUAGES CXX)

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

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest_lib" "googletest_lib")

add_executable(lab2_tests
                tests/BubbleSorter_tests.cpp
                tests/InsertionSorter_tests.cpp
                tests/CocktailSorter_tests.cpp
                tests/SelectionSorter_tests.cpp
                tests/CountingSorter_tests.cpp
                tests/BinaryInsertionSorter_tests.cpp
                tests/DoubleSelectionSorter_tests.cpp
                tests/InsertionByTreeSorter_tests.cpp
                tests/MergeSorter_tests.cpp
                tests/HeapSorter_tests.cpp
                )
target_include_directories(lab2_tests PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${LAB5_INCLUDE_PATH}" "${SRC}" "${TESTS}")
target_link_libraries(lab2_tests gtest gtest_main ${LAB2_LIBRARY} ${LAB3_LIBRARY})

#add_executable(lab2_ui src/BubbleSort.cpp)
#target_include_directories(lab2_ui PRIVATE "${SRC}")

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab2_tests PRIVATE /W4)
else()
    #target_compile_options(lab2_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
