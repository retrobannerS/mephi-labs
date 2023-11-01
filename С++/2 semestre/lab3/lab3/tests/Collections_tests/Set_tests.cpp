#include <stdexcept>
#include "gtest/gtest.h"
#include "Collections/Set.hpp"

using namespace std;
using namespace lab3;

TEST(Set, Constructor) {
    //arrange&act
    Set<int> set;
    //assert
    EXPECT_EQ(set.power(), 0);
}

TEST(Set, CopyConstructor) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    Set<int> set4;
    //act
    Set<int> set2(set);
    Set<int> set3 = set;
    Set<int> set5(set4);
    //assert
    EXPECT_TRUE(set5.empty());
    EXPECT_EQ(set2.power(), 3);
    EXPECT_EQ(set3.power(), 3);
    EXPECT_TRUE(set2.contains(1));
    EXPECT_TRUE(set2.contains(2));
    EXPECT_TRUE(set2.contains(3));
    EXPECT_TRUE(set3.contains(1));
    EXPECT_TRUE(set3.contains(2));
    EXPECT_TRUE(set3.contains(3));
}

TEST(Set, AssignmentOperator) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    Set<int> set2;
    Set<int> set3;
    Set<int> set4;
    //act
    set3 = set;
    set4 = set2;
    //assert
    EXPECT_TRUE(set4.empty());
    EXPECT_EQ(set3.power(), 3);
    EXPECT_TRUE(set3.contains(1));
    EXPECT_TRUE(set3.contains(2));
    EXPECT_TRUE(set3.contains(3));
}

TEST(Set, Contains) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    //act&assert
    EXPECT_TRUE(set.contains(1));
    EXPECT_TRUE(set.contains(2));
    EXPECT_TRUE(set.contains(3));
    EXPECT_FALSE(set.contains(4));
    EXPECT_FALSE(set.contains(5));
    EXPECT_FALSE(set.contains(6));
}

TEST(Set, power) {
    //arrange
    Set<int> set;
    //act&assert
    EXPECT_EQ(set.power(), 0);
    set.add(1);
    EXPECT_EQ(set.power(), 1);
    set.add(2);
    EXPECT_EQ(set.power(), 2);
    set.add(3);
    EXPECT_EQ(set.power(), 3);
    set.remove(1);
    EXPECT_EQ(set.power(), 2);
    set.remove(2);
    EXPECT_EQ(set.power(), 1);
    set.remove(3);
    EXPECT_EQ(set.power(), 0);
    set.remove(3);
    EXPECT_EQ(set.power(), 0);
}

TEST(Set, Empty) {
    //arrange
    Set<int> set;
    //act&assert
    EXPECT_TRUE(set.empty());
    set.add(1);
    EXPECT_FALSE(set.empty());
    set.remove(1);
    EXPECT_TRUE(set.empty());
}

TEST(Set, Add) {
    //arrange
    Set<int> set;
    //act
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(3);
    set.add(2);
    set.add(1);
    //assert
    EXPECT_EQ(set.power(), 3);
    EXPECT_TRUE(set.contains(1));
    EXPECT_TRUE(set.contains(2));
    EXPECT_TRUE(set.contains(3));
}

TEST(Set, Remove) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    //act
    set.remove(2);
    set.remove(2);
    //assert
    EXPECT_EQ(set.power(), 2);
    EXPECT_TRUE(set.contains(1));
    EXPECT_FALSE(set.contains(2));
    EXPECT_TRUE(set.contains(3));
}

TEST(Set, clear) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    //act
    set.clear();
    //assert
    EXPECT_EQ(set.power(), 0);
    EXPECT_FALSE(set.contains(1));
    EXPECT_FALSE(set.contains(2));
    EXPECT_FALSE(set.contains(3));
}

