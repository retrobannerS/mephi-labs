#include "Collections/GVector.hpp"
#include "gtest/gtest.h"
#include <stdexcept>

using namespace lab3;
using namespace std;

TEST(GVector, Constructor) {
    //arrange&act
    GVector<int> vector(5);
    //assert
    EXPECT_EQ(vector.dim(), 5);
    EXPECT_EQ(vector[0], 0);
    EXPECT_EQ(vector[1], 0);
    EXPECT_EQ(vector[2], 0);
    EXPECT_EQ(vector[3], 0);
    EXPECT_EQ(vector[4], 0);
}

TEST(GVector,ConstructorWithItem) {
    //arrange&act
    GVector<int> vector(5, 1);
    //assert
    EXPECT_EQ(vector.dim(), 5);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 1);
    EXPECT_EQ(vector[2], 1);
    EXPECT_EQ(vector[3], 1);
    EXPECT_EQ(vector[4], 1);
}

TEST(GVector, ConstructorWithItems) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    //act
    GVector<int> vector(5, items);
    //assert
    EXPECT_EQ(vector.dim(), 5);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);
    EXPECT_EQ(vector[3], 4);
    EXPECT_EQ(vector[4], 5);
}

TEST(GVector, ConstructorWithArray) {
    //arrange
    DynamicArray<int> array(5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i + 1;
    }
    //act
    GVector<int> vector(array);
    //assert
    EXPECT_EQ(vector.dim(), 5);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);
    EXPECT_EQ(vector[3], 4);
    EXPECT_EQ(vector[4], 5);
}

TEST(GVector, ConstructorWithList) {
    //arrange
    LinkedList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.PushBack(i + 1);
    }
    //act
    GVector<int> vector(list);
    //assert
    EXPECT_EQ(vector.dim(), 5);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);
    EXPECT_EQ(vector[3], 4);
    EXPECT_EQ(vector[4], 5);
}

TEST(GVector, ConstructorWithSequence) {
    //arrange
    DynamicArray<int> array(5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i + 1;
    }
    Sequence<int> *sequence = new ArraySequence<int>(array);
    //act
    GVector<int> vector(sequence);
    //assert
    EXPECT_EQ(vector.dim(), 5);
    EXPECT_EQ(vector[0], 1);
    EXPECT_EQ(vector[1], 2);
    EXPECT_EQ(vector[2], 3);
    EXPECT_EQ(vector[3], 4);
    EXPECT_EQ(vector[4], 5);
    delete sequence;
}

TEST(GVector, CopyConstructor) {
    //arrange
    DynamicArray<int> array(5);
    for (int i = 0; i < 5; ++i) {
        array[i] = i + 1;
    }
    GVector<int> vector(array);
    //act
    GVector<int> vector2(vector);
    GVector<int> vector3 = vector;
    //assert
    EXPECT_EQ(vector2.dim(), 5);
    EXPECT_EQ(vector2[0], 1);
    EXPECT_EQ(vector2[1], 2);
    EXPECT_EQ(vector2[2], 3);
    EXPECT_EQ(vector2[3], 4);
    EXPECT_EQ(vector2[4], 5);
    EXPECT_EQ(vector3.dim(), 5);
    EXPECT_EQ(vector3[0], 1);
    EXPECT_EQ(vector3[1], 2);
    EXPECT_EQ(vector3[2], 3);
    EXPECT_EQ(vector3[3], 4);
    EXPECT_EQ(vector3[4], 5);
}

TEST(GVector, OperatorSquareBrackets) {
    //arrange
    GVector<int> vector(5);
    //act&assert
    for(int i = 0; i < 5; ++i) {
        EXPECT_EQ(vector[i], 0);
        vector[i] = i + 1;
        EXPECT_EQ(vector[i], i + 1);
    }
    EXPECT_THROW(vector[-1], out_of_range);
    EXPECT_THROW(vector[5], out_of_range);
}

