#include "data_classes/SmartDynamicArray.hpp"
#include "gtest/gtest.h"
#include <stdexcept>
#include <string>

using namespace sem3;

SharedPtr<SmartDynamicArray<std::string>> ArrayForTest() {
    auto a = make_shared<std::string[]>(10);
    for (int i = 0; i != 10; ++i) {
        a[i] = "TEST" + std::to_string(i);
    }
    auto ptr = sem3::make_shared<SmartDynamicArray<std::string>>(10, a);
    return ptr;
}

TEST(SmartDynamicArray, DefaultConstructor) {
    // arrange
    SmartDynamicArray<int> arr;

    // act

    // assert
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_THROW(arr.get(0), std::out_of_range);
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithSize) {
    // arrange
    SmartDynamicArray<int> arr(5);

    // act

    // assert
    EXPECT_EQ(arr.getSize(), 5);
    EXPECT_THROW(arr.get(5), std::out_of_range);
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr.get(-1), std::out_of_range);
    EXPECT_THROW(arr[-1], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithZeroSize) {
    // arrange
    SmartDynamicArray<int> arr(0);

    // act

    // assert
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_THROW(arr.get(0), std::out_of_range);
    EXPECT_THROW(arr[0], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithNegativeSize) {
    // arrange

    // act

    // assert
    EXPECT_THROW(SmartDynamicArray<int>(-1), std::invalid_argument);
}

TEST(SmartDynamicArray, ConstructorWithSizeAndItem) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_EQ(arr->getSize(), 10);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
    EXPECT_THROW(arr->get(10), std::out_of_range);
    EXPECT_THROW((*arr)[10], std::out_of_range);
    EXPECT_THROW(arr->get(-1), std::out_of_range);
    EXPECT_THROW((*arr)[-1], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithSizeAndItemWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act

    // assert
    EXPECT_EQ(arr->getSize(), 0);
    EXPECT_THROW(arr->get(0), std::out_of_range);
    EXPECT_THROW((*arr)[0], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithSizeAndItemWithNegativeSize) {
    // arrange

    // act

    // assert
    EXPECT_THROW(SmartDynamicArray<int>(-1, 0), std::invalid_argument);
}

TEST(SmartDynamicArray, ConstructorWithArray) {
    // arrange
    auto arr = sem3::make_shared<int[]>(10);
    for (int i = 0; i != 10; ++i) {
        arr[i] = i;
    }

    // act
    SmartDynamicArray<int> arr2(10, arr.get());

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), 0);
    EXPECT_EQ(arr2.get(4), 4);
}

TEST(SmartDynamicArray, ConstructorWithArrayWithZeroSize) {
    // arrange
    auto arr = sem3::make_shared<int[]>(0);

    // act
    SmartDynamicArray<int> arr2(0, arr.get());

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithArrayWithNegativeSize) {
    // arrange
    auto arr = sem3::make_shared<int[]>(0);

    // act

    // assert
    EXPECT_THROW(SmartDynamicArray<int>(-1, arr.get()), std::invalid_argument);
}

TEST(SmartDynamicArray, ConstructorWithSharedPtrArray) {
    // arrange
    auto arr = sem3::make_shared<std::string[]>(10);
    for (int i = 0; i != 10; ++i) {
        arr[i] = "TEST" + std::to_string(i);
    }

    // act
    SmartDynamicArray<std::string> arr2(10, arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), "TEST0");
    EXPECT_EQ(arr2.get(4), "TEST4");
}

