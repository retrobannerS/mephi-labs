#include "Collections/Matrixes/SqMatrix.hpp"
#include "gtest/gtest.h"
#include <stdexcept>

using namespace lab3;
using namespace std;

TEST(SqMatrix, Constructor) {
    //arrange&act
    SqMatrix<int> matrix(5);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(matrix.get(i, j), 0);
    }
}

TEST(SqMatrix, ConstructorWithItem) {
    //arrange&act
    SqMatrix<int> matrix(5, 1);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(matrix.get(i, j), 1);
    }
}

TEST(SqMatrix, CopyConstructor) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    //act
    SqMatrix<int> matrix2(matrix);
    SqMatrix<int> matrix3 = matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(matrix2.get(i, j), 1);
    }
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(matrix3.get(i, j), 1);
    }
}

TEST(SqMatrix, makeZero) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    //act
    matrix.makeZero();
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(matrix.get(i, j), 0);
    }
}

TEST(SqMatrix, get) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            EXPECT_EQ(matrix.get(i, j), 0);
            matrix.set(i, j, i + j);
            EXPECT_EQ(matrix.get(i, j), i + j);
        }
    }
}

TEST(SqMatrix, WrongGet) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    EXPECT_THROW(matrix.get(5, 0), out_of_range);
    EXPECT_THROW(matrix.get(0, 5), out_of_range);
    EXPECT_THROW(matrix.get(5, 5), out_of_range);
    EXPECT_THROW(matrix.get(-1, 0), out_of_range);
    EXPECT_THROW(matrix.get(0, -1), out_of_range);
}

TEST(SqMatrix, getRow) {
    //arrange
    SqMatrix<int> matrix(5);
    matrix.makeOne();

    //act
    Sequence<int> *row0 = matrix.getRow(0);
    Sequence<int> *row1 = matrix.getRow(1);
    Sequence<int> *row2 = matrix.getRow(2);
    Sequence<int> *row3 = matrix.getRow(3);
    Sequence<int> *row4 = matrix.getRow(4);

    //assert
    EXPECT_EQ(row0->GetSize(), 5);
    EXPECT_EQ(row1->GetSize(), 5);
    EXPECT_EQ(row2->GetSize(), 5);
    EXPECT_EQ(row3->GetSize(), 5);
    EXPECT_EQ(row4->GetSize(), 5);
    EXPECT_EQ(row0->Get(0), 1);
    EXPECT_EQ(row0->Get(1), 0);
    EXPECT_EQ(row0->Get(2), 0);
    EXPECT_EQ(row0->Get(3), 0);
    EXPECT_EQ(row0->Get(4), 0);
    EXPECT_EQ(row1->Get(0), 0);
    EXPECT_EQ(row1->Get(1), 1);
    EXPECT_EQ(row1->Get(2), 0);
    EXPECT_EQ(row1->Get(3), 0);
    EXPECT_EQ(row1->Get(4), 0);
    EXPECT_EQ(row2->Get(0), 0);
    EXPECT_EQ(row2->Get(1), 0);
    EXPECT_EQ(row2->Get(2), 1);
    EXPECT_EQ(row2->Get(3), 0);
    EXPECT_EQ(row2->Get(4), 0);
    EXPECT_EQ(row3->Get(0), 0);
    EXPECT_EQ(row3->Get(1), 0);
    EXPECT_EQ(row3->Get(2), 0);
    EXPECT_EQ(row3->Get(3), 1);
    EXPECT_EQ(row3->Get(4), 0);
    EXPECT_EQ(row4->Get(0), 0);
    EXPECT_EQ(row4->Get(1), 0);
    EXPECT_EQ(row4->Get(2), 0);
    EXPECT_EQ(row4->Get(3), 0);
    EXPECT_EQ(row4->Get(4), 1);
    delete row0;
    delete row1;
    delete row2;
    delete row3;
    delete row4;
}

