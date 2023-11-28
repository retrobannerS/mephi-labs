#include "CycleSorter.hpp"
#include "SmartArraySequence.hpp"
#include "gtest/gtest.h"
#include <iostream>

using namespace sem3;

TEST(CycleSorter, Random) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(rand() % 100);
    }
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CycleSorter, Sorted) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(i);
    }
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CycleSorter, Reversed) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 10; i > 0; --i) {
        sequence->append(i);
    }
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CycleSorter, Same) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(1);
    }
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CycleSorter, Empty) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(CycleSorter, One) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(1);
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 1);
}

TEST(CycleSorter, Two) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(2);
    sequence->append(1);
    CycleSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 2);
    EXPECT_TRUE(sequence->get(0) <= sequence->get(1));
}