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

TEST(SmartDynamicArray, ConstructorWithSharedPtrArrayWithZeroSize) {
    // arrange
    auto arr = sem3::make_shared<std::string[]>(0);

    // act
    SmartDynamicArray<std::string> arr2(0, arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
}

TEST(SmartDynamicArray, ConstructorWithSharedPtrArrayWithNegativeSize) {
    // arrange
    auto arr = sem3::make_shared<std::string[]>(0);

    // act

    // assert
    EXPECT_THROW(SmartDynamicArray<std::string>(-1, arr), std::invalid_argument);
}

TEST(SmartDynamicArray, CopyConstructor) {
    // arrange
    auto arr = ArrayForTest();

    // act
    SmartDynamicArray<std::string> arr2(*arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), "TEST0");
    EXPECT_EQ(arr2.get(4), "TEST4");
}

TEST(SmartDynamicArray, CopyConstructorWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act
    SmartDynamicArray<int> arr2(*arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
}

TEST(SmartDynamicArray, MoveConstructor) {
    // arrange
    auto arr = ArrayForTest();

    // act
    SmartDynamicArray<std::string> arr2(std::move(*arr));

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), "TEST0");
    EXPECT_EQ(arr2.get(4), "TEST4");
    EXPECT_EQ(arr->getSize(), 0);
    EXPECT_THROW(arr->get(0), std::out_of_range);
}

TEST(SmartDynamicArray, MoveConstructorWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act
    SmartDynamicArray<int> arr2(std::move(*arr));

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
    EXPECT_EQ(arr->getSize(), 0);
    EXPECT_THROW(arr->get(0), std::out_of_range);
}

TEST(SmartDynamicArray, DynamicArrayCopyConstructor) {
    // arrange
    lab2::DynamicArray<int> arr(10);
    for (int i = 0; i != 10; ++i) {
        arr.Set(i, i);
    }

    // act
    SmartDynamicArray<int> arr2(arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), 0);
    EXPECT_EQ(arr2.get(4), 4);
}

TEST(SmartDynamicArray, DynamicArrayCopyConstructorWithZeroSize) {
    // arrange
    lab2::DynamicArray<int> arr(0);

    // act
    SmartDynamicArray<int> arr2(arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
}

TEST(SmartDynamicArray, Destructor) {
    // arrange
    auto arr = new SmartDynamicArray<int>(10);

    // act
    delete arr;

    // assert
}

TEST(SmartDynamicArray, AssignmentOperator) {
    // arrange
    auto arr = ArrayForTest();
    SmartDynamicArray<std::string> arr2;

    // act
    arr2 = *arr;

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), "TEST0");
    EXPECT_EQ(arr2.get(4), "TEST4");
}

TEST(SmartDynamicArray, AssignmentOperatorWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);
    SmartDynamicArray<int> arr2;

    // act
    arr2 = *arr;

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
}

TEST(SmartDynamicArray, AssignmentOperatorWithSelf) {
    // arrange
    auto arr = ArrayForTest();

    // act
    *arr = *arr;

    // assert
    EXPECT_EQ(arr->getSize(), 10);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
}

TEST(SmartDynamicArray, MoveAssignmentOperator) {
    // arrange
    auto arr = ArrayForTest();
    SmartDynamicArray<std::string> arr2;

    // act
    arr2 = std::move(*arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), "TEST0");
    EXPECT_EQ(arr2.get(4), "TEST4");
    EXPECT_EQ(arr->getSize(), 0);
    EXPECT_THROW(arr->get(0), std::out_of_range);
}

TEST(SmartDynamicArray, MoveAssignmentOperatorWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);
    SmartDynamicArray<int> arr2;

    // act
    arr2 = std::move(*arr);

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
    EXPECT_EQ(arr->getSize(), 0);
    EXPECT_THROW(arr->get(0), std::out_of_range);
}

TEST(SmartDynamicArray, MoveAssignmentOperatorWithSelf) {
    // arrange
    auto arr = ArrayForTest();

    // act
    *arr = std::move(*arr);

    // assert
    EXPECT_EQ(arr->getSize(), 10);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
}

