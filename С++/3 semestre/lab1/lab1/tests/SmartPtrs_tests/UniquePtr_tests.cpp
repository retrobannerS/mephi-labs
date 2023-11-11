#include <memory>

#include "gtest/gtest.h"
#include "smart_pointers/UniquePtr.hpp"

using namespace sem3;

TEST(UniquePtrTests, EmptyConstructor) {
    // arrange

    // act
    UniquePtr<int> ptr1;

    // assert
    ASSERT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrTests, ConstructorWithPointer) {
    // arrange
    int *rawPtr = new int(42);

    // act
    UniquePtr<int> ptr(rawPtr);

    // assert
    ASSERT_EQ(ptr.get(), rawPtr);
}

TEST(UniquePtrTests, AssignOperatorWithNullptr) {
    // arrange
    int *rawPtr = new int(42);
    UniquePtr<int> ptr(rawPtr);

    // act
    ptr = nullptr;

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTests, ReleaseMethod) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    int *rawPtr = ptr.release();

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(*rawPtr, 42);
    delete rawPtr;
}

TEST(UniquePtrTests, ResetMethod) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    ptr.reset(new int(13));

    // assert
    ASSERT_EQ(*ptr, 13);
}

TEST(UniquePtrTests, ResetMethodWithNullptr) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    ptr.reset();

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTests, SwapMethod) {
    // arrange
    int *rawPtr1 = new int(5);
    int *rawPtr2 = new int(10);
    UniquePtr<int> ptr1(rawPtr1);
    UniquePtr<int> ptr2(rawPtr2);

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(*ptr1, 10);
    ASSERT_EQ(*ptr2, 5);
}

TEST(UniquePtrTests, SwapMethodWithNullptr) {
    // arrange
    int *rawPtr1 = new int(5);
    UniquePtr<int> ptr1(rawPtr1);
    UniquePtr<int> ptr2(nullptr);

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr2, 5);
}

TEST(UniquePtrTests, GetMethod) {
    // arrange
    int *ptr1 = new int(5);
    UniquePtr<int> ptr1_(ptr1);

    // act
    int *ptr1_get = ptr1_.get();
    *ptr1_get = 2;

    // assert
    ASSERT_EQ(ptr1_get, ptr1);
    ASSERT_EQ(*ptr1_, 2);
}

TEST(UniquePtrTests, BooleanConversionOperator) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act & assert
    ASSERT_TRUE(ptr);
    ptr.reset();
    ASSERT_FALSE(ptr);
}

TEST(UniquePtrTests, DereferenceOperator) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act & assert
    ASSERT_EQ(*ptr, 42);
}

TEST(UniquePtrTests, ArrowOperator) {
    // arrange
    struct Foo {
        int bar;
    };
    UniquePtr<Foo> ptr(new Foo{42});

    // act & assert
    ASSERT_EQ(ptr->bar, 42);
}

TEST(UniquePtrTests, BooleanOperators) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(42));
    UniquePtr<int> ptr3(new int(13));
    UniquePtr<int> null_ptr;
    nullptr_t other_null_ptr;

    // act
    int *test_ptr1 = new int(3);
    UniquePtr<int> real_ptr1(test_ptr1);
    int *test_ptr2 = new int(4);
    UniquePtr<int> real_ptr2(test_ptr2);

    // assert
    ASSERT_NE(ptr1, ptr2);
    ASSERT_NE(ptr1, ptr3);
    ASSERT_EQ(ptr1, ptr1);
    ASSERT_NE(ptr1, null_ptr);
    ASSERT_NE(ptr1, other_null_ptr);
    ASSERT_NE(other_null_ptr, ptr1);
    ASSERT_EQ(null_ptr, other_null_ptr);
    ASSERT_EQ(other_null_ptr, null_ptr);
    ASSERT_EQ(test_ptr1, real_ptr1.get());
    ASSERT_EQ(real_ptr1.get(), test_ptr1);
    ASSERT_NE(test_ptr1, real_ptr2.get());
}

TEST(UniquePtrTests, SwapFunction) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(13));

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(*ptr1, 13);
    ASSERT_EQ(*ptr2, 42);
}