#include "gtest/gtest.h"
#include "CocktailSorter.hpp"
#include "SmartArraySequence.hpp"

using namespace sem3;

TEST(CocktailSorter, Random) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(rand() % 100);
    }
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CocktailSorter, Sorted) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(i);
    }
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CocktailSorter, Reversed) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 10; i > 0; --i) {
        sequence->append(i);
    }
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CocktailSorter, Same) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    for (int i = 0; i < 10; ++i) {
        sequence->append(1);
    }
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    for (int i = 0; i < sequence->getSize() - 1; ++i) {
        EXPECT_TRUE(sequence->get(i) <= sequence->get(i + 1));
    }
}

TEST(CocktailSorter, Empty) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(CocktailSorter, One) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(1);
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 1);
}

TEST(CocktailSorter, Two) {
    // arrange
    SharedPtr<SmartSequence<int>> sequence = SharedPtr<SmartSequence<int>>(new SmartArraySequence<int>());
    sequence->append(2);
    sequence->append(1);
    CocktailSorter<int> sorter(sequence, [](int a, int b) { return a - b; });

    // act
    sorter.sort();

    // assert
    EXPECT_EQ(sequence->getSize(), 2);
    EXPECT_TRUE(sequence->get(0) <= sequence->get(1));
}