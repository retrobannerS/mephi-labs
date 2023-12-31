cmake_minimum_required(VERSION 3.22)
project(lab3 VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/includes")
set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/includes")
set(LAB5_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab5_lib/includes")
set(LAB6_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab6_lib/includes")
set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TESTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/googletest_lib" "googletest_lib")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/lib/lab2_library.lib")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/lib/lab3_library.lib")
elseif(APPLE)
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/lib/lab2_library_mac.a")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/lib/lab3_library_mac.a")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab2_lib/lib/lab2_library.a")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../libs/lab3_lib/lib/lab3_library.a")
endif()

add_executable(lab3_tests
               src/BoxesProblem.cpp
               tests/BoxesProblem_tests.cpp
                        )
target_include_directories(lab3_tests PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${LAB5_INCLUDE_PATH}" "${LAB6_INCLUDE_PATH}" "${SRC}" "${TESTS}")
target_link_libraries(lab3_tests gtest gtest_main ${LAB2_LIBRARY} ${LAB3_LIBRARY})

add_executable(lab3_ui UI/main.cpp)
target_include_directories(lab3_ui PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" "${LAB5_INCLUDE_PATH}" "${LAB6_INCLUDE_PATH}")
target_link_libraries(lab3_ui ${LAB2_LIBRARY} ${LAB3_LIBRARY} sfml-graphics sfml-window sfml-system)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    target_compile_options(lab2_tests PRIVATE /W4)
else()
    #target_compile_options(lab2_tests PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
