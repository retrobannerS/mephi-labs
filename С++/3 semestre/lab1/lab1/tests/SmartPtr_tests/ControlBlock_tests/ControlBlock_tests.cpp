#include "smart_pointers/ControlBlock.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(ControlBlockTests, Constructor) {
    // arrange and act
    auto block = new ControlBlock<int>(new int(10));

    // assert
    EXPECT_NE(block->get(), nullptr);
    EXPECT_EQ(*(block->get()), 10);
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_EQ(block->get_weak_ref_count(), 0);

    // delete
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, IncrementRefCount) {
    // arrange
    auto block = new ControlBlock<int>(new int(10));

    // act
    block->increment_ref_count();

    // assert
    EXPECT_EQ(block->get_ref_count(), 2);
    EXPECT_EQ(block->get_weak_ref_count(), 0);

    // delete
    block->decrement_ref_count_and_delete_if_0();
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, CorrectDeleting) {
    // arrange
    auto block = new ControlBlock<int>(new int(10));

    // act
    block->increment_ref_count();
    block->increment_weak_ref_count();

    // assert
    EXPECT_EQ(block->get_ref_count(), 2);
    EXPECT_EQ(block->get_weak_ref_count(), 1);

    // act
    block->decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_EQ(block->get_weak_ref_count(), 1);
    EXPECT_NE(block->get(), nullptr);

    // act
    block->decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_ref_count(), 0);
    EXPECT_EQ(block->get_weak_ref_count(), 1);
    EXPECT_EQ(block->get(), nullptr);
    EXPECT_THROW(block->decrement_ref_count_and_delete_if_0(), std::logic_error);

    //delete
    block->decrement_weak_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, DecrementRefCount) {
    // arrange
    int *rawPtr = new int(10);
    auto block = new ControlBlock<int>(rawPtr);

    // act
    block->increment_ref_count();
    block->decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_NE(block->get(), nullptr);

    // act
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, IncrementWeakRefCount) {
    // arrange
    auto block = new ControlBlock<int>(new int(10));

    // act
    block->increment_weak_ref_count();

    // assert
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_EQ(block->get_weak_ref_count(), 1);

    // delete
    block->decrement_ref_count_and_delete_if_0();
    block->decrement_weak_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, DecrementWeakRefCount) {
    // arrange
    auto block = new ControlBlock<int>(new int(10));

    // act
    block->increment_weak_ref_count();
    
    // assert
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_EQ(block->get_weak_ref_count(), 1);

    // delete
    block->decrement_weak_ref_count_and_delete_if_0();
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, CorrectDeletingWithWeakRefCount) {
    // arrange
    auto block = new ControlBlock<int>(new int(10));

    // act
    block->increment_ref_count();
    block->increment_weak_ref_count();

    // assert
    EXPECT_EQ(block->get_ref_count(), 2);
    EXPECT_EQ(block->get_weak_ref_count(), 1);

    // act
    block->decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_EQ(block->get_weak_ref_count(), 1);
    EXPECT_NE(block->get(), nullptr);

    // act
    block->decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_ref_count(), 0);
    EXPECT_EQ(block->get_weak_ref_count(), 1);
    EXPECT_EQ(block->get(), nullptr);

    // delete
    block->decrement_weak_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, GetWeakRefCount) {
    // arrange
    auto block = new ControlBlock<int>(new int(10));

    // act
    block->increment_weak_ref_count();
    block->increment_weak_ref_count();

    // assert
    EXPECT_EQ(block->get_weak_ref_count(), 2);

    // act
    block->decrement_weak_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_weak_ref_count(), 1);

    // delete
    block->decrement_ref_count_and_delete_if_0();
    block->decrement_weak_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, ConstructorWithNullptr) {
    // arrange and act
    EXPECT_THROW(ControlBlock<int> block(nullptr), std::invalid_argument);
}