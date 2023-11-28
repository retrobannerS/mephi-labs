#include "CombSorter.hpp"
#include "SmartArraySequence.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(CombSorter, Random) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(rand() % 100);
    }
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CombSorter, Sorted) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(i);
    }
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CombSorter, Reversed) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 10; i > 0; --i) {
        sequence->append(i);
    }
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CombSorter, Same) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(1);
    }
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CombSorter, Empty) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(CombSorter, One) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(1);
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 1);
}

TEST(CombSorter, Two) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(2);
    sequence->append(1);
    CombSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 2);
    EXPECT_TRUE(sequence->get(0) <= sequence->get(1));
}