TEST(SmartDynamicArray, DynamicArrayAssignmentOperator) {
    // arrange
    lab2::DynamicArray<int> arr(10);
    for (int i = 0; i != 10; ++i) {
        arr.Set(i, i);
    }
    SmartDynamicArray<int> arr2;

    // act
    arr2 = arr;

    // assert
    EXPECT_EQ(arr2.getSize(), 10);
    EXPECT_EQ(arr2.get(0), 0);
    EXPECT_EQ(arr2.get(4), 4);
}

TEST(SmartDynamicArray, DynamicArrayAssignmentOperatorWithZeroSize) {
    // arrange
    lab2::DynamicArray<int> arr(0);
    SmartDynamicArray<int> arr2;

    // act
    arr2 = arr;

    // assert
    EXPECT_EQ(arr2.getSize(), 0);
    EXPECT_THROW(arr2.get(0), std::out_of_range);
    EXPECT_THROW(arr2[0], std::out_of_range);
}

TEST(SmartDynamicArray, GetMethod) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
    EXPECT_EQ(arr->get(9), "TEST9");
}

TEST(SmartDynamicArray, GetMethodWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act

    // assert
    EXPECT_THROW(arr->get(0), std::out_of_range);
    EXPECT_THROW((*arr)[0], std::out_of_range);
}

TEST(SmartDynamicArray, GetMethodWithNegativeIndex) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->get(-1), std::out_of_range);
    EXPECT_THROW((*arr)[-1], std::out_of_range);
}

TEST(SmartDynamicArray, GetMethodWithIndexOutOfRange) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->get(10), std::out_of_range);
    EXPECT_THROW((*arr)[10], std::out_of_range);
}

TEST(SmartDynamicArray, GetSizeMethod) {
    // arrange
    auto arr = ArrayForTest();
    auto arr2 = make_shared<SmartDynamicArray<int>>(0, 0);

    // act

    // assert
    EXPECT_EQ(arr->getSize(), 10);
    EXPECT_EQ(arr2->getSize(), 0);
}

TEST(SmartDynamicArray, GetSubArrayMethod) {
    // arrange
    auto arr = ArrayForTest();

    // act
    auto arr2 = arr->getSubArray(2, 5);
    auto arr3 = arr->getSubArray(0, 10);

    // assert
    EXPECT_EQ(arr2.get(0), "TEST2");
    EXPECT_EQ(arr2.getSize(), 3);
    EXPECT_EQ(arr2.get(2), "TEST4");
    EXPECT_EQ(arr3.getSize(), 10);
    EXPECT_EQ(arr3.get(0), "TEST0");
    EXPECT_EQ(arr3.get(9), "TEST9");
}

TEST(SmartDynamicArray, GetSubArrayMethodExcepts) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->getSubArray(-1, 5), std::out_of_range);
    EXPECT_THROW(arr->getSubArray(2, 1), std::invalid_argument);
    EXPECT_THROW(arr->getSubArray(0, 11), std::out_of_range);
    EXPECT_THROW(arr->getSubArray(10, 10), std::out_of_range);
    EXPECT_THROW(arr->getSubArray(2, -1), std::out_of_range);
}

TEST(SmartDynamicArray, SetMethod) {
    // arrange
    auto arr = ArrayForTest();

    // act
    arr->set(0, "TEST10");
    arr->set(4, "TEST11");
    arr->set(9, "TEST12");

    // assert
    EXPECT_EQ(arr->get(0), "TEST10");
    EXPECT_EQ(arr->get(4), "TEST11");
    EXPECT_EQ(arr->get(9), "TEST12");
    EXPECT_EQ(arr->get(1), "TEST1");
    EXPECT_EQ(arr->get(3), "TEST3");
    EXPECT_EQ(arr->get(8), "TEST8");
}

TEST(SmartDynamicArray, SetMethodExceptions) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->set(-1, "TEST10"), std::out_of_range);
    EXPECT_THROW(arr->set(10, "TEST10"), std::out_of_range);
}

TEST(SmartDynamicArray, OtherSetMethod) {
    // arrange
    auto arr = ArrayForTest();

    // act
    arr->set(2, 5, "TEST10");

    // assert
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(1), "TEST1");
    EXPECT_EQ(arr->get(2), "TEST10");
    EXPECT_EQ(arr->get(3), "TEST10");
    EXPECT_EQ(arr->get(4), "TEST10");
    EXPECT_EQ(arr->get(5), "TEST5");
    EXPECT_EQ(arr->get(6), "TEST6");
    EXPECT_EQ(arr->get(9), "TEST9");
}

