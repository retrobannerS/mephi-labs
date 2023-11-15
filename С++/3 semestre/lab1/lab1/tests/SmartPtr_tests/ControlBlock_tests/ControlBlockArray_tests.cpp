#include "gtest/gtest.h"
#include "smart_pointers/ControlBlock.hpp"

TEST(ControlBlockArrayTests, Constructor) {
    //arrange and act
    sem3::ControlBlock<int[]> block(new int[3]{10, 2, 3});

    //assert
    EXPECT_NE(block.get(), nullptr);
    EXPECT_EQ(block.get()[0], 10);
    EXPECT_EQ(block.get_ref_count(), 1);
}

TEST(ControlBlockArrayTests, IncrementRefCount) {
    //arrange
    sem3::ControlBlock<int[]> block(new int[3]{1, 2, 3});

    //act
    block.increment_ref_count();

    //assert
    EXPECT_EQ(block.get_ref_count(), 2);
}

TEST(ControlBlockArrayTests, DecrementRefCount) {
    //arrange
    sem3::ControlBlock<int[]> block(new int[3]{1, 2, 3});

    //act
    block.increment_ref_count();
    block.decrement_ref_count_and_delete_if_0();

    //assert
    EXPECT_EQ(block.get_ref_count(), 1);
    EXPECT_NE(block.get(), nullptr);

    //act
    block.decrement_ref_count_and_delete_if_0();

    //assert
    EXPECT_EQ(block.get_ref_count(), 0);
    EXPECT_EQ(block.get(), nullptr);
}

TEST(ControlBlockArrayTests, ConstructorWithNullptr) {
    //arrange and act
    // Constructing a ControlBlock with nullptr should throw a std::invalid_argument exception
    EXPECT_THROW(sem3::ControlBlock<int[]> block(nullptr), std::invalid_argument);
}

TEST(ControlBlockArrayTests, DecrementRefCountWithRefCount0) {
    //arrange
    sem3::ControlBlock<int[]> block(new int[3]{1, 2, 3});

    //act 
    block.decrement_ref_count_and_delete_if_0();

    //act and assert
    // Decrementing the reference count when it's already 0 should throw a std::logic_error exception
    EXPECT_THROW(block.decrement_ref_count_and_delete_if_0(), std::logic_error);
}