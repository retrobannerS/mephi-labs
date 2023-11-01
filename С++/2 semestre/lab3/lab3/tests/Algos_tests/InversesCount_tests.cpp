#include <gtest/gtest.h>
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "Algos/InversionsCount.hpp"

using namespace lab2;
using namespace lab3;

TEST(InversionsCountTest, TestInversionsCount) {
    // Arrange
    int values1[] = {4, 3, 2, 1};
    int values2[] = {1, 2, 3, 4};
    int values3[] = {5, 7, 1, 4, 6};
    ArraySequence<int> seq1(4, values1);
    int expected1 = 6;
    ArraySequence<int> seq2(4, values2);
    int expected2 = 0;
    ArraySequence<int> seq3(5, values3);
    int expected3 = 5;

    // Act & Assert
    ASSERT_EQ(InversionsCount(&seq1), expected1);
    ASSERT_EQ(InversionsCount(&seq2), expected2);
    ASSERT_EQ(InversionsCount(&seq3), expected3);
}

