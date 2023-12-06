cmake_minimum_required(VERSION 3.22)
project(lab4 VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/includes")
set(LAB5_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab5_lib/includes")
set(LAB6_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab6_lib/includes")
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.lib")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/lib/lab3_library.lib")
elseif(APPLE)
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library_mac.a")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/lib/lab3_library_mac.a")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
endif()

add_library(lab8_lib STATIC
               BaseGraph.cpp
               DiGraph.cpp
               Graph.cpp
               DiGraphProcessor.cpp
               GraphProcessor.cpp
               )
target_include_directories(lab8_lib PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${LAB5_INCLUDE_PATH}" "${LAB6_INCLUDE_PATH}" "${SRC}" "${TESTS}")
target_link_libraries(lab8_lib ${LAB2_LIBRARY} ${LAB3_LIBRARY})

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab2_tests PRIVATE /W4)
else()
    #target_compile_options(lab2_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
