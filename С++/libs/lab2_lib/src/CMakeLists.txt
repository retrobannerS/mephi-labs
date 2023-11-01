cmake_minimum_required(VERSION 3.22)
project(lab2libbb)

set(CMAKE_CXX_STANDARD 23)

add_library(lab2 STATIC 
        DynamicArray.hpp
        LinkedList.hpp
        Sequence.hpp 
        ArraySequence.hpp 
        ListSequence.hpp
        Options.hpp 
        IEnumerable.hpp 
        IEnumerator.hpp
        TestFailedException.cpp
        TestFailedException.hpp)

set_target_properties(lab2 PROPERTIES LINKER_LANGUAGE CXX)
