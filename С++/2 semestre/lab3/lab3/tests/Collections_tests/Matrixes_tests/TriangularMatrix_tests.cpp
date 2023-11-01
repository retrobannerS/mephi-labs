#include "gtest/gtest.h"
#include "Collections/Matrixes/TriangularMatrix.hpp"
#include <stdexcept>

using namespace lab3;
using namespace std;

TEST(LowerTriangularMatrix, Constructor) {
    //arrange&act
    LowerTriangularMatrix<int> matrix(5);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix(j, i), 0);
    }
}

TEST(LowerTriangularMatrix, ConstructorWithItem) {
    //arrange&act
    LowerTriangularMatrix<int> matrix(5, 1);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix(j, i), 1);
    }
}

TEST(LowerTriangularMatrix, CopyConstructor) {
    //arrange
    LowerTriangularMatrix<int> matrix(5, 1);
    //act
    LowerTriangularMatrix<int> matrix2(matrix);
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix2(j, i), 1);
    }
}

TEST(LowerTriangularMatrix, Destructor) {
    //arrange&act
    auto *matrix = new LowerTriangularMatrix<int>(5, 1);
    delete matrix;
    //assert
    EXPECT_TRUE(true);
}

TEST(LowerTriangularMatrix, operatorAssign) {
    //arrange
    LowerTriangularMatrix<int> matrix(5, 1);
    //act
    LowerTriangularMatrix<int> matrix2(5, 2);
    matrix2 = matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix2(j, i), 1);
    }
}

TEST(LowerTriangularMatrix, operatorPlus) {
    //arrange
    LowerTriangularMatrix<int> matrix(5, 1);
    LowerTriangularMatrix<int> matrix2(5, 2);
    //act
    LowerTriangularMatrix<int> matrix3 = matrix + matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix3(j, i), 3);
    }
}

TEST(LowerTriangularMatrix, operatorMinus) {
    //arrange
    LowerTriangularMatrix<int> matrix(5, 1);
    LowerTriangularMatrix<int> matrix2(5, 2);
    //act
    LowerTriangularMatrix<int> matrix3 = matrix - matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j)
            EXPECT_EQ(matrix3(j, i), -1);
    }
}

TEST(LowerTriangularMatrix, transpose) {
    //arrange
    LowerTriangularMatrix<int> matrix(5, 1);
    //act
    UpperTriangularMatrix<int> *matrix2 = matrix.transpose();
    //assert
    EXPECT_EQ(matrix2->dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j < 5; ++j) {
            if(i != j) {
                EXPECT_THROW((*matrix2)(j, i), out_of_range);
            }
            EXPECT_EQ((*matrix2)(i, j), 1);
        }
    }
    delete matrix2;
}

TEST(UpperTriangularMatrix, Constructor) {
    //arrange&act
    UpperTriangularMatrix<int> matrix(5);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j)
            EXPECT_EQ(matrix(i, j), 0);
    }
}

TEST(UpperTriangularMatrix, ConstructorWithItem) {
    //arrange&act
    UpperTriangularMatrix<int> matrix(5, 1);
    //assert
    EXPECT_EQ(matrix.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j)
            EXPECT_EQ(matrix(i, j), 1);
    }
}

TEST(UpperTriangularMatrix, CopyConstructor) {
    //arrange
    UpperTriangularMatrix<int> matrix(5, 1);
    //act
    UpperTriangularMatrix<int> matrix2(matrix);
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j)
            EXPECT_EQ(matrix2(i, j), 1);
    }
}

TEST(UpperTriangularMatrix, Destructor) {
    //arrange&act
    auto *matrix = new UpperTriangularMatrix<int>(5, 1);
    delete matrix;
    //assert
    EXPECT_TRUE(true);
}

TEST(UpperTriangularMatrix, operatorAssign) {
    //arrange
    UpperTriangularMatrix<int> matrix(5, 1);
    //act
    UpperTriangularMatrix<int> matrix2(5, 2);
    matrix2 = matrix;
    //assert
    EXPECT_EQ(matrix2.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j)
            EXPECT_EQ(matrix2(i, j), 1);
    }
}

TEST(UpperTriangularMatrix, operatorPlus) {
    //arrange
    UpperTriangularMatrix<int> matrix(5, 1);
    UpperTriangularMatrix<int> matrix2(5, 2);
    //act
    UpperTriangularMatrix<int> matrix3 = matrix + matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j)
            EXPECT_EQ(matrix3(i, j), 3);
    }
}

TEST(UpperTriangularMatrix, operatorMinus) {
    //arrange
    UpperTriangularMatrix<int> matrix(5, 1);
    UpperTriangularMatrix<int> matrix2(5, 2);
    //act
    UpperTriangularMatrix<int> matrix3 = matrix - matrix2;
    //assert
    EXPECT_EQ(matrix3.dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j)
            EXPECT_EQ(matrix3(i, j), -1);
    }
}