TEST(Set, Union) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    Set<int> set2;
    set2.add(4);
    set2.add(5);
    set2.add(6);

    Set<int> set3;
    set3.add(1);
    set3.add(2);
    set3.add(3);
    Set<int> set4;
    set4.add(2);
    set4.add(3);
    set4.add(4);
    //act
    Set<int> set5 = set.union_with(set2);
    Set<int> set6 = set2.union_with(set);
    Set<int> set7 = set3.union_with(set4);
    Set<int> set8 = set4.union_with(set3);
    //assert
    EXPECT_EQ(set5.power(), 6);
    EXPECT_TRUE(set5.contains(1));
    EXPECT_TRUE(set5.contains(2));
    EXPECT_TRUE(set5.contains(3));
    EXPECT_TRUE(set5.contains(4));
    EXPECT_TRUE(set5.contains(5));
    EXPECT_TRUE(set5.contains(6));
    EXPECT_EQ(set6.power(), 6);
    EXPECT_TRUE(set6.contains(1));
    EXPECT_TRUE(set6.contains(2));
    EXPECT_TRUE(set6.contains(3));
    EXPECT_TRUE(set6.contains(4));
    EXPECT_TRUE(set6.contains(5));
    EXPECT_TRUE(set6.contains(6));
    EXPECT_TRUE(set5 == set6);
    EXPECT_EQ(set7.power(), 4);
    EXPECT_TRUE(set7.contains(1));
    EXPECT_TRUE(set7.contains(2));
    EXPECT_TRUE(set7.contains(3));
    EXPECT_TRUE(set7.contains(4));
    EXPECT_EQ(set8.power(), 4);
    EXPECT_TRUE(set8.contains(1));
    EXPECT_TRUE(set8.contains(2));
    EXPECT_TRUE(set8.contains(3));
    EXPECT_TRUE(set8.contains(4));
    EXPECT_TRUE(set7 == set8);
}

TEST(Set, emptyUnion) {
    //arrange
    Set<int> set;
    Set<int> set2;
    Set<int> set5;
    set5.add(1);
    set5.add(2);
    //act
    Set<int> set3 = set.union_with(set2);
    Set<int> set4 = set2.union_with(set);
    Set<int> set6 = set.union_with(set5);
    //assert
    EXPECT_EQ(set3.power(), 0);
    EXPECT_EQ(set4.power(), 0);
    EXPECT_TRUE(set3 == set4);
    EXPECT_EQ(set6.power(), 2);
    EXPECT_TRUE(set6.contains(1));
    EXPECT_TRUE(set6.contains(2));
}

TEST(Set, Intersection) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    Set<int> set2;
    set2.add(2);
    set2.add(3);
    set2.add(4);
    Set<int> set3;
    set3.add(1);
    set3.add(2);
    set3.add(3);
    Set<int> set4;
    set4.add(4);
    set4.add(5);
    set4.add(6);
    //act
    Set<int> set5 = set.intersection_with(set2);
    Set<int> set6 = set2.intersection_with(set);
    Set<int> set7 = set3.intersection_with(set4);
    Set<int> set8 = set4.intersection_with(set3);
    //assert
    EXPECT_EQ(set5.power(), 2);
    EXPECT_TRUE(set5.contains(2));
    EXPECT_TRUE(set5.contains(3));
    EXPECT_EQ(set6.power(), 2);
    EXPECT_TRUE(set6.contains(2));
    EXPECT_TRUE(set6.contains(3));
    EXPECT_TRUE(set5 == set6);
    EXPECT_TRUE(set7.empty());
    EXPECT_TRUE(set8.empty());
    EXPECT_TRUE(set7 == set8);
}

TEST(Set, emptyIntersection) {
    //arrange
    Set<int> set;
    Set<int> set2;
    Set<int> set5;
    set5.add(1);
    set5.add(2);
    //act
    Set<int> set3 = set.intersection_with(set2);
    Set<int> set4 = set2.intersection_with(set);
    Set<int> set6 = set.intersection_with(set5);
    //assert
    EXPECT_EQ(set3.power(), 0);
    EXPECT_EQ(set4.power(), 0);
    EXPECT_TRUE(set3 == set4);
    EXPECT_EQ(set6.power(), 0);
}

