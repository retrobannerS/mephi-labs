#include <stdexcept>
#include "gtest/gtest.h"
#include "Collections/Matrixes/RectangularMatrix.hpp"

using namespace lab2;
using namespace lab3;
using namespace std;

TEST(RectangularMatrix, ConstructorWithDim) {
    //arrange&act
    RectangularMatrix<int> matrix(5, 7);
    //assert
    EXPECT_EQ(matrix.rows(), 5);
    EXPECT_EQ(matrix.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j)
            EXPECT_EQ(matrix(i, j), 0);
    EXPECT_THROW(RectangularMatrix<int> matrix2(-1, 5), invalid_argument);
    EXPECT_THROW(RectangularMatrix<int> matrix2(5, -1), invalid_argument);
    EXPECT_THROW(RectangularMatrix<int> matrix2(5, 0), invalid_argument);
    EXPECT_THROW(RectangularMatrix<int> matrix2(0, 5), invalid_argument);
}

TEST(RectangularMatrix, ConstructorWithItem) {
    //arrange&act
    RectangularMatrix<int> matrix(5, 7, 1);
    //assert
    EXPECT_EQ(matrix.rows(), 5);
    EXPECT_EQ(matrix.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j)
            EXPECT_EQ(matrix(i, j), 1);
    EXPECT_THROW(RectangularMatrix<int> matrix2(-1, 5, 1), invalid_argument);
    EXPECT_THROW(RectangularMatrix<int> matrix2(5, -1, 1), invalid_argument);
    EXPECT_THROW(RectangularMatrix<int> matrix2(5, 0, 1), invalid_argument);
    EXPECT_THROW(RectangularMatrix<int> matrix2(0, 5, 1), invalid_argument);
}

TEST(RectangularMatrix, CopyConstructor) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    //act
    RectangularMatrix<int> matrix2(matrix);
    RectangularMatrix<int> matrix3 = matrix;
    //assert
    EXPECT_EQ(matrix2.rows(), 5);
    EXPECT_EQ(matrix3.rows(), 5);
    EXPECT_EQ(matrix2.cols(), 7);
    EXPECT_EQ(matrix3.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j) {
            EXPECT_EQ(matrix2(i, j), 1);
            EXPECT_EQ(matrix3(i, j), 1);
        }
}

TEST(RectangularMatrix, Destructor) {
    //arrange&act
    auto *matrix = new RectangularMatrix<int>(5, 7, 1);
    delete matrix;
    //assert
    EXPECT_TRUE(true);
}

TEST(RectangularMatrix, operatorAssign) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    //act
    RectangularMatrix<int> matrix2(5, 7, 2);
    matrix2 = matrix;
    //assert
    EXPECT_EQ(matrix2.rows(), 5);
    EXPECT_EQ(matrix2.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j)
            EXPECT_EQ(matrix2(i, j), 1);
}

TEST(RectangularMatrix, rows) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(0, 0, 1);
    //act&assert
    EXPECT_EQ(matrix.rows(), 5);
    EXPECT_EQ(matrix2.rows(), 0);
}

TEST(RectangularMatrix, cols) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(0, 0, 1);
    //act&assert
    EXPECT_EQ(matrix.cols(), 7);
    EXPECT_EQ(matrix2.cols(), 0);
}

TEST(RectangularMatrix, shape) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(0, 0, 1);
    //act&assert
    EXPECT_EQ(matrix.shape(), make_pair(5, 7));
    EXPECT_EQ(matrix2.shape(), make_pair(0, 0));
}

TEST(RectangularMatrix, operatorParentheses) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    //act&assert
    EXPECT_EQ(matrix(0, 0), 1);
    EXPECT_EQ(matrix(4, 6), 1);
    EXPECT_THROW(matrix(5, 0), out_of_range);
    EXPECT_THROW(matrix(0, 7), out_of_range);
    EXPECT_THROW(matrix(5, 7), out_of_range);
    EXPECT_THROW(matrix(-1, 0), out_of_range);
    EXPECT_THROW(matrix(0, -1), out_of_range);
    EXPECT_THROW(matrix(-1, -1), out_of_range);
}

TEST(RectangularMatrix, get) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    //act&assert
    EXPECT_EQ(matrix.get(0, 0), 1);
    EXPECT_EQ(matrix.get(4, 6), 1);
    EXPECT_THROW(matrix.get(5, 0), out_of_range);
    EXPECT_THROW(matrix.get(0, 7), out_of_range);
    EXPECT_THROW(matrix.get(5, 7), out_of_range);
    EXPECT_THROW(matrix.get(-1, 0), out_of_range);
    EXPECT_THROW(matrix.get(0, -1), out_of_range);
    EXPECT_THROW(matrix.get(-1, -1), out_of_range);
}

