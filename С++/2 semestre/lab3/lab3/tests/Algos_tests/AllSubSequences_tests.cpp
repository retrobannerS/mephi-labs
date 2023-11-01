#include "Algos/AllSubSequences.hpp"
#include <gtest/gtest.h>
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include <vector>

using namespace lab2;
using namespace lab3;

TEST(AllSubSequencesTest, TestAllSubSequences) {
    // Arrange
    int values[3] = {1, 2, 3};
    ArraySequence<int> seq(3, values);
    std::vector<std::vector<int>> expected = {{1}, {1, 2}, {1, 2, 3}, {2}, {2, 3}, {3}};

    // Act
    Sequence<Sequence<int> *> *result = AllSubSequences(&seq);

    // Assert
    EXPECT_EQ(result->GetSize(), expected.size());

    for (int i = 0; i < expected.size(); ++i) {
        const Sequence<int>* subSeq = result->Get(i);
        EXPECT_EQ(subSeq->GetSize(), expected[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j) {
            EXPECT_EQ(subSeq->Get(j), expected[i][j]);
        }
        delete result->Get(i);
    }

    delete result;
}
