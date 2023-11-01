cmake_minimum_required (VERSION 3.25)
project (lab2correct2)

set (CMAKE_CXX_STANDARD 23)

add_executable (lab2test
                RunTests.cpp
                Tests/UnitTest.cpp
                Tests/TestCluster.cpp
                Tests/TestRunner.cpp
                Tests/DynamicArrayTests/DynamicArrayTests.cpp
                Tests/LinkedListTests/LinkedListTests.cpp
                Tests/ArraySequenceTests/ArraySequenceTests.cpp
                Tests/ListSequenceTests/ListSequenceTests.cpp
                MyExceptions/TestFailedException.cpp
                )

add_library(lab2 STATIC Data_Classes/DynamicArray.hpp Data_Classes/DynamicArray.cpp)

