cmake_minimum_required(VERSION 3.22)
project(lab4 VERSION 0.0.1 LANGUAGES CXX)

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

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest_lib" "googletest_lib")

add_executable(lab4 main.cpp)
target_link_libraries(lab4 ${LAB2_LIBRARY} ${LAB3_LIBRARY})
target_include_directories(lab4 PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${SRC}")

add_executable(lab4_tests
        tests/N_ary_tree_tests.cpp)
target_include_directories(lab4_tests PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${SRC}")
target_link_libraries(lab4_tests gtest gtest_main ${LAB2_LIBRARY} ${LAB3_LIBRARY})

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab4 PRIVATE /W4)
    target_compile_options(lab4_tests PRIVATE /W4)
else()
    #target_compile_options(lab3 PRIVATE -Wall -Wextra -pedantic -Werror)
    #target_compile_options(lab3_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
