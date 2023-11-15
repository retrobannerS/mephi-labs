#include "smart_pointers/SharedPtr.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(SharedPtrArrayTests, EmptyConstructor) {
    //arrange
    SharedPtr<int[]> ptr;

    //act

    //assert
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrArrayTests, Constructor) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]);

    //assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(SharedPtrArrayTests, ConstructorWithNullptr) {
    //arrange
    SharedPtr<int[]> ptr(nullptr);

    //assert
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrArrayTests, CopyConstructor) {
    //arrange
    SharedPtr<int[]> original(new int[10]);

    //act
    SharedPtr<int[]> copy = original;

    //assert
    EXPECT_NE(copy.get(), nullptr);
    EXPECT_EQ(copy.use_count(), 2);
    EXPECT_EQ(original.use_count(), 2);
}

TEST(SharedPtrArrayTests, CopyConstructorWithNullptr) {
    //arrange
    SharedPtr<int[]> original(nullptr);

    //act
    SharedPtr<int[]> copy = original;

    //assert
    EXPECT_EQ(copy.get(), nullptr);
    EXPECT_EQ(copy.use_count(), 0);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrArrayTests, MoveConstructor) {
    //arrange
    SharedPtr<int[]> original(new int[10]);

    //act
    SharedPtr<int[]> moved(std::move(original));

    //assert
    EXPECT_NE(moved.get(), nullptr);
    EXPECT_EQ(moved.use_count(), 1);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrArrayTests, MoveConstructorWithNullptr) {
    //arrange
    SharedPtr<int[]> original(nullptr);

    //act
    SharedPtr<int[]> moved(std::move(original));

    //assert
    EXPECT_EQ(moved.get(), nullptr);
    EXPECT_EQ(moved.use_count(), 0);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrArrayTests, DestructorDecreasesCount) {
    //arrange
    SharedPtr<int[]>* ptr = new SharedPtr<int[]>(new int[10]);
    SharedPtr<int[]> ptr2 = *ptr;
    EXPECT_EQ(ptr2.use_count(), 2);

    //act
    delete ptr; // This should call the destructor

    //assert
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrArrayTests, AssignmentOperator) {
    //arrange
    SharedPtr<int[]> original(new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    SharedPtr<int[]> copy;

    //act
    copy = original;

    //assert
    EXPECT_NE(copy.get(), nullptr);
    EXPECT_EQ(copy.use_count(), 2);
    EXPECT_EQ(original.use_count(), 2);
    EXPECT_EQ(original[5], copy[5]);
}

TEST(SharedPtrArrayTests, AssignmentOperatorWithNullptr) {
    //arrange
    SharedPtr<int[]> original(nullptr);
    SharedPtr<int[]> copy;

    //act
    copy = original;

    //assert
    EXPECT_EQ(copy.get(), nullptr);
    EXPECT_EQ(copy.use_count(), 0);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrArrayTests, MoveAssignmentOperator) {
    //arrange
    SharedPtr<int[]> original(new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    SharedPtr<int[]> moved;

    //act
    moved = std::move(original);

    //assert
    EXPECT_NE(moved.get(), nullptr);
    EXPECT_EQ(moved.use_count(), 1);
    EXPECT_EQ(moved[5], 6);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrArrayTests, MoveAssignmentOperatorWithNullptr) {
    //arrange
    SharedPtr<int[]> original(nullptr);
    SharedPtr<int[]> moved;

    //act
    moved = std::move(original);

    //assert
    EXPECT_EQ(moved.get(), nullptr);
    EXPECT_EQ(moved.use_count(), 0);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrArrayTests, ResetMethodWithObject) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    //act
    ptr.reset(new int[5]{11, 12, 13, 14, 15});

    //assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_EQ(ptr[0], 11);
}

TEST(SharedPtrArrayTests, ResetMethodWithNullptr) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});

    //act
    ptr.reset(nullptr);

    //assert
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrArrayTests, ResetMethodDecreasesCount) {
    //arrange
    SharedPtr<int[]> ptr1(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    SharedPtr<int[]> ptr2 = ptr1;

    //act
    ptr1.reset(new int[10]{10, 11, 12, 13, 14, 15, 16, 17, 18, 19});

    //assert
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrArrayTests, SwapMethod) {
    //arrange
    SharedPtr<int[]> ptr1(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    SharedPtr<int[]> ptr2(new int[10]{10, 11, 12, 13, 14, 15, 16, 17, 18, 19});

    //act
    ptr1.swap(ptr2);

    //assert
    EXPECT_NE(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1[3], 13);
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(ptr2[3], 3);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrArrayTests, SwapMethodWithNullptr) {
    //arrange
    SharedPtr<int[]> ptr1(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    SharedPtr<int[]> ptr2(nullptr);

    //act
    ptr1.swap(ptr2);

    //assert
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(ptr2[3], 3);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrArrayTests, GetMethod) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    //act
    int* raw_ptr = ptr.get();

    //assert
    EXPECT_NE(raw_ptr, nullptr);
    EXPECT_EQ(raw_ptr[3], 3);
}

TEST(SharedPtrArrayTests, GetMethodWithNullptr) {
    //arrange
    SharedPtr<int[]> ptr(nullptr);

    //act
    int* raw_ptr = ptr.get();

    //assert
    EXPECT_EQ(raw_ptr, nullptr);
}

TEST(SharedPtrArrayTests, UniqueMethod) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    //act and assert
    EXPECT_TRUE(ptr.unique());

    //arrange
    SharedPtr<int[]> ptr2 = ptr;

    //act and assert
    EXPECT_FALSE(ptr.unique());
    EXPECT_FALSE(ptr2.unique());
}

TEST(SharedPtrArrayTests, UseCountMethod) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    //act and assert
    EXPECT_EQ(ptr.use_count(), 1);

    //arrange
    SharedPtr<int[]> ptr2 = ptr;

    //act and assert
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}

