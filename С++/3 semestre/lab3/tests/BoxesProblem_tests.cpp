#include "gtest/gtest.h"
#include "BoxesProblem.hpp"
#include <iostream>
#include <utility>
#include <vector>

using namespace lab2;
using namespace std;

TEST(BoxesProblem, Test1) {
    // Arrange
    ArraySequence<int> items;
    ArraySequence<int> iWeights;
    ArraySequence<int> iVolumes;
    ArraySequence<int> iCosts;
    ArraySequence<int> Boxes;
    ArraySequence<int> bWeight;
    ArraySequence<int> bVolume;
    ArraySequence<int> bCost;
    vector<int> items_ = {0, 1, 2, 3, 4};
    vector<int> iWeights_ = {10, 2, 3, 5, 8};
    vector<int> iVolumes_ = {8, 5, 3, 2, 10};
    vector<int> iCosts_ = {0, 1, 2, 3, 4};
    vector<int> Boxes_ = {0, 1, 2, 3, 4};
    vector<int> bWeight_ = {1, 3, 6, 8, 10};
    vector<int> bVolume_ = {1, 3, 6, 8, 10};
    vector<int> bCost_ = {0, 1, 2, 3, 4};
    for(int i = 0; i < items_.size(); i++) {
        items.PushBack(items_[i]);
        iWeights.PushBack(iWeights_[i]);
        iVolumes.PushBack(iVolumes_[i]);
        iCosts.PushBack(iCosts_[i]);
        Boxes.PushBack(Boxes_[i]);
        bWeight.PushBack(bWeight_[i]);
        bVolume.PushBack(bVolume_[i]);
        bCost.PushBack(bCost_[i]);
    }

    // Act
    auto result = sem3::BoxesProblem(items, iWeights, iVolumes, iCosts, Boxes, bWeight, bVolume, bCost);

    // Assert
    EXPECT_EQ(result.first, 12);
    EXPECT_EQ(result.second.GetSize(), 3);
    EXPECT_EQ(result.second[0].first, 4);
    EXPECT_EQ(result.second[0].second.GetSize(), 1);
    EXPECT_EQ(result.second[0].second[0], 4);
    EXPECT_EQ(result.second[1].first, 4);
    EXPECT_EQ(result.second[1].second.GetSize(), 3);
    EXPECT_EQ(result.second[1].second[0], 1);
    EXPECT_EQ(result.second[1].second[1], 2);
    EXPECT_EQ(result.second[1].second[2], 3);
    EXPECT_EQ(result.second[2].first, 4);
    EXPECT_EQ(result.second[2].second.GetSize(), 1);
    EXPECT_EQ(result.second[2].second[0], 0);
}