TEST(GVector, Get) {
    //arrange
    GVector<int> vector(5);
    //act&assert
    for(int i = 0; i < 5; ++i) {
        EXPECT_EQ(vector.Get(i), 0);
        vector[i] = i + 1;
        EXPECT_EQ(vector.Get(i), i + 1);
    }
    EXPECT_THROW(vector.Get(-1), out_of_range);
    EXPECT_THROW(vector.Get(5), out_of_range);
}

TEST(GVector, OperatorEqual) {
    //arrange
    GVector<int> vector(5, 10);
    GVector<int> vector2(1);
    //act
    vector2 = vector;
    //assert
    EXPECT_EQ(vector2.dim(), 5);
    EXPECT_EQ(vector2[0], 10);
}

TEST(GVector, OperatorPlus) {
    //arrange
    int items1[] = {1, 2, 3, 4, 5};
    int items2[] = {5, 4, 3, 2, 1};
    GVector<int> vector1(5, items1);
    GVector<int> vector2(5, items2);
    //act
    GVector<int> vector3 = vector1 + vector2;
    GVector<int> vector4 = vector1 + vector2 + vector3;
    //assert
    EXPECT_EQ(vector3.dim(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(vector3[i], 6);
    }
    EXPECT_EQ(vector4.dim(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(vector4[i], 12);
    }
}

TEST(GVector, OperatorMinus) {
    //arrange
    int items1[] = {1, 2, 3, 4, 5};
    int items2[] = {5, 6, 7, 8, 9};
    GVector<int> vector1(5, items1);
    GVector<int> vector2(5, items2);
    //act
    GVector<int> vector3 = vector1 - vector2;
    GVector<int> vector4 = vector1 - vector2 - vector3;
    //assert
    EXPECT_EQ(vector3.dim(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(vector3[i], -4);
    }
    EXPECT_EQ(vector4.dim(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(vector4[i], 0);
    }
}

TEST(GVector, OperatorScalarMultiply) {
    //arrange
    int items1[] = {1, 2, 3, 4, 5};
    int items2[] = {5, 4, 3, 2, 1};
    GVector<int> vector1(5, items1);
    GVector<int> vector2(5, items2);
    //act
    int result = vector1 * vector2;
    int result2 = vector1 * vector1;
    //assert
    EXPECT_EQ(result, 35);
    EXPECT_EQ(result2, vector1.module() * vector1.module());
}

TEST(GVector, OperatorMultiply) {
    //arrange
    int items1[] = {1, 2, 3, 4, 5};
    GVector<int> vector1(5, items1);
    //act
    GVector<int> vector2 = vector1 * 2;
    GVector<int> vector3 = 2 * vector1;
    //assert
    EXPECT_EQ(vector2.dim(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(vector2[i], 2 * (i + 1));
    }
    EXPECT_EQ(vector3.dim(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(vector3[i], 2 * (i + 1));
    }
}

TEST(GVector, Module) {
    //arrange
    int items1[] = { 3, 4};
    GVector<int> vector1(2, items1);
    GVector<int> vector2(2);
    GVector<int> vector3(0);
    //act
    double result1 = vector1.module();
    double result2 = vector2.module();
    double result3 = vector3.module();
    //assert
    EXPECT_EQ(result1, 5);
    EXPECT_EQ(result2, 0);
    EXPECT_EQ(result3, 0);
}

TEST(GVector, zero) {
    //arrange
    int items1[] = { 3, 4};
    //act
    GVector<int> vector1(2, items1);
    GVector<int> vector2(2);
    GVector<int> vector3(0);
    //assert
    EXPECT_FALSE(vector1.zero());
    EXPECT_TRUE(vector2.zero());
    EXPECT_TRUE(vector3.zero());
}

TEST(GVector, clear) {
    //arrange
    int items1[] = { 3, 4};
    //act
    GVector<int> vector1(2, items1);
    vector1.clear();
    //assert
    EXPECT_EQ(vector1.dim(), 2);
    EXPECT_TRUE(vector1.zero());
}

TEST(GVector, Iterators) {
    //arrange
    GVector<int> vector(6);
    //act&assert
    for(auto x : vector) {
        EXPECT_EQ(x, 0);
    }
}






