cmake_minimum_required(VERSION 3.22)
project(lab1 VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.lib")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/lib/lab3_library.lib")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/includes")
elseif(APPLE)
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/lib/lab3_library_mac.a")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/includes")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
    set(LAB3_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/lib/lab3_library.a")
    set(LAB3_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab3_lib/includes")
endif()

add_library(lab5 STATIC 
            ControlBlock.hpp
            SharedPtr.hpp
            SmartArraySequence.hpp
            SmartDynamicArray.hpp
            SmartLinkedList.hpp
            SmartListSequence.hpp
            SmartSequence.hpp
            UniquePtr.hpp
            WeakPtr.hpp)

set_target_properties(lab5 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(lab5 PRIVATE "${LAB2_INCLUDE_PATH}" "${LAB3_INCLUDE_PATH}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(lab5 ${LAB2_LIBRARY} ${LAB3_LIBRARY})