TEST(SmartDynamicArray, OtherSetMethodExceptions) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->set(-1, 5, "TEST10"), std::out_of_range);
    EXPECT_THROW(arr->set(2, 1, "TEST10"), std::invalid_argument);
    EXPECT_THROW(arr->set(0, 11, "TEST10"), std::out_of_range);
    EXPECT_THROW(arr->set(10, 10, "TEST10"), std::out_of_range);
    EXPECT_THROW(arr->set(2, -1, "TEST10"), std::out_of_range);
}

TEST(SmartDynamicArray, IndexOperator) {
    // arrange
    auto arr = ArrayForTest();

    // act
    (*arr)[3] = "TEST10";

    // assert
    EXPECT_EQ((*arr)[0], "TEST0");
    EXPECT_EQ((*arr)[4], "TEST4");
    EXPECT_EQ((*arr)[9], "TEST9");
    EXPECT_EQ((*arr)[3], "TEST10");
}

TEST(SmartDynamicArray, IndexOperatorWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act

    // assert
    EXPECT_THROW((*arr)[0], std::out_of_range);
}

TEST(SmartDynamicArray, IndexOperatorWithNegativeIndex) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW((*arr)[-1], std::out_of_range);
}

TEST(SmartDynamicArray, IndexOperatorWithIndexOutOfRange) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW((*arr)[10], std::out_of_range);
}

TEST(SmartDynamicArray, ConcatOperator) {
    // arrange
    auto arr = ArrayForTest();
    auto arr2 = ArrayForTest();

    // act
    auto arr3 = *arr + *arr2;

    // assert
    EXPECT_EQ(arr3.getSize(), 20);
    EXPECT_EQ(arr3.get(0), "TEST0");
    EXPECT_EQ(arr3.get(4), "TEST4");
    EXPECT_EQ(arr3.get(9), "TEST9");
    EXPECT_EQ(arr3.get(10), "TEST0");
    EXPECT_EQ(arr3.get(14), "TEST4");
    EXPECT_EQ(arr3.get(19), "TEST9");
}

TEST(SmartDynamicArray, ManyConcatOperators) {
    // arrange
    auto arr = ArrayForTest();
    auto arr2 = ArrayForTest();
    auto arr3 = ArrayForTest();
    auto arr4 = ArrayForTest();
    auto arr5 = ArrayForTest();

    // act
    auto arr6 = *arr + *arr2 + *arr3 + *arr4 + *arr5;

    // assert
    EXPECT_EQ(arr6.getSize(), 50);
    EXPECT_EQ(arr6.get(0), "TEST0");
    EXPECT_EQ(arr6.get(4), "TEST4");
    EXPECT_EQ(arr6.get(9), "TEST9");
    EXPECT_EQ(arr6.get(10), "TEST0");
    EXPECT_EQ(arr6.get(14), "TEST4");
    EXPECT_EQ(arr6.get(19), "TEST9");
    EXPECT_EQ(arr6.get(20), "TEST0");
    EXPECT_EQ(arr6.get(24), "TEST4");
    EXPECT_EQ(arr6.get(29), "TEST9");
    EXPECT_EQ(arr6.get(30), "TEST0");
    EXPECT_EQ(arr6.get(34), "TEST4");
    EXPECT_EQ(arr6.get(39), "TEST9");
    EXPECT_EQ(arr6.get(40), "TEST0");
    EXPECT_EQ(arr6.get(44), "TEST4");
    EXPECT_EQ(arr6.get(49), "TEST9");
}

TEST(SmartDynamicArray, ConcatOperatorWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);
    auto arr2 = make_shared<SmartDynamicArray<int>>(0, 0);

    // act
    auto arr3 = *arr + *arr2;

    // assert
    EXPECT_EQ(arr3.getSize(), 0);
    EXPECT_THROW(arr3.get(0), std::out_of_range);
}

TEST(SmartDynamicArray, ConcatOperatorWithSelf) {
    // arrange
    auto arr = ArrayForTest();

    // act
    auto arr3 = *arr + *arr;

    // assert
    EXPECT_EQ(arr3.getSize(), 20);
    EXPECT_EQ(arr3.get(0), "TEST0");
    EXPECT_EQ(arr3.get(4), "TEST4");
    EXPECT_EQ(arr3.get(9), "TEST9");
    EXPECT_EQ(arr3.get(10), "TEST0");
    EXPECT_EQ(arr3.get(14), "TEST4");
    EXPECT_EQ(arr3.get(19), "TEST9");
}