TEST(RectangularMatrix, set) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    //act&assert
    EXPECT_EQ(matrix.get(0, 0), 1);
    matrix.set(0, 0, 2);
    EXPECT_EQ(matrix.get(0, 0), 2);
    EXPECT_EQ(matrix.get(4, 6), 1);
    matrix.set(4, 6, 2);
    EXPECT_EQ(matrix.get(4, 6), 2);
    EXPECT_THROW(matrix.set(5, 0, 2), out_of_range);
    EXPECT_THROW(matrix.set(0, 7, 2), out_of_range);
    EXPECT_THROW(matrix.set(5, 7, 2), out_of_range);
    EXPECT_THROW(matrix.set(-1, 0, 2), out_of_range);
    EXPECT_THROW(matrix.set(0, -1, 2), out_of_range);
    EXPECT_THROW(matrix.set(-1, -1, 2), out_of_range);
}

TEST(RectangularMatrix, setRow) {
    //arrange
    ArraySequence<int> row(7);
    for(int i = 0; i < 7; ++i)
        row.Set(i, i);
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(2, 2, 1);
    //act
    matrix.setRow(0, row);

    //assert
    for(int i = 0; i < 7; ++i)
        EXPECT_EQ(matrix.get(0, i), i);
    for(int i = 1; i < 5; ++i)
        for(int j = 0; j < 7; ++j)
            EXPECT_EQ(matrix.get(i, j), 1);
    EXPECT_THROW(matrix.setRow(5, row), out_of_range);
    EXPECT_THROW(matrix2.setRow(1, row), invalid_argument);
}

TEST(RectangularMatrix, setCol) {
    //arrange
    ArraySequence<int> col(5);
    for(int i = 0; i < 5; ++i)
        col.Set(i, i);
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(2, 2, 1);
    //act
    matrix.setCol(0, col);

    //assert
    for(int i = 0; i < 5; ++i)
        EXPECT_EQ(matrix.get(i, 0), i);
    for(int i = 0; i < 5; ++i)
        for(int j = 1; j < 7; ++j)
            EXPECT_EQ(matrix.get(i, j), 1);
    EXPECT_THROW(matrix.setCol(7, col), out_of_range);
    EXPECT_THROW(matrix2.setCol(1, col), invalid_argument);
}

TEST(RectangularMatrix, operatorPlus) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(5, 7, 2);
    RectangularMatrix<int> matrix3(5, 6, 3);
    RectangularMatrix<int> matrix4(6, 7, 4);

    //act
    RectangularMatrix<int> matrix5 = matrix + matrix2;

    //assert
    EXPECT_EQ(matrix5.rows(), 5);
    EXPECT_EQ(matrix5.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j)
            EXPECT_EQ(matrix5.get(i, j), 3);
    EXPECT_THROW(matrix + matrix3, invalid_argument);
    EXPECT_THROW(matrix + matrix4, invalid_argument);
}

TEST(RectangularMatrix, EmptyOperatorPlus) {
    //arrange
    RectangularMatrix<int> matrix(0, 0, 1);
    RectangularMatrix<int> matrix2(0, 0, 2);
    RectangularMatrix<int> matrix3(0, 0, 3);
    RectangularMatrix<int> matrix4(0, 0, 4);

    //act
    RectangularMatrix<int> matrix5 = matrix + matrix2;

    //assert
    EXPECT_EQ(matrix5.rows(), 0);
    EXPECT_EQ(matrix5.cols(), 0);
}

TEST(RectangularMatrix, operatorMinus) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);
    RectangularMatrix<int> matrix2(5, 7, 2);
    RectangularMatrix<int> matrix3(5, 6, 3);
    RectangularMatrix<int> matrix4(6, 7, 4);

    //act
    RectangularMatrix<int> matrix5 = matrix - matrix2;

    //assert
    EXPECT_EQ(matrix5.rows(), 5);
    EXPECT_EQ(matrix5.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j)
            EXPECT_EQ(matrix5.get(i, j), -1);
    EXPECT_THROW(matrix - matrix3, invalid_argument);
    EXPECT_THROW(matrix - matrix4, invalid_argument);
}

TEST(RectangularMatrix, EmptyOperatorMinus) {
    //arrange
    RectangularMatrix<int> matrix(0, 0, 1);
    RectangularMatrix<int> matrix2(0, 0, 2);
    RectangularMatrix<int> matrix3(0, 0, 3);
    RectangularMatrix<int> matrix4(0, 0, 4);

    //act
    RectangularMatrix<int> matrix5 = matrix - matrix2;

    //assert
    EXPECT_EQ(matrix5.rows(), 0);
    EXPECT_EQ(matrix5.cols(), 0);
}