TEST(Set, Difference) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    Set<int> set2;
    set2.add(2);
    set2.add(3);
    set2.add(4);
    Set<int> set3;
    set3.add(1);
    set3.add(2);
    set3.add(3);
    Set<int> set4;
    set4.add(4);
    set4.add(5);
    set4.add(6);
    //act
    Set<int> set5 = set.difference_with(set2);
    Set<int> set6 = set2.difference_with(set);
    Set<int> set7 = set3.difference_with(set4);
    Set<int> set8 = set4.difference_with(set3);
    //assert
    EXPECT_EQ(set5.power(), 1);
    EXPECT_TRUE(set5.contains(1));
    EXPECT_EQ(set6.power(), 1);
    EXPECT_TRUE(set6.contains(4));
    EXPECT_FALSE(set5 == set6);
    EXPECT_EQ(set7.power(), 3);
    EXPECT_TRUE(set7.contains(1));
    EXPECT_TRUE(set7.contains(2));
    EXPECT_TRUE(set7.contains(3));
    EXPECT_EQ(set8.power(), 3);
    EXPECT_TRUE(set8.contains(4));
    EXPECT_TRUE(set8.contains(5));
    EXPECT_TRUE(set8.contains(6));
    EXPECT_FALSE(set7 == set8);
}

TEST(Set, emptyDifference) {
    //arrange
    Set<int> set;
    Set<int> set2;
    Set<int> set5;
    set5.add(1);
    set5.add(2);
    //act
    Set<int> set3 = set.difference_with(set2);
    Set<int> set4 = set2.difference_with(set);
    Set<int> set6 = set.difference_with(set5);
    //assert
    EXPECT_EQ(set3.power(), 0);
    EXPECT_EQ(set4.power(), 0);
    EXPECT_TRUE(set3 == set4);
    EXPECT_EQ(set6.power(), 0);
}

TEST(Set, map) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(4);
    auto f = [](const int &x) { return x * x; };
    //act
    Set<int> set2 = set.map(f);
    //assert
    EXPECT_EQ(set2.power(), 4);
    EXPECT_TRUE(set2.contains(1));
    EXPECT_TRUE(set2.contains(4));
    EXPECT_TRUE(set2.contains(9));
    EXPECT_TRUE(set2.contains(16));
}

TEST(Set, emptyMap) {
    //arrange
    Set<int> set;
    auto f = [](const int &x) { return x * x; };
    //act
    Set<int> set2 = set.map(f);
    //assert
    EXPECT_EQ(set2.power(), 0);
}

TEST(Set, where) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(4);
    auto f = [](const int &x) { return x % 2 == 0; };
    //act
    Set<int> set2 = set.where(f);
    //assert
    EXPECT_EQ(set2.power(), 2);
    EXPECT_TRUE(set2.contains(2));
    EXPECT_TRUE(set2.contains(4));
}

TEST(Set, emptyWhere) {
    //arrange
    Set<int> set;
    auto f = [](const int &x) { return x % 2 == 0; };
    //act
    Set<int> set2 = set.where(f);
    //assert
    EXPECT_EQ(set2.power(), 0);
}

TEST(Set, isSubset) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(4);
    Set<int> set2;
    set2.add(1);
    set2.add(2);
    set2.add(3);
    Set<int> set3;
    set3.add(1);
    set3.add(2);
    set3.add(3);
    set3.add(4);
    set3.add(5);
    Set<int> set4(set3);
    //act
    bool b1 = set2.is_subset_of(set);
    bool b2 = set.is_subset_of(set2);
    bool b3 = set.is_subset_of(set3);
    bool b4 = set3.is_subset_of(set);
    bool b5 = set4.is_subset_of(set3);
    bool b6 = set3.is_subset_of(set4);
    //assert
    EXPECT_TRUE(b1);
    EXPECT_FALSE(b2);
    EXPECT_TRUE(b3);
    EXPECT_FALSE(b4);
    EXPECT_TRUE(b5);
    EXPECT_TRUE(b6);
}

TEST(Set, operator_is_equal) {
    //arrange
    Set<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.add(4);
    Set<int> set2;
    set2.add(1);
    set2.add(2);
    set2.add(3);
    Set<int> set3;
    set3.add(1);
    set3.add(2);
    set3.add(3);
    set3.add(4);
    set3.add(5);
    Set<int> set4(set3);
    //act
    bool b1 = set == set2;
    bool b2 = set == set3;
    bool b3 = set3 == set;
    bool b4 = set3 == set4;
    //assert
    EXPECT_FALSE(b1);
    EXPECT_FALSE(b2);
    EXPECT_FALSE(b3);
    EXPECT_TRUE(b4);
}
