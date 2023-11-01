#include "BaseContainer.hpp"
#include "Collections/Stack.hpp"
#include "gtest/gtest.h"

using namespace lab2;
using namespace lab3;

TEST(BaseContainer, empty) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    Stack<int> stack2(10);
    EXPECT_FALSE(stack2.empty());
}

TEST(BaseContainer, size) {
    Stack<int> stack;
    EXPECT_EQ(stack.size(), 0);
    Stack<int> stack2(10);
    EXPECT_EQ(stack2.size(), 10);
    int array_to_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stack<int> stack3(10, array_to_constructor);
    EXPECT_EQ(stack3.size(), 10);
    EXPECT_EQ(1, 1);
}

TEST(BaseContainer, clear) {
    int array_to_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stack<int> stack(10, array_to_constructor);
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(stack.pop(), 10 - i);
    }
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST(BaseContainer, empty_clear) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    stack.clear();
    EXPECT_TRUE(stack.empty());
}

TEST(BaseContainer, reduce) {
    auto add = [](const int &a, const int &b) -> int { return a + b; };
    auto mult = [](const int &a, const int &b) -> int { return a * b; };
    int array_to_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stack<int> stack(10, array_to_constructor);
    EXPECT_EQ(stack.reduce(add), 55);
    EXPECT_EQ(stack.reduce(mult), 3628800);
}

TEST(BaseContainer, ReduceEmptyOneAndTwo) {
    Stack<int> stack0;
    Stack<int> stack1(1);
    Stack<int> stack2(2);
    auto add = [](const int &a, const int &b) -> int { return a + b; };
    EXPECT_THROW(stack0.reduce(add), std::invalid_argument);
    EXPECT_THROW(stack1.reduce(add), std::invalid_argument);
    EXPECT_EQ(stack2.reduce(add), 0);
}

TEST(BaseContainer, slice) {
    //arrange
    Stack<int> stack;
    ListSequence<int> sequence_for_slice(3, 5);

    //act
    stack.push(5);
    stack.push(7);
    stack.push(7);
    stack.push(7);
    stack.push(5);
    stack.slice(1, 3, sequence_for_slice);

    //assert
    EXPECT_EQ(stack.size(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(stack.pop(), 5);
    }
    EXPECT_TRUE(stack.empty());
}

TEST(BaseContainer, SliceWithNegativeArguments) {
    //arrange
    Stack<int> stack;
    int array_for_constructor[5] = {1, 2, 3, 4, 5};
    ListSequence<int> sequence_for_slice1(5, array_for_constructor);
    ListSequence<int> sequence_for_slice2(7, 1);

    //act
    stack.push(5);
    stack.push(7);
    stack.push(7);
    stack.push(7);
    stack.push(7);
    stack.push(7);
    stack.push(8);
    stack.slice(-2, 5, sequence_for_slice1);

    //assert
    EXPECT_EQ(stack.size(), 7);
    EXPECT_EQ(stack.pop(), 8);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.pop(), 5);
    EXPECT_EQ(stack.pop(), 5);
    EXPECT_TRUE(stack.empty());
}

TEST(BaseContainer, WrongSlice) {
    //arrange
    Stack<int> stack;
    ListSequence<int> sequence_for_slice1(5, 1);
    ListSequence<int> sequence_for_slice2(7, 1);

    //act
    stack.push(5);
    stack.push(7);
    stack.push(7);
    stack.push(7);
    stack.push(7);

    //assert
    EXPECT_THROW(stack.slice(1, 5, sequence_for_slice1), std::out_of_range);
    EXPECT_THROW(stack.slice(1, 7, sequence_for_slice2), std::out_of_range);
    EXPECT_THROW(stack.slice(1, 0, sequence_for_slice1), std::out_of_range);
    EXPECT_THROW(stack.slice(1, -1, sequence_for_slice1), std::out_of_range);
    EXPECT_THROW(stack.slice(1, 2, sequence_for_slice2), std::out_of_range);
    EXPECT_THROW(stack.slice(-51, 0, sequence_for_slice2), std::out_of_range);
    EXPECT_THROW(stack.slice(-51, -1, sequence_for_slice2), std::out_of_range);
}

TEST(BaseContainer, Iterators) {
    int array_to_constructor[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Stack<int> stack(10, array_to_constructor);
    for(const auto it : stack) {
        EXPECT_EQ(it, array_to_constructor[it]);
    }
}

TEST(BaseContainer, EmptyIterator) {
    Stack<int> stack;
    for(const auto it : stack) {
        EXPECT_FALSE(true);
    }
}

TEST(BaseContainer, find) {
    //arrange
    int values1[15] = {2, 7, 18, 23, 4, 35, 28, 39, 42, 1, 2, 3, 0, -10, -15};
    int values2[5] = {42, 1, 2, 3, 0};
    Stack<int> stack(15, values1);
    Sequence<int> *sequence_for_find1 = new ListSequence<int>(15, values1);
    Sequence<int> *sequence_for_find2 = new ListSequence<int>(5, values2);
    Sequence<int> *sequence_for_find3 = new ListSequence<int>(10, 5);

    //act
    int index1 = stack.find(*sequence_for_find1);
    int index2 = stack.find(*sequence_for_find2);


    //assert
    EXPECT_EQ(index1, 0);
    EXPECT_EQ(index2, 8);
    EXPECT_THROW(stack.find(*sequence_for_find3), std::logic_error);
    delete sequence_for_find1;
    delete sequence_for_find2;
    delete sequence_for_find3;
}

TEST(BaseContainer, tryFind) {
    int values1[15] = {2, 7, 18, 23, 4, 35, 28, 39, 42, 1, 2, 3, 0, -10, -15};
    int values2[5] = {42, 1, 2, 3, 0};
    Stack<int> stack(15, values1);
    Sequence<int> *sequence_for_find1 = new ListSequence<int>(15, values1);
    Sequence<int> *sequence_for_find2 = new ListSequence<int>(5, values2);
    Sequence<int> *sequence_for_find3 = new ListSequence<int>(10, 5);

    //act
    Options<int> options1 = stack.tryFind(*sequence_for_find1);
    Options<int> options2 = stack.tryFind(*sequence_for_find2);
    Options<int> options3 = stack.tryFind(*sequence_for_find3);


    //assert
    EXPECT_EQ(options1.Value(), 0);
    EXPECT_EQ(options2.Value(), 8);
    EXPECT_FALSE(options3.HasValue());
    delete sequence_for_find1;
    delete sequence_for_find2;
    delete sequence_for_find3;
}