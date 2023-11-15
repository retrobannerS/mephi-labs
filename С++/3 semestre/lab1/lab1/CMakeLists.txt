cmake_minimum_required(VERSION 3.22)
project(lab1 VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/lib/lab2_library.lib")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/lib/lab3_library.lib")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/includes")
elseif(APPLE)
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/lib/lab3_library_mac.a")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/includes")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/lib/lab3_library.a")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/lab3_lib/includes")
endif()

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS "${CMAKE_CURRENT_SOURCE_DIR}/Tests")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest_lib" "googletest_lib")

add_executable(lab1_tests 
                tests/SmartPtr_tests/UniquePtr_tests/UniquePtr_tests.cpp
                tests/SmartPtr_tests/UniquePtr_tests/UniquePtrArray_tests.cpp
                tests/SmartPtr_tests/ControlBlock_tests/ControlBlock_tests.cpp
                tests/SmartPtr_tests/ControlBlock_tests/ControlBlockArray_tests.cpp
                tests/SmartPtr_tests/SharedPtr_tests/SharedPtr_tests.cpp
                tests/SmartPtr_tests/SharedPtr_tests/SharedPtrArray_tests.cpp
                )
target_include_directories(lab1_tests PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${SRC}" "${TESTS}")
target_link_libraries(lab1_tests gtest gtest_main ${LAB2_LIBRARY} ${LAB3_LIBRARY})

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab1 PRIVATE /W4)
    target_compile_options(lab1_tests PRIVATE /W4)
else()
    #target_compile_options(lab3 PRIVATE -Wall -Wextra -pedantic -Werror)
    #target_compile_options(lab3_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