TEST(SharedPtrArrayTests, UniqueMethodWithNullptr) {
    //arrange
    SharedPtr<int[]> ptr(nullptr);

    //act and assert
    EXPECT_FALSE(ptr.unique());

    //arrange
    SharedPtr<int[]> ptr2 = ptr;

    //act and assert
    EXPECT_FALSE(ptr.unique());
    EXPECT_FALSE(ptr2.unique());
}

TEST(SharedPtrArrayTests, UseCountMethodWithNullptr) {
    //arrange
    SharedPtr<int[]> ptr(nullptr);

    //act and assert
    EXPECT_EQ(ptr.use_count(), 0);

    //arrange
    SharedPtr<int[]> ptr2 = ptr;

    //act and assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 0);
}

TEST(SharedPtrArrayTests, BoolOperator) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    SharedPtr<int[]> ptr2(nullptr);

    //act and assert
    EXPECT_TRUE(ptr);
    EXPECT_FALSE(ptr2);    
}

TEST(SharedPtrArrayTests, ComparisonOperators) {
    //arrange
    SharedPtr<int[]> ptr1(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    SharedPtr<int[]> ptr2 = ptr1;
    SharedPtr<int[]> ptr3(new int[10]{10, 11, 12, 13, 14, 15, 16, 17, 18, 19});
    int* raw_ptr = ptr1.get();

    //act and assert
    EXPECT_EQ(ptr1, ptr2);
    EXPECT_NE(ptr1, ptr3);
    EXPECT_EQ(ptr1, raw_ptr);
    EXPECT_NE(ptr3, raw_ptr);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr3, nullptr);

    //arrange
    ptr1.reset();

    //act and assert
    EXPECT_EQ(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr3, nullptr);
}

TEST(SharedPtrArrayTests, ArraySubscriptOperator) {
    //arrange
    SharedPtr<int[]> ptr(new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    //act and assert
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(ptr[i], i);
    }
}
