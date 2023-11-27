#include "gtest/gtest.h"
#include "InsertionSorter.hpp"
#include "SmartListSequence.hpp"

using namespace sem3;

TEST(InsertionSorter, Random) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(rand() % 100);
    }
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(InsertionSorter, Sorted) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(i);
    }
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(InsertionSorter, Reversed) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    for (int i = 10; i > 0; --i) {
        sequence->append(i);
    }
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(InsertionSorter, Same) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(1);
    }
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(InsertionSorter, Empty) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(InsertionSorter, One) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    sequence->append(1);
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 1);
}

TEST(InsertionSorter, Two) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartListSequence<int>());
    sequence->append(2);
    sequence->append(1);
    InsertionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 2);
    EXPECT_TRUE(sequence->get(0) <= sequence->get(1));
}