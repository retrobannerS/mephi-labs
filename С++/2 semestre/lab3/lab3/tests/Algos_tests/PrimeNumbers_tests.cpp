#include <gtest/gtest.h>
#include <utility>
#include "ArraySequence.hpp"
#include "Algos/PrimeNumbers/PrimeNumbers.h"

using namespace lab2;
using namespace lab3;
using namespace std;

TEST(PrimeNumberTest, TestFactorize) {
    // Arrange
    int num1 = 100;
    pair<int, int> values1[2] = { {2, 2}, {5, 2} };
    ArraySequence<std::pair<int, int>> expected1(2, values1);

    int num2 = 17;
    pair<int, int> values2[1] = { {17, 1} };
    ArraySequence<std::pair<int, int>> expected2(1, values2);

    // Act
    ArraySequence<pair<int,int>> arr1 = factorize(num1);
    ArraySequence<pair<int,int>> arr2 = factorize(num2);

    //assert
    ASSERT_EQ(arr1.GetSize(), expected1.GetSize());
    ASSERT_EQ(arr2.GetSize(), expected2.GetSize());
    for(int i = 0; i < arr1.GetSize(); i++){
        ASSERT_EQ(arr1.Get(i).first, expected1.Get(i).first);
        ASSERT_EQ(arr1.Get(i).second, expected1.Get(i).second);
    }
    for(int i = 0; i < arr2.GetSize(); i++){
        ASSERT_EQ(arr2.Get(i).first, expected2.Get(i).first);
        ASSERT_EQ(arr2.Get(i).second, expected2.Get(i).second);
    }
}

TEST(PrimeNumberTest, TestIsPrime) {
    // Arrange & Act & Assert
    ASSERT_TRUE(isPrime(2));
    ASSERT_TRUE(isPrime(3));
    ASSERT_TRUE(isPrime(7));
    ASSERT_FALSE(isPrime(1));
    ASSERT_FALSE(isPrime(4));
    ASSERT_FALSE(isPrime(9));
}

TEST(PrimeNumberTest, TestSieveOfEratosthenes) {
    // Arrange
    int n = 10;
    bool values[] = {false, false, true, true, false, true, false, true, false, false, false};
    ArraySequence<bool> expected(11, values);

    // Act
    ArraySequence<bool> result = sieveOfEratosthenes(n);

    // Assert
    ASSERT_EQ(result.GetSize(), expected.GetSize());
    for(int i = 0; i < result.GetSize(); i++){
        ASSERT_EQ(result.Get(i), expected.Get(i));
    }
}