#include <stdexcept>
#include "gtest/gtest.h"
#include "Collections/Matrixes/DiagMatrix.hpp"

using namespace lab2;
using namespace lab3;
using namespace std;

TEST(DiagMatrix, ConstructorWithDim) {
    //arrange&act
    DiagMatrix<int> matrix(5);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix(i, i), 0);
}

TEST(DiagMatrix, ConstructorWithItem) {
    //arrange&act
    DiagMatrix<int> matrix(5, 1);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix(i, i), 1);
}

TEST(DiagMatrix, ConstructorWithItems) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    //act
    DiagMatrix<int> matrix(5, items);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix(i, i), i + 1);
}

TEST(DiagMatrix, SequenceConstructor) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    Sequence<int> *array = new ArraySequence<int>(5, items);
    //act
    DiagMatrix<int> matrix(array);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix(i, i), i + 1);
    delete array;
}

TEST(DiagMatrix, CopyConstructor) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    //act
    DiagMatrix<int> matrix2(matrix);
    DiagMatrix<int> matrix3 = matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        EXPECT_EQ(matrix2(i, i), i + 1);
        EXPECT_EQ(matrix3(i, i), i + 1);
    }
}

TEST(DiagMatrix, Destructor) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    auto *matrix = new DiagMatrix<int>(5, items);
    //act
    delete matrix;
    //assert
    EXPECT_TRUE(true);
}

TEST(DiagMatrix, operatorAssign) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    //act
    DiagMatrix<int> matrix2(5, 2);
    matrix2 = matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix2(i, i), i + 1);
}

TEST(DiagMatrix, dim) {
    //arrange
    DiagMatrix<int> zero(0);
    DiagMatrix<int> matrix(5);
    //act&assert
    EXPECT_EQ(zero.dim(), 0);
    EXPECT_EQ(matrix.dim(), 5);
}

TEST(DiagMatrix, get) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    DiagMatrix<int> zero(0);
    //act&assert
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix.get(i, i), i + 1);
    EXPECT_THROW(zero.get(0, 0), out_of_range);
}

TEST(DiagMatrix, set) {
    //arrange
    DiagMatrix<int> matrix(5);
    DiagMatrix<int> zero(0);
    //act&assert
    for(int i = 0; i < 5; ++i) {
        matrix.set(i, i, i + 1);
        EXPECT_EQ(matrix(i, i), i + 1);
    }
    EXPECT_THROW(zero.set(0, 0, 1), out_of_range);
}

TEST(DiagMatrix, operatorPlus) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    DiagMatrix<int> matrix2(5, 2);
    DiagMatrix<int> matrix3(7, 3);
    //act
    DiagMatrix<int> matrix4 = matrix + matrix2;
    //assert
    EXPECT_EQ(matrix4.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix4(i, i), i + 3);
    EXPECT_THROW(matrix + matrix3, invalid_argument);
}

TEST(DiagMatrix, emptyOperatorPlus) {
    //arrange
    DiagMatrix<int> matrix(0);
    DiagMatrix<int> matrix2(0);
    //act
    DiagMatrix<int> matrix3 = matrix + matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 0);
}

TEST(DiagMatrix, operatorMinus) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    DiagMatrix<int> matrix2(5, 2);
    DiagMatrix<int> matrix3(7, 3);
    //act
    DiagMatrix<int> matrix4 = matrix - matrix2;
    //assert
    EXPECT_EQ(matrix4.dim(), 5);
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix4(i, i), i - 1);
    EXPECT_THROW(matrix - matrix3, invalid_argument);
}

TEST(DiagMatrix, emptyOperatorMinus) {
    //arrange
    DiagMatrix<int> matrix(0);
    DiagMatrix<int> matrix2(0);
    //act
    DiagMatrix<int> matrix3 = matrix - matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 0);
}

TEST(DiagMatrix, scalarMult) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    //act
    DiagMatrix<int> matrix2 = matrix * 2;
    DiagMatrix<int> matrix3 = 2 * matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        EXPECT_EQ(matrix2(i, i), (i + 1) * 2);
        EXPECT_EQ(matrix3(i, i), (i + 1) * 2);
    }
}

TEST(DiagMatrix, trace) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    DiagMatrix<int> matrix2(10);
    DiagMatrix<int> zero(0);
    //act&assert
    EXPECT_EQ(matrix.trace(), 15);
    EXPECT_EQ(matrix2.trace(), 0);
    EXPECT_THROW(zero.trace(), logic_error);
}

TEST(DiagMatrix, det) {
    //arrange
    int items[5] = {1, 2, 3, 4, 5};
    DiagMatrix<int> matrix(5, items);
    DiagMatrix<int> matrix2(10);
    DiagMatrix<int> zero(0);
    //act&assert
    EXPECT_EQ(matrix.det(), 120);
    EXPECT_EQ(matrix2.det(), 0);
    EXPECT_THROW(zero.det(), logic_error);
}