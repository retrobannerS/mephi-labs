#include "Data_types/mycomplex.h"
#include "Collections/GVector.hpp"
#include "Collections/Matrixes/SqMatrix.hpp"
#include "Collections/PriorityQueue.hpp"
#include "gtest/gtest.h"

using namespace lab3;

TEST(ComplexWithGVector, Set) {
    //arrange
    GVector<complex> vector(5);
    //act
    for(auto &item : vector) {
        item = {1, 1};
    }
    //assert
    EXPECT_EQ(vector[0], complex(1, 1));
    EXPECT_EQ(vector[1], complex(1, 1));
}

TEST(ComplexWithGVector, Operators) {
    //arrange
    GVector<complex> vector(5, {10, 22});
    GVector<complex> vector2(5, {1, 1});
    //act
    GVector<complex> vector3 = vector + vector2;
    GVector<complex> vector4 = vector - vector2;
    complex vector5 = vector * vector2;
    vector2 = vector;
    complex temp = complex();
    for(int i = 0; i != 5; ++i) {
        temp += complex(10, 22) * complex(1, 1);
    }

    //assert
    EXPECT_EQ(vector3[0], complex(11, 23));
    EXPECT_EQ(vector4[0], complex(9, 21));
    EXPECT_EQ(vector5, temp);
}

TEST(ComplexWithSqMatrix, trace) {
    //arrange
    SqMatrix<complex> matrix(5);
    for(int i = 0; i != 5; ++i) {
        matrix(i, i) = {double(10 + i), double(10 - i)};
    }

    //act
    complex trace = matrix.trace();

    //assert
    EXPECT_EQ(trace, complex(60, 40));
}

TEST(ComplexWithSqMatrix, makeOne_and_zero) {
    //arrange
    SqMatrix<complex> matrix(5);
    for(int i = 0; i != 5; ++i) {
        matrix(i, i) = {double(10 + i), double(10 - i)};
    }
    SqMatrix<complex> matrix2 = matrix;

    //act
    matrix.makeOne();
    matrix2.makeZero();

    //assert
    for(int i = 0; i != 5; ++i)
        for(int j = 0; j != 5; ++j) {
            if(i == j) {
                EXPECT_EQ(matrix(i, j), complex(1, 0));
                EXPECT_EQ(matrix2(i, j), complex(0, 0));
            }
            else {
                EXPECT_EQ(matrix(i, j), complex(0, 0));
                EXPECT_EQ(matrix2(i, j), complex(0, 0));
            }
        }
}

TEST(ComplexWithSqMatrix, Operators) {
    //arrange
    SqMatrix<complex> matrix(3);
    SqMatrix<complex> matrix2(3);
    for(int i = 0; i != 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix(i, j) = {double(10 + i), double(10 - i)};
            matrix2(i, j) = {double(10 + i), double(10 - i)};
        }
    }
    SqMatrix<complex> matrix_equal(1);

    //act
    SqMatrix<complex> matrix3 = matrix + matrix2;
    SqMatrix<complex> matrix4 = matrix - matrix2;
    matrix_equal = matrix;

    //assert
    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 3; ++j) {
            EXPECT_EQ(matrix3(i, j), complex(20 + 2 * i, 20 - 2 * i));
            EXPECT_EQ(matrix4(i, j), complex(0, 0));
            EXPECT_EQ(matrix_equal(i, j), complex(10 + i, 10 - i));
        }
}

TEST(ComplexWithSqMatrix, operatorMult) {
    //arrange
    SqMatrix<complex> matrix(2, {1, 1});
    SqMatrix<complex> matrix2(2, {2, 2});
    matrix2(1, 0) = {3, 3};
    matrix2(0, 1) = {4, 4};

    //act
    SqMatrix<complex> matrix3 = matrix * matrix2;

    //assert
    EXPECT_EQ(matrix3(0, 0), complex(0, 10));
    EXPECT_EQ(matrix3(0, 1), complex(0, 12));
    EXPECT_EQ(matrix3(1, 0), complex(0, 10));
    EXPECT_EQ(matrix3(1, 1), complex(0, 12));
}

TEST(ComplexWithSqMatrix, det) {
    //arrange
    SqMatrix<complex> matrix(3);
    matrix(0, 0) = {1, 1};
    matrix(0, 1) = {6, 1};
    matrix(0, 2) = {2, 1};
    matrix(1, 0) = {1, 0};
    matrix(1, 1) = {2, 0};
    matrix(1, 2) = {3, 0};
    matrix(2, 0) = {2, 1};
    matrix(2, 1) = {3, 1};
    matrix(2, 2) = {1, 1};

    //act
    complex det = matrix.det();

    //assert
    EXPECT_EQ(det, complex(21, 6));
}

TEST(ComplexWithSqMatrix, inverse) {
    //arrange
    SqMatrix<complex> matrix(2);
    matrix(0, 0) = {2, 1};
    matrix(0, 1) = {1, 1};
    matrix(1, 0) = {3, 1};
    matrix(1, 1) = {22, 18};

    //act
    SqMatrix<complex> matrix2 = matrix.inverse();

    //arrange
    EXPECT_EQ(matrix2(0, 0), complex(125.0/291, -21.0/97));
    EXPECT_EQ(matrix2(0, 1), complex(-13.0/582, 5.0/582));
    EXPECT_EQ(matrix2(1, 0), complex(-7.0/194, 23.0/582));
    EXPECT_EQ(matrix2(1, 1), complex(17.0/582, -7.0/291));
}

TEST(SqMatrixWithPriorityQueue, map) {
    PriorityQueue<complex> queue;
    queue.push(complex(1, 1), 1);
    queue.push(complex(2, 2), 2);
    queue.push(complex(3, 3), 3);
    queue.push(complex(4, 4), 4);
    auto queue2 = queue.map([](const complex &x) { return x * x; });
    EXPECT_EQ(queue2->top().first, complex(0, 2));
    EXPECT_EQ(queue2->top().second, 1);
    queue2->pop();
    EXPECT_EQ(queue2->top().first, complex(0, 8));
    EXPECT_EQ(queue2->top().second, 2);
    queue2->pop();
    EXPECT_EQ(queue2->top().first, complex(0, 18));
    EXPECT_EQ(queue2->top().second, 3);
    queue2->pop();
    EXPECT_EQ(queue2->top().first, complex(0, 32));
    EXPECT_EQ(queue2->top().second, 4);
    delete queue2;
}

TEST(SqMatrixWithPriorityQueue, where) {
    auto func = [](const complex &x) { return x.re() > 2; };
    PriorityQueue<complex> queue;
    queue.push(complex(1, 1), 1);
    queue.push(complex(2, 2), 2);
    queue.push(complex(3, 3), 3);
    queue.push(complex(4, 4), 4);

    auto queue2 = queue.where(func);

    //assert
    EXPECT_EQ(queue2->top().first, complex(3, 3));
    EXPECT_EQ(queue2->top().second, 3);
    queue2->pop();
    EXPECT_EQ(queue2->top().first, complex(4, 4));
    EXPECT_EQ(queue2->top().second, 4);
    delete queue2;
}

TEST(SqMatrixWithPriorityQueue, reduce) {
    auto func = [](const complex &x, const complex &y) { return x + y; };
    PriorityQueue<complex> queue;
    queue.push(complex(1, 1), 1);
    queue.push(complex(2, 2), 2);
    queue.push(complex(3, 3), 3);
    queue.push(complex(4, 4), 4);

    complex reduced = queue.reduce(func);

    //assert
    EXPECT_EQ(reduced, complex(10, 10));
}

