#include "smart_pointers/ControlBlock.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(ControlBlockTests, Constructor) {
    // arrange and act
    ControlBlock<int> block(new int(10));

    // assert
    EXPECT_NE(block.get(), nullptr);
    EXPECT_EQ(*block.get(), 10);
    EXPECT_EQ(block.get_ref_count(), 1);

    // delete
    block.decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, IncrementRefCount) {
    // arrange
    ControlBlock<int> block(new int(10));

    // act
    block.increment_ref_count();

    // assert
    EXPECT_EQ(block.get_ref_count(), 2);

    // delete
    block.decrement_ref_count_and_delete_if_0();
}

TEST(ControlBlockTests, DecrementRefCount) {
    // arrange
    ControlBlock<int> block(new int(10));

    // act
    block.increment_ref_count();
    block.decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block.get_ref_count(), 1);
    EXPECT_NE(block.get(), nullptr);

    // act
    block.decrement_ref_count_and_delete_if_0();

    // assert
    EXPECT_EQ(block.get_ref_count(), 0);
    EXPECT_EQ(block.get(), nullptr);
}

TEST(ControlBlockTests, ConstructorWithNullptr) {
    // arrange and act
    EXPECT_THROW(ControlBlock<int> block(nullptr), std::invalid_argument);
}

TEST(ControlBlockTests, DecrementRefCountWithRefCount0) {
    // arrange
    ControlBlock<int> block(new int(10));

    // act
    block.decrement_ref_count_and_delete_if_0();

    // act and assert
    //  Decrementing the reference count when it's already 0 should throw a std::logic_error exception
    EXPECT_THROW(block.decrement_ref_count_and_delete_if_0(), std::logic_error);
}