TEST(SqMatrix, WrongGetRow) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    EXPECT_THROW(matrix.getRow(5), out_of_range);
    EXPECT_THROW(matrix.getRow(-1), out_of_range);
}

TEST(SqMatrix, getCol) {
    //arrange
    SqMatrix<int> matrix(5);
    matrix.makeOne();

    //act
    Sequence<int> *col0 = matrix.getCol(0);
    Sequence<int> *col1 = matrix.getCol(1);
    Sequence<int> *col2 = matrix.getCol(2);
    Sequence<int> *col3 = matrix.getCol(3);
    Sequence<int> *col4 = matrix.getCol(4);

    //assert
    EXPECT_EQ(col0->GetSize(), 5);
    EXPECT_EQ(col1->GetSize(), 5);
    EXPECT_EQ(col2->GetSize(), 5);
    EXPECT_EQ(col3->GetSize(), 5);
    EXPECT_EQ(col4->GetSize(), 5);
    EXPECT_EQ(col0->Get(0), 1);
    EXPECT_EQ(col0->Get(1), 0);
    EXPECT_EQ(col0->Get(2), 0);
    EXPECT_EQ(col0->Get(3), 0);
    EXPECT_EQ(col0->Get(4), 0);
    EXPECT_EQ(col1->Get(0), 0);
    EXPECT_EQ(col1->Get(1), 1);
    EXPECT_EQ(col1->Get(2), 0);
    EXPECT_EQ(col1->Get(3), 0);
    EXPECT_EQ(col1->Get(4), 0);
    EXPECT_EQ(col2->Get(0), 0);
    EXPECT_EQ(col2->Get(1), 0);
    EXPECT_EQ(col2->Get(2), 1);
    EXPECT_EQ(col2->Get(3), 0);
    EXPECT_EQ(col2->Get(4), 0);
    EXPECT_EQ(col3->Get(0), 0);
    EXPECT_EQ(col3->Get(1), 0);
    EXPECT_EQ(col3->Get(2), 0);
    EXPECT_EQ(col3->Get(3), 1);
    EXPECT_EQ(col3->Get(4), 0);
    EXPECT_EQ(col4->Get(0), 0);
    EXPECT_EQ(col4->Get(1), 0);
    EXPECT_EQ(col4->Get(2), 0);
    EXPECT_EQ(col4->Get(3), 0);
    EXPECT_EQ(col4->Get(4), 1);
    delete col0;
    delete col1;
    delete col2;
    delete col3;
    delete col4;
}

TEST(SqMatrix, set) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    for (int i = 0; i < 5; ++i) {
        for (int j = i; j < 5; ++j) {
            matrix.set(i, j, i + j);
            EXPECT_EQ(matrix.get(i, j), i + j);
        }
    }
}

TEST(SqMatrix, WrongSet) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    EXPECT_THROW(matrix.set(5, 0, 0), out_of_range);
    EXPECT_THROW(matrix.set(0, 5, 0), out_of_range);
    EXPECT_THROW(matrix.set(5, 5, 0), out_of_range);
    EXPECT_THROW(matrix.set(-1, 0, 0), out_of_range);
    EXPECT_THROW(matrix.set(0, -1, 0), out_of_range);
}

TEST(SqMatrix, setRow) {
    //arrange
    int row1[4] = {1, 2, 3, 4};
    int row2[4] = {5, 6, 7, 8};
    int row3[4] = {9, 10, 11, 12};
    int row4[4] = {13, 14, 15, 16};
    ArraySequence<int> row1_(4, row1);
    ArraySequence<int> row2_(4, row2);
    ArraySequence<int> row3_(4, row3);
    ArraySequence<int> row4_(4, row4);
    SqMatrix<int> matrix(4);
    matrix.setRow(0, row1_);
    matrix.setRow(1, row2_);
    matrix.setRow(2, row3_);
    matrix.setRow(3, row4_);

    //act&assert
    for(int i = 0; i != 4; ++i) {
        EXPECT_EQ(matrix.get(0, i), row1[i]);
        EXPECT_EQ(matrix.get(1, i), row2[i]);
        EXPECT_EQ(matrix.get(2, i), row3[i]);
        EXPECT_EQ(matrix.get(3, i), row4[i]);
    }
}

