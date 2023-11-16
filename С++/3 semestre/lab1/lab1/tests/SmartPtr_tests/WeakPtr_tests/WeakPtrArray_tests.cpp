#include "gtest/gtest.h"
#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/WeakPtr.hpp"

using namespace sem3;

TEST(WeakPtrArrayTests, DefaultConstructor) {
    // arrange
    WeakPtr<int[]> ptr;

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, CopyConstructor) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);

    // act
    WeakPtr<int[]> ptr2(ptr);

    // assert
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.expired(), false);
}

TEST(WeakPtrArrayTests, CopyConstructorWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;

    // act
    WeakPtr<int[]> ptr2(ptr);

    // assert
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.expired(), true);
}

TEST(WeakPtrArrayTests, CopyConstructorWithSharedPtr) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);

    // act
    auto shared_ptr2 = ptr.lock();

    // assert
    EXPECT_EQ(shared_ptr2.use_count(), 2);
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(ptr.expired(), false);
}

TEST(WeakPtrArrayTests, MoveConstructor) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);

    // act
    WeakPtr<int[]> ptr2(std::move(ptr));

    // assert
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.expired(), false);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, MoveConstructorWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;

    // act
    WeakPtr<int[]> ptr2(std::move(ptr));

    // assert
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.expired(), true);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, Destructor) {
    // arrange
    auto shared_ptr = new SharedPtr<int[]>(new int[5]);
    WeakPtr<int[]> ptr(*shared_ptr);

    // act
    delete shared_ptr;

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, AssignmentOperator) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);
    WeakPtr<int[]> ptr2;

    // act
    ptr2 = ptr;

    // assert
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.expired(), false);
    EXPECT_EQ(ptr.lock().get(), ptr2.lock().get());
}

TEST(WeakPtrArrayTests, AssignmentOperatorWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;
    WeakPtr<int[]> ptr2;

    // act
    ptr2 = ptr;

    // assert
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.expired(), true);
    EXPECT_EQ(ptr.lock().get(), ptr2.lock().get());
}

TEST(WeakPtrArrayTests, AssignmentOperatorWithSharedPtr) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr;

    // act
    ptr = shared_ptr;

    // assert
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_EQ(ptr.expired(), false);
    EXPECT_EQ(ptr.lock().get(), shared_ptr.get());
}

TEST(WeakPtrArrayTests, AssignmentOperatorWithSharedPtrAndNullptr) {
    // arrange
    SharedPtr<int[]> shared_ptr;
    WeakPtr<int[]> ptr;

    // act
    ptr = shared_ptr;

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(ptr.lock().get(), shared_ptr.get());
}

TEST(WeakPtrArrayTests, MoveAssignmentOperator) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);
    WeakPtr<int[]> ptr2;

    // act
    ptr2 = std::move(ptr);

    // assert
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.expired(), false);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(ptr2.lock().get(), shared_ptr.get());
}

TEST(WeakPtrArrayTests, MoveAssignmentOperatorWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;
    WeakPtr<int[]> ptr2;

    // act
    ptr2 = std::move(ptr);

    // assert
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.expired(), true);
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, Reset) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);

    // act
    ptr.reset();

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(shared_ptr.use_count(), 1);
}

TEST(WeakPtrArrayTests, ResetWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;

    // act
    ptr.reset();

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(ptr.lock().get(), nullptr);
}

TEST(WeakPtrArrayTests, Swap) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);
    WeakPtr<int[]> ptr2;

    // act
    ptr.swap(ptr2);

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.expired(), false);
    EXPECT_EQ(ptr2.lock().get(), shared_ptr.get());
}

TEST(WeakPtrArrayTests, SwapWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;
    WeakPtr<int[]> ptr2;

    // act
    ptr.swap(ptr2);

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(ptr2.use_count(), 0);
    EXPECT_EQ(ptr2.expired(), true);
    EXPECT_EQ(ptr.lock().get(), nullptr);
    EXPECT_EQ(ptr2.lock().get(), nullptr);
}

TEST(WeakPtrArrayTests, Swap2) {
    // arrange
    SharedPtr<int[]> shared_ptr1(new int[5]);
    SharedPtr<int[]> shared_ptr2(new int[10]);
    WeakPtr<int[]> ptr1(shared_ptr1);
    WeakPtr<int[]> ptr2(shared_ptr2);

    // act
    ptr1.swap(ptr2);

    // assert
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_EQ(ptr1.expired(), false);
    EXPECT_EQ(ptr1.lock().get(), shared_ptr2.get());
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr2.expired(), false);
    EXPECT_EQ(ptr2.lock().get(), shared_ptr1.get());
}

TEST(WeakPtrArrayTests, UseCount) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);

    // act
    auto shared_ptr2 = ptr.lock();

    // assert
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(ptr.expired(), false);
    EXPECT_EQ(shared_ptr.use_count(), 2);
    EXPECT_EQ(shared_ptr2.use_count(), 2);
}

TEST(WeakPtrArrayTests, UseCountWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;

    // act
    auto shared_ptr = ptr.lock();

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(shared_ptr.use_count(), 0);
}

TEST(WeakPtrArrayTests, Expired) {
    // arrange
    auto shared_ptr = new SharedPtr<int[]>(new int[5]);
    WeakPtr<int[]> ptr(*shared_ptr);

    // act&assert
    EXPECT_EQ(ptr.expired(), false);
    delete shared_ptr;
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, ExpiredWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;

    // act&assert
    EXPECT_EQ(ptr.expired(), true);
}

TEST(WeakPtrArrayTests, Lock) {
    // arrange
    SharedPtr<int[]> shared_ptr(new int[5]);
    WeakPtr<int[]> ptr(shared_ptr);

    // act
    auto shared_ptr2 = ptr.lock();

    // assert
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(ptr.expired(), false);
    EXPECT_EQ(shared_ptr.use_count(), 2);
    EXPECT_EQ(shared_ptr2.use_count(), 2);
    EXPECT_EQ(shared_ptr.get(), shared_ptr2.get());
}

TEST(WeakPtrArrayTests, LockWithNullptr) {
    // arrange
    WeakPtr<int[]> ptr;

    // act
    auto shared_ptr = ptr.lock();

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(shared_ptr.use_count(), 0);
    EXPECT_EQ(shared_ptr.get(), nullptr);
}

TEST(WeakPtrArrayTests, LockWithExpired) {
    // arrange
    auto shared_ptr = new SharedPtr<int[]>(new int[5]);
    WeakPtr<int[]> ptr(*shared_ptr);

    // act
    delete shared_ptr;
    auto shared_ptr2 = ptr.lock();

    // assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr.expired(), true);
    EXPECT_EQ(shared_ptr2.use_count(), 0);
    EXPECT_EQ(shared_ptr2.get(), nullptr);
}
