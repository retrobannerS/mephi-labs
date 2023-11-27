#include "SelectionSorter.hpp"
#include "SmartArraySequence.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(SelectionSorter, Random) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(rand() % 100);
    }
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(SelectionSorter, Sorted) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(i);
    }
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(SelectionSorter, Reversed) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 10; i > 0; --i) {
        sequence->append(i);
    }
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(SelectionSorter, Same) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(1);
    }
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(SelectionSorter, Empty) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(SelectionSorter, One) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(1);
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 1);
}

TEST(SelectionSorter, Two) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(2);
    sequence->append(1);
    SelectionSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 2);
    EXPECT_TRUE(sequence->get(0) <= sequence->get(1));
}