TEST(SqMatrix, WrongSetRow) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    EXPECT_THROW(matrix.setRow(5, ArraySequence<int>(5)), out_of_range);
    EXPECT_THROW(matrix.setRow(-1, ArraySequence<int>(5)), out_of_range);
}

TEST(SqMatrix, setCol) {
    //arrange
    int col1[4] = {1, 2, 3, 4};
    int col2[4] = {5, 6, 7, 8};
    int col3[4] = {9, 10, 11, 12};
    int col4[4] = {13, 14, 15, 16};
    ArraySequence<int> col1_(4, col1);
    ArraySequence<int> col2_(4, col2);
    ArraySequence<int> col3_(4, col3);
    ArraySequence<int> col4_(4, col4);
    SqMatrix<int> matrix(4);
    matrix.setCol(0, col1_);
    matrix.setCol(1, col2_);
    matrix.setCol(2, col3_);
    matrix.setCol(3, col4_);

    //act&assert
    for(int i = 0; i != 4; ++i) {
        EXPECT_EQ(matrix.get(i, 0), col1[i]);
        EXPECT_EQ(matrix.get(i, 1), col2[i]);
        EXPECT_EQ(matrix.get(i, 2), col3[i]);
        EXPECT_EQ(matrix.get(i, 3), col4[i]);
    }
}

TEST(SqMatrix, WrongSetCol) {
    //arrange
    SqMatrix<int> matrix(5);
    //act&assert
    EXPECT_THROW(matrix.setCol(5, ArraySequence<int>(5)), out_of_range);
    EXPECT_THROW(matrix.setCol(-1, ArraySequence<int>(5)), out_of_range);
}

TEST(SqMatrix, OperatorBrackets) {
    //arrange
    SqMatrix<int> matrix(5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            matrix.set(i, j, i + j);
    }

    //act&assert
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix(i, j), i + j);
    }
}

TEST(SqMatrix, operatorPlus) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    SqMatrix<int> matrix2(5, 2);
    //act
    SqMatrix<int> matrix3 = matrix + matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix3.get(i, j), 3);
    }
}

TEST(SqMatrix, operatorPlusWrongDim) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    SqMatrix<int> matrix2(6, 2);
    //act&assert
    EXPECT_THROW(matrix + matrix2, invalid_argument);
}

TEST(SqMatrix, operatorMinus) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    SqMatrix<int> matrix2(5, 2);
    //act
    SqMatrix<int> matrix3 = matrix2 - matrix;
    //assert
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix3.get(i, j), 1);
    }
}

TEST(SqMatrix, operatorMinusWrongDim) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    SqMatrix<int> matrix2(6, 2);
    //act&assert
    EXPECT_THROW(matrix2 - matrix, invalid_argument);
}

TEST(SqMatrix, operatorMultiply) {
    //arrange
    int col1[] = {5, 4, 8};
    int col2[] = {1, 2, 3};
    int col3[] = {0, 2, 1};
    int col1_[] = {22, 11, 2};
    int col2_[] = {17, 8, 3};
    int col3_[] = {18, 8, 3};
    ArraySequence<int> arr1(3, col1);
    ArraySequence<int> arr2(3, col2);
    ArraySequence<int> arr3(3, col3);
    ArraySequence<int> arr1_(3, col1_);
    ArraySequence<int> arr2_(3, col2_);
    ArraySequence<int> arr3_(3, col3_);
    SqMatrix<int> matrix(3);
    SqMatrix<int> matrix2(3);
    matrix.setCol(0, arr1);
    matrix.setCol(1, arr2);
    matrix.setCol(2, arr3);
    matrix2.setCol(0, arr1_);
    matrix2.setCol(1, arr2_);
    matrix2.setCol(2, arr3_);
    //act
    SqMatrix<int> matrix3 = matrix * matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 3);
    EXPECT_EQ(matrix3.get(0, 0), 121);
    EXPECT_EQ(matrix3.get(0, 1), 93);
    EXPECT_EQ(matrix3.get(0, 2), 98);
    EXPECT_EQ(matrix3.get(1, 0), 114);
    EXPECT_EQ(matrix3.get(1, 1), 90);
    EXPECT_EQ(matrix3.get(1, 2), 94);
    EXPECT_EQ(matrix3.get(2, 0), 211);
    EXPECT_EQ(matrix3.get(2, 1), 163);
    EXPECT_EQ(matrix3.get(2, 2), 171);
}

TEST(SqMatrix, operatorMultiplyWrongDim) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    SqMatrix<int> matrix2(6, 2);
    //act&assert
    EXPECT_THROW(matrix * matrix2, invalid_argument);
}

TEST(SqMatrix, operatorMultScalar) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    //act
    SqMatrix<int> matrix2 = matrix * 2;
    SqMatrix<int> matrix3 = 3 * matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix2.get(i, j), 2);
            EXPECT_EQ(matrix3.get(i, i), 3);
    }
}

TEST(SqMatrix, operatorEqual) {
    //arrange
    SqMatrix<int> matrix(5, 1);
    SqMatrix<int> matrix2(7, 22);
    //act
    matrix2 = matrix;

    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix2.get(i, j), 1);
    }
}

TEST(SqMatrix, det) {
    //arrange
    int col1[] = {5, 4, 8};
    int col2[] = {1, 2, 3};
    int col3[] = {0, 2, 1};
    ArraySequence<int> arr1(3, col1);
    ArraySequence<int> arr2(3, col2);
    ArraySequence<int> arr3(3, col3);
    SqMatrix<int> matrix(3);
    matrix.setCol(0, arr1);
    matrix.setCol(1, arr2);
    matrix.setCol(2, arr3);
    SqMatrix<int> matrix2(3);
    SqMatrix<int> matrix3(5, 1);
    //act
    int det = matrix.det();
    int det2 = matrix2.det();
    int det3 = matrix3.det();
    //assert
    EXPECT_EQ(det, -8);
    EXPECT_EQ(det2, 0);
    EXPECT_EQ(matrix3.det(), 0);
}

TEST(SqMatrix, transpose) {
    //arrange
    int row1[] = {5, 4, 8};
    int row2[] = {1, 2, 3};
    int row3[] = {0, 2, 1};
    ArraySequence<int> arr1(3, row1);
    ArraySequence<int> arr2(3, row2);
    ArraySequence<int> arr3(3, row3);
    SqMatrix<int> matrix(3);
    matrix.setRow(0, arr1);
    matrix.setRow(1, arr2);
    matrix.setRow(2, arr3);
    SqMatrix<int> matrix2(3);
    matrix2.makeOne();
    //act
    SqMatrix<int> matrix3 = matrix.transpose();
    SqMatrix<int> matrix4 = matrix2.transpose();
    //assert
    EXPECT_EQ(matrix3.dim(), 3);
    EXPECT_EQ(matrix3.get(0, 0), 5);
    EXPECT_EQ(matrix3.get(0, 1), 1);
    EXPECT_EQ(matrix3.get(0, 2), 0);
    EXPECT_EQ(matrix3.get(1, 0), 4);
    EXPECT_EQ(matrix3.get(1, 1), 2);
    EXPECT_EQ(matrix3.get(1, 2), 2);
    EXPECT_EQ(matrix3.get(2, 0), 8);
    EXPECT_EQ(matrix3.get(2, 1), 3);
    EXPECT_EQ(matrix3.get(2, 2), 1);
    EXPECT_EQ(matrix4.dim(), 3);
    EXPECT_EQ(matrix4.get(0, 0), 1);
    EXPECT_EQ(matrix4.get(0, 1), 0);
    EXPECT_EQ(matrix4.get(0, 2), 0);
    EXPECT_EQ(matrix4.get(1, 0), 0);
    EXPECT_EQ(matrix4.get(1, 1), 1);
    EXPECT_EQ(matrix4.get(1, 2), 0);
    EXPECT_EQ(matrix4.get(2, 0), 0);
    EXPECT_EQ(matrix4.get(2, 1), 0);
    EXPECT_EQ(matrix4.get(2, 2), 1);
}

