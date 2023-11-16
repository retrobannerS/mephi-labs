#include "smart_pointers/ControlBlock.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(ControlBlockArrayTests, Constructor) {
    // arrange and act
    auto block = new ControlBlock<int[]>(new int[3]{10, 2, 3});

    // assert
    EXPECT_NE(block->get(), nullptr);
    EXPECT_EQ(block->get()[0], 10);
    EXPECT_EQ(block->get_ref_count(), 1);

    // delete
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockArrayTests, IncrementRefCount) {
    // arrange
    auto block = new ControlBlock<int[]>(new int[3]{10, 2, 3});

    // act
    block->increment_ref_count();

    // assert
    EXPECT_EQ(block->get_ref_count(), 2);

    // delete
    block->decrement_ref_count_and_delete_if_0();
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockArrayTests, DecrementRefCount) {
    // arrange
    auto block = new ControlBlock<int[]>(new int[3]{10, 2, 3});

    // act
    block->increment_ref_count();
    block->decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block->get_ref_count(), 1);
    EXPECT_NE(block->get(), nullptr);

    // act
    block->decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockArrayTests, ConstructorWithNullptr) {
    // arrange and act
    //  Constructing a ControlBlock with nullptr should throw a std::invalid_argument exception
    EXPECT_THROW(sem3::ControlBlock<int[]> block(nullptr), std::invalid_argument);
}