TEST(RectangularMatrix, OperatorMult) {
    //arrange
    RectangularMatrix<int> matrix(2, 3, 1);
    RectangularMatrix<int> matrix2(3, 4, 2);
    matrix2(2, 0) = 3;
    matrix2(2, 1) = 4;
    matrix2(2, 2) = 5;
    matrix2(2, 3) = 6;

    //act
    RectangularMatrix<int> matrix3 = matrix * matrix2;

    //assert
    EXPECT_EQ(matrix3.rows(), 2);
    EXPECT_EQ(matrix3.cols(), 4);
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 4; ++j)
            EXPECT_EQ(matrix3.get(i, j), 7 + j);
}

TEST(RectangularMatrix, ScalarMult) {
    //arrange
    RectangularMatrix<int> matrix(5, 7, 1);

    //act
    RectangularMatrix<int> matrix2 = matrix * 2;
    RectangularMatrix<int> matrix3 = 2 * matrix;

    //assert
    EXPECT_EQ(matrix2.rows(), 5);
    EXPECT_EQ(matrix2.cols(), 7);
    EXPECT_EQ(matrix3.rows(), 5);
    EXPECT_EQ(matrix3.cols(), 7);
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 7; ++j) {
            EXPECT_EQ(matrix2.get(i, j), 2);
            EXPECT_EQ(matrix3.get(i, j), 2);
        }
}

TEST(RectangularMatrix, EmptyScalarMult) {
    //arrange
    RectangularMatrix<int> matrix(0, 0, 1);

    //act
    RectangularMatrix<int> matrix2 = matrix * 2;
    RectangularMatrix<int> matrix3 = 2 * matrix;

    //assert
    EXPECT_EQ(matrix2.rows(), 0);
    EXPECT_EQ(matrix2.cols(), 0);
    EXPECT_EQ(matrix3.rows(), 0);
    EXPECT_EQ(matrix3.cols(), 0);
}

TEST(RectangularMatrix, transpose) {
    //arrange
    RectangularMatrix<int> matrix(5, 7);
    for(int i = 0; i != 5; ++i)
        for(int j = 0; j != 7; ++j)
            matrix.set(i, j, i + j);

    //act
    RectangularMatrix<int> matrix2 = matrix.transpose();

    //assert
    EXPECT_EQ(matrix2.rows(), 7);
    EXPECT_EQ(matrix2.cols(), 5);
    for(int i = 0; i < 7; ++i)
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(matrix2.get(i, j), i + j);
}

TEST(RectangularMatrix, EmptyTranspose) {
    //arrange
    RectangularMatrix<int> matrix(0, 0);

    //act
    RectangularMatrix<int> matrix2 = matrix.transpose();

    //assert
    EXPECT_EQ(matrix2.rows(), 0);
    EXPECT_EQ(matrix2.cols(), 0);
}

TEST(RectangularMatrix, getsubmatrix) {
    //arrange
    RectangularMatrix<int> matrix(5, 7);
    for(int i = 0; i != 5; ++i)
        for(int j = 0; j != 7; ++j)
            matrix.set(i, j, i + j);

    //act
    RectangularMatrix<int> matrix2 = matrix.submatrix(1, 2);

    //assert
    EXPECT_EQ(matrix2.rows(), 4);
    EXPECT_EQ(matrix2.cols(), 6);
    EXPECT_EQ(matrix2.get(0, 0), 0);
    EXPECT_EQ(matrix2.get(0, 1), 1);
    EXPECT_EQ(matrix2.get(0, 2), 3);
    EXPECT_EQ(matrix2.get(0, 3), 4);
    EXPECT_EQ(matrix2.get(0, 4), 5);
    EXPECT_EQ(matrix2.get(0, 5), 6);
    EXPECT_EQ(matrix2.get(1, 0), 2);
    EXPECT_EQ(matrix2.get(1, 1), 3);
    EXPECT_EQ(matrix2.get(1, 2), 5);
    EXPECT_EQ(matrix2.get(1, 3), 6);
    EXPECT_EQ(matrix2.get(1, 4), 7);
    EXPECT_EQ(matrix2.get(1, 5), 8);
    EXPECT_EQ(matrix2.get(2, 0), 3);
    EXPECT_EQ(matrix2.get(2, 1), 4);
    EXPECT_EQ(matrix2.get(2, 2), 6);
    EXPECT_EQ(matrix2.get(2, 3), 7);
    EXPECT_EQ(matrix2.get(2, 4), 8);
    EXPECT_EQ(matrix2.get(2, 5), 9);
    EXPECT_EQ(matrix2.get(3, 0), 4);
    EXPECT_EQ(matrix2.get(3, 1), 5);
    EXPECT_EQ(matrix2.get(3, 2), 7);
    EXPECT_EQ(matrix2.get(3, 3), 8);
    EXPECT_EQ(matrix2.get(3, 4), 9);
    EXPECT_EQ(matrix2.get(3, 5), 10);
}

TEST(RectangularMatrix, EmptyGetSubmatrix) {
    //arrange
    RectangularMatrix<int> matrix(0, 0);

    //act&assert
    EXPECT_THROW(matrix.submatrix(0, 0), invalid_argument);
}