TEST(SqMatrix, trace) {
    //assert
    int row1[] = {5, 4, 8};
    int row2[] = {1, 2, 3};
    int row3[] = {0, 2, 1};
    ArraySequence<int> arr1(3, row1);
    ArraySequence<int> arr2(3, row2);
    ArraySequence<int> arr3(3, row3);
    SqMatrix<int> matrix(3);
    matrix.setRow(0, arr1);
    matrix.setRow(1, arr2);
    matrix.setRow(2, arr3);
    SqMatrix<int> matrix2(3);
    matrix2.makeOne();
    SqMatrix<int> matrix3(5, 0);

    //act
    int trace = matrix.trace();
    int trace2 = matrix2.trace();
    int trace3 = matrix3.trace();

    //assert
    EXPECT_EQ(trace, 8);
    EXPECT_EQ(trace2, 3);
    EXPECT_EQ(trace3, 0);
}

TEST(SqMatrix, inverse) {
    //arrange
    double row1[] = {5, 4, 8};
    double row2[] = {1, 2, 3};
    double row3[] = {0, 2, 1};
    ArraySequence<double> arr1(3, row1);
    ArraySequence<double> arr2(3, row2);
    ArraySequence<double> arr3(3, row3);
    SqMatrix<double> matrix(3);
    matrix.setRow(0, arr1);
    matrix.setRow(1, arr2);
    matrix.setRow(2, arr3);
    SqMatrix<double> matrix2(3);
    matrix2.makeOne();
    SqMatrix<double> matrix3(5, 0);

    //act
    SqMatrix<double> matrix4 = matrix.inverse();
    SqMatrix<double> matrix5 = matrix2.inverse();

    //assert
    EXPECT_EQ(matrix4.dim(), 3);
    EXPECT_EQ(matrix4.get(0, 0), 0.5);
    EXPECT_EQ(matrix4.get(0, 1), -1.5);
    EXPECT_EQ(matrix4.get(0, 2), 0.5);
    EXPECT_EQ(matrix4.get(1, 0), 0.125);
    EXPECT_EQ(matrix4.get(1, 1), -0.625);
    EXPECT_EQ(matrix4.get(1, 2), 0.875);
    EXPECT_EQ(matrix4.get(2, 0), -0.25);
    EXPECT_EQ(matrix4.get(2, 1), 1.25);
    EXPECT_EQ(matrix4.get(2, 2), -0.75);
    EXPECT_THROW(matrix3.inverse(), std::invalid_argument);
    EXPECT_EQ(matrix5.dim(), 3);
    EXPECT_EQ(matrix5.get(0, 0), 1);
    EXPECT_EQ(matrix5.get(0, 1), 0);
    EXPECT_EQ(matrix5.get(0, 2), 0);
    EXPECT_EQ(matrix5.get(1, 0), 0);
    EXPECT_EQ(matrix5.get(1, 1), 1);
    EXPECT_EQ(matrix5.get(1, 2), 0);
    EXPECT_EQ(matrix5.get(2, 0), 0);
    EXPECT_EQ(matrix5.get(2, 1), 0);
    EXPECT_EQ(matrix5.get(2, 2), 1);
}
