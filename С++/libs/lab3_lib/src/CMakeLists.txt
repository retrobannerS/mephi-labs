cmake_minimum_required(VERSION 3.22)
project(lab3lib VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.lib")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
else()
    set(LAB2_LIBRARY "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/lib/lab2_library.a")
    set(LAB2_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../lab2_lib/includes")
endif()

add_library(lab3_library STATIC
        Collections/Matrixes/DiagMatrix.hpp
        Collections/Matrixes/RectangularMatrix.hpp
        Collections/Matrixes/SqMatrix.hpp
        Collections/Matrixes/TriangularMatrix.hpp
        Collections/Deque.hpp Collections/GVector.hpp
        Collections/PriorityQueue.hpp
        Collections/Queue.hpp
        Collections/Set.hpp Collections/Stack.hpp
        Data_types/mycomplex.cpp
        Data_types/mycomplex.h
        Data_types/person.cpp
        Data_types/Person.h
        BaseContainer.hpp
        Algos/hanoi/hanoi.cpp
        Algos/hanoi/hanoi.h
        Algos/PrimeNumbers/PrimeNumbers.cpp
        Algos/PrimeNumbers/PrimeNumbers.h
        Algos/AllSubSequences.hpp
        Algos/InversionsCount.hpp)

target_link_libraries(lab3_library ${LAB2_LIBRARY})
target_include_directories(lab3_library PRIVATE "${LAB2_INCLUDE_PATH}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