TEST(UpperTriangularMatrix, transpose) {
    //arrange
    UpperTriangularMatrix<int> matrix(5, 1);
    //act
    LowerTriangularMatrix<int> *matrix2 = matrix.transpose();
    //assert
    EXPECT_EQ(matrix2->dim(), 5);
    for(int i = 0; i < 5; ++i) {
        for(int j = i; j <= i; ++j) {
            if(i != j) {
                EXPECT_THROW((*matrix2)(i, j), out_of_range);
            }
            EXPECT_EQ((*matrix2)(j, i), 1);
        }
    }
    delete matrix2;
}

TEST(TriangularMatrix, Destructor) {
    //arrange
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    auto *matrix2 = new LowerTriangularMatrix<int>(5, 1);
    auto *matrix3 = new UpperTriangularMatrix<int>(5, 1);
    //act
    delete matrix;
    delete matrix2;
    delete matrix3;
    //assert
    EXPECT_TRUE(true);
}

TEST(TriangularMatrix, dim) {
    //arrange
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    UpperTriangularMatrix<int> matrix2(7, 1);
    LowerTriangularMatrix<int> matrix3(9, 1);
    //act
    int dim = matrix->dim();
    int dim2 = matrix2.dim();
    int dim3 = matrix3.dim();
    //assert
    EXPECT_EQ(dim, 5);
    EXPECT_EQ(dim2, 7);
    EXPECT_EQ(dim3, 9);
    delete matrix;
}

TEST(TriangularMatrix, operatorBrackets) {
    //arrange
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    UpperTriangularMatrix<int> matrix2(7, 1);
    LowerTriangularMatrix<int> matrix3(9, 1);
    //act
    int item = (*matrix)(0, 0);
    int item2 = matrix2(0, 0);
    int item3 = matrix3(0, 0);
    (*matrix)(1, 1) = 2;
    matrix2(1, 1) = 2;
    matrix3(1, 1) = 2;
    //assert
    EXPECT_EQ(item, 1);
    EXPECT_EQ(item2, 1);
    EXPECT_EQ(item3, 1);
    EXPECT_EQ((*matrix)(1, 1), 2);
    EXPECT_EQ(matrix2(1, 1), 2);
    EXPECT_EQ(matrix3(1, 1), 2);
    delete matrix;
}

TEST(TriangularMetrix, Get) {
    //arrange
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    UpperTriangularMatrix<int> matrix2(7, 2);
    LowerTriangularMatrix<int> matrix3(9, 3);
    //act&assert
    for(int i = 0; i != 5; ++i) {
        for(int j = 0; j <= i; ++j) {
            EXPECT_EQ(matrix->get(i, j), 1);
        }
    }

    for(int i = 0; i != 7; ++i) {
        for(int j = i; j != 7; ++j) {
            EXPECT_EQ(matrix2.get(i, j), 2);
        }
    }

    for(int i = 0; i != 9; ++i) {
        for(int j = 0; j <= i; ++j) {
            EXPECT_EQ(matrix3.get(i, j), 3);
        }
    }
    delete matrix;
}

TEST(TriangularMatrix, Set) {
    //arrange
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    UpperTriangularMatrix<int> matrix2(7, 2);
    LowerTriangularMatrix<int> matrix3(9, 3);
    //act&assert
    for (int i = 0; i != 5; ++i) {
        for (int j = 0; j <= i; ++j) {
            matrix->set(i, j, 2);
            EXPECT_EQ(matrix->get(i, j), 2);
        }
    }

    for (int i = 0; i != 7; ++i) {
        for (int j = i; j != 7; ++j) {
            matrix2.set(i, j, 3);
            EXPECT_EQ(matrix2.get(i, j), 3);
        }
    }

    for (int i = 0; i != 9; ++i) {
        for (int j = 0; j <= i; ++j) {
            matrix3.set(i, j, 4);
            EXPECT_EQ(matrix3.get(i, j), 4);
        }
    }
    delete matrix;
}

TEST(TriangularMatrix, trace) {
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    UpperTriangularMatrix<int> matrix2(7, 2);
    LowerTriangularMatrix<int> matrix3(9, 3);
    //act
    int trace = matrix->trace();
    int trace2 = matrix2.trace();
    int trace3 = matrix3.trace();
    //assert
    EXPECT_EQ(trace, 5);
    EXPECT_EQ(trace2, 14);
    EXPECT_EQ(trace3, 27);
    delete matrix;
}

TEST(TriangularMatrix, det) {
    //arrange
    TriangularMatrix<int> *matrix = new LowerTriangularMatrix<int>(5, 1);
    UpperTriangularMatrix<int> matrix2(7, 2);
    LowerTriangularMatrix<int> matrix3(9, 3);
    //act
    int det = matrix->det();
    int det2 = matrix2.det();
    int det3 = matrix3.det();
    //assert
    EXPECT_EQ(det, 1);
    EXPECT_EQ(det2, 128);
    EXPECT_EQ(det3, 19683);
    delete matrix;
}