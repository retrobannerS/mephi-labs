cmake_minimum_required(VERSION 3.22)
project(lab3 VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/lib/lab2_library.lib")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/lib/lab3_library.lib")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/includes")
elseif(APPLE)
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/lib/lab2_library_mac.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/lib/lab3_library_mac.a")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/includes")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/lib/lab3_library.a")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/includes")
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest_lib" "googletest_lib")

add_executable(lab3 main.cpp )
target_link_libraries(lab3 ${LAB2_LIBRARY})
target_include_directories(lab3 PRIVATE "${LAB2_INCLUDE_PATH}")

add_executable(lab3_tests
        tests/BaseContainer_tests.cpp
        tests/Collections_tests/Stack_tests.cpp
        tests/Collections_tests/Queue_tests.cpp
        tests/Collections_tests/PriorityQueue_tests.cpp
        tests/Collections_tests/Deque_tests.cpp
        tests/Collections_tests/GVector_tests.cpp
        tests/Collections_tests/Matrixes_tests/SqMatrix_tests.cpp
        tests/Collections_tests/Matrixes_tests/TriangularMatrix_tests.cpp
        tests/Collections_tests/Matrixes_tests/DiagMatrix_tests.cpp
        tests/Collections_tests/Matrixes_tests/RectangularMatrix_tests.cpp
        tests/Collections_tests/Set_tests.cpp
        tests/Data_types_tests/mycomplex_tests.cpp
        tests/Data_types_tests/Person_tests.cpp
        tests/Algos_tests/Hanoi_tests.cpp
        tests/Algos_tests/AllSubSequences_tests.cpp
        tests/Algos_tests/InversesCount_tests.cpp
        tests/Algos_tests/PrimeNumbers_tests.cpp)
target_include_directories(lab3_tests PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}")
target_link_libraries(lab3_tests gtest gtest_main ${LAB2_LIBRARY} ${LAB3_LIBRARY})


if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab3 PRIVATE /W4)
    target_compile_options(lab3_tests PRIVATE /W4)
else()
    #target_compile_options(lab3 PRIVATE -Wall -Wextra -pedantic -Werror)
    #target_compile_options(lab3_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()