TEST(SmartDynamicArray, ResizeMethod) {
    // arrange
    auto arr = ArrayForTest();

    // act
    arr->resize(5);

    // assert
    EXPECT_EQ(arr->getSize(), 5);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
    EXPECT_THROW(arr->get(5), std::out_of_range);
}

TEST(SmartDynamicArray, ResizeMethod2) {
    // arrange
    auto arr = ArrayForTest();

    // act
    arr->resize(15);

    // assert
    EXPECT_EQ(arr->getSize(), 15);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
    EXPECT_EQ(arr->get(9), "TEST9");
    EXPECT_THROW(arr->get(15), std::out_of_range);
}

TEST(SmartDynamicArray, ResizeMethodWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act
    arr->resize(5);

    // assert
    EXPECT_EQ(arr->getSize(), 5);
}

TEST(SmartDynamicArray, ResizeMethodWithNegativeSize) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->resize(-1), std::invalid_argument);
}

TEST(SmartDynamicArray, ResizeMethodWithItem) {
    // arrange
    auto arr = ArrayForTest();

    // act
    arr->resize(5, "TEST10");

    // assert
    EXPECT_EQ(arr->getSize(), 5);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
    EXPECT_THROW(arr->get(5), std::out_of_range);
}

TEST(SmartDynamicArray, ResizeMethodWithItem2) {
    // arrange
    auto arr = ArrayForTest();

    // act
    arr->resize(15, "TEST10");

    // assert
    EXPECT_EQ(arr->getSize(), 15);
    EXPECT_EQ(arr->get(0), "TEST0");
    EXPECT_EQ(arr->get(4), "TEST4");
    EXPECT_EQ(arr->get(9), "TEST9");
    EXPECT_EQ(arr->get(10), "TEST10");
    EXPECT_EQ(arr->get(14), "TEST10");
    EXPECT_THROW(arr->get(15), std::out_of_range);
}

TEST(SmartDynamicArray, ResizeMethodWithItemWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);

    // act
    arr->resize(5, 10);

    // assert
    EXPECT_EQ(arr->getSize(), 5);
    EXPECT_EQ(arr->get(0), 10);
    EXPECT_EQ(arr->get(4), 10);
}

TEST(SmartDynamicArray, ResizeMethodWithItemWithNegativeSize) {
    // arrange
    auto arr = ArrayForTest();

    // act

    // assert
    EXPECT_THROW(arr->resize(-1, "TEST10"), std::invalid_argument);
}

TEST(SmartDynamicArray, ConcatMethod) {
    // arrange
    auto arr = ArrayForTest();
    auto arr2 = ArrayForTest();

    // act
    auto arr3 = arr->concat(*arr2);

    // assert
    EXPECT_EQ(arr3.getSize(), 20);
    EXPECT_EQ(arr3.get(0), "TEST0");
    EXPECT_EQ(arr3.get(4), "TEST4");
    EXPECT_EQ(arr3.get(9), "TEST9");
    EXPECT_EQ(arr3.get(10), "TEST0");
    EXPECT_EQ(arr3.get(14), "TEST4");
    EXPECT_EQ(arr3.get(19), "TEST9");
}

TEST(SmartDynamicArray, ConcatMethodWithZeroSize) {
    // arrange
    auto arr = make_shared<SmartDynamicArray<int>>(0, 0);
    auto arr2 = make_shared<SmartDynamicArray<int>>(0, 0);

    // act
    auto arr3 = arr->concat(*arr2);

    // assert
    EXPECT_EQ(arr3.getSize(), 0);
    EXPECT_THROW(arr3.get(0), std::out_of_range);
}

TEST(SmartDynamicArray, ConcatMethodWithSelf) {
    // arrange
    auto arr = ArrayForTest();

    // act
    auto arr3 = arr->concat(*arr);

    // assert
    EXPECT_EQ(arr3.getSize(), 20);
    EXPECT_EQ(arr3.get(0), "TEST0");
    EXPECT_EQ(arr3.get(4), "TEST4");
    EXPECT_EQ(arr3.get(9), "TEST9");
    EXPECT_EQ(arr3.get(10), "TEST0");
    EXPECT_EQ(arr3.get(14), "TEST4");
    EXPECT_EQ(arr3.get(19), "TEST9");
}
