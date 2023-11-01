#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "Collections/Stack.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace std;
using namespace lab2;
using namespace lab3;

TEST(Stack, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(Stack, ConstructorWithSize) {
    Stack<int> stack(5);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    for(int i = 0; i < 5; i++) {
        EXPECT_EQ(stack.pop(), 0);
    }
}

TEST(Stack, ConstructorWithSizeAndItem) {
    Stack<string> stack(5, "Hello");
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 5);
    for(int i = 0; i < 5; i++) {
        EXPECT_EQ(stack.pop(), "Hello");
    }
}

TEST(Stack, ConstructorWithSizeAndItems) {
    string items[] = {"Hello", "World", "!"};
    Stack<string> stack(3, items);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 3);
    for(int i = 0; i < 3; i++) {
        EXPECT_EQ(stack.pop(), items[2 - i]);
    }
}

TEST(Stack, ConstructorWithDynamicArray) {
    DynamicArray<string> array(10, "Hello");
    for(int i = 0; i < 10; i++) {
        array[i] += to_string(i);
    }
    Stack<string> stack(array);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.pop(), array[9 - i]);
    }
}

TEST(Stack, ConstructorWithLinkedList) {
    LinkedList<string> list(10, "Hello");
    for(int i = 0; i < 10; i++) {
        list[i] += to_string(i);
    }
    Stack<string> stack(list);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.pop(), list[9 - i]);
    }
}

TEST(Stack, ConstructorWithSequence) {
    LinkedList<string> list(10, "Hello");
    for(int i = 0; i < 10; i++) {
        list[i] += to_string(i);
    }
    Sequence<string> *test_sequence = new ListSequence<string>(list);
    Stack<string> stack(test_sequence);

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.pop(), list[9 - i]);
        EXPECT_EQ((*test_sequence)[9 - i], list[9 - i]);
    }
    delete test_sequence;
}

TEST(Stack, CopyConstructor) {
    Stack<string> stack;
    for(int i = 0; i < 10; i++) {
        stack.push("Hello" + to_string(i));
    }
    Stack<string> stack2(stack);
    Stack<string> stack3 = stack;

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 10);
    EXPECT_FALSE(stack2.empty());
    EXPECT_EQ(stack2.size(), 10);
    EXPECT_FALSE(stack3.empty());
    EXPECT_EQ(stack3.size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.peek(), stack2.pop());
        EXPECT_EQ(stack.pop(), stack3.pop());
    }
}

TEST(Stack, Destructor) {
    auto *stack = new Stack<string>;
    for(int i = 0; i < 10; i++) {
        stack->push("Hello" + to_string(i));
    }
    delete stack;
}

TEST(Stack, Push) {
    Stack<string> stack;
    for(int i = 0; i < 10; i++) {
        stack.push("Hello" + to_string(i));
    }

    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.pop(), "Hello" + to_string(9 - i));
    }
}

TEST(Stack, Pop) {
    Stack<string> stack;
    for(int i = 0; i < 10; i++) {
        stack.push("Hello" + to_string(i));
    }

    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.pop(), "Hello" + to_string(9 - i));
    }
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    EXPECT_THROW(stack.pop(), out_of_range);
}

TEST(Stack, tryPop) {
    Stack<string> stack;
    Options<string> options;
    for(int i = 0; i < 10; i++) {
        stack.push("Hello" + to_string(i));
    }

    for(int i = 0; i < 10; i++) {
        options = stack.tryPop();
        EXPECT_TRUE(options.HasValue());
        EXPECT_EQ(options.Value(), "Hello" + to_string(9 - i));
    }
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    options = stack.tryPop();
    EXPECT_FALSE(options.HasValue());
}

TEST(Stack, Peek) {
    Stack<string> stack;
    for(int i = 0; i < 10; i++) {
        stack.push("Hello" + to_string(i));
    }

    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(stack.peek(), "Hello" + to_string(9 - i));
        EXPECT_EQ(stack.pop(), "Hello" + to_string(9 - i));
    }
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(Stack, tryPeek) {
    Stack<string> stack;
    Options<string> options;
    for(int i = 0; i < 10; i++) {
        stack.push("Hello" + to_string(i));
    }

    for(int i = 0; i < 10; i++) {
        options = stack.tryPeek();
        EXPECT_TRUE(options.HasValue());
        EXPECT_EQ(options.Value(), "Hello" + to_string(9 - i));
        EXPECT_EQ(stack.pop(), "Hello" + to_string(9 - i));
    }
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    options = stack.tryPeek();
    EXPECT_FALSE(options.HasValue());
}

TEST(Stack, Concat) {
    //arrange
    int array_for_constructor1[5] = {1, 2, 3, 4, 5};
    int array_for_constructor2[5] = {6, 7, 8, 9, 10};
    Stack<int> stack1(5, array_for_constructor1);
    Stack<int> stack2(5, array_for_constructor2);
    Stack<int> *concatenated_stack;

    //act
    concatenated_stack = stack1.concat(stack2);


    //assert
    EXPECT_EQ(concatenated_stack->size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(concatenated_stack->pop(), 10 - i);
    }
    EXPECT_TRUE(concatenated_stack->empty());
    delete concatenated_stack;
}

TEST(Stack, GetSubStack) {
    //arrange
    int array_for_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    Stack<int> stack(10, array_for_constructor);
    Stack<int> *sub_stack;

    //act
    sub_stack = stack.getSubStack(3, 7);

    //assert
    EXPECT_EQ(sub_stack->size(), 5);
    for(int i = 0; i < 5; i++) {
        EXPECT_EQ(sub_stack->pop(), 8 - i);
    }
    EXPECT_TRUE(sub_stack->empty());
    delete sub_stack;
}

TEST(Stack, FullGetSubStack) {
    //arrange
    int array_for_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    Stack<int> stack(10, array_for_constructor);
    Stack<int> *sub_stack;

    //act
    sub_stack = stack.getSubStack(0, 9);

    //assert
    EXPECT_EQ(sub_stack->size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(sub_stack->pop(), 10 - i);
    }
    EXPECT_TRUE(sub_stack->empty());
    delete sub_stack;
}

TEST(Stack, OneGetSubStack) {
    //arrange
    int array_for_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    Stack<int> stack(10, array_for_constructor);
    Stack<int> *sub_stack;

    //act
    sub_stack = stack.getSubStack(3, 3);

    //assert
    EXPECT_EQ(sub_stack->size(), 1);
    EXPECT_EQ(sub_stack->pop(), 4);
    EXPECT_TRUE(sub_stack->empty());
    delete sub_stack;
}

TEST(Stack, WrongGetSubSequence) {
    //arrange
    int array_for_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    Stack<int> stack(10, array_for_constructor);

    //act & assert
    EXPECT_THROW(stack.getSubStack(3, 2), out_of_range);
    EXPECT_THROW(stack.getSubStack(11, 12), out_of_range);
    EXPECT_THROW(stack.getSubStack(-1, 0), out_of_range);
    EXPECT_THROW(stack.getSubStack(0, 11), out_of_range);
    EXPECT_THROW(stack.getSubStack(-1, 11), out_of_range);
    EXPECT_THROW(stack.getSubStack(2, -1), out_of_range);
}

TEST(Stack, OperatorPlus) {
    //arrange
    int array_for_constructor1[5] = {1, 2, 3, 4, 5};
    int array_for_constructor2[5] = {6, 7, 8, 9, 10};
    Stack<int> stack1(5, array_for_constructor1);
    Stack<int> stack2(5, array_for_constructor2);
    Stack<int>* concatenated_stack;

    //act
    concatenated_stack = stack1 + stack2;

    //assert
    EXPECT_EQ(concatenated_stack->size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(concatenated_stack->pop(), 10 - i);
    }
    EXPECT_TRUE(concatenated_stack->empty());
    delete concatenated_stack;
}

TEST(Stack, map) {
    //arrange
    int array_for_constructor[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    Stack<int> stack(10, array_for_constructor);
    Stack<int> *mapped_stack;
    Stack<int> *empty_mapped_stack;
    auto pow2 = [](const int &x) {return x * x;};
    auto zero = [](const int &x) {return 0;};

    //act
    mapped_stack = stack.map(pow2);
    empty_mapped_stack = stack.map(zero);

    //assert
    EXPECT_EQ(mapped_stack->size(), 10);
    EXPECT_EQ(empty_mapped_stack->size(), 10);
    for(int i = 0; i < 10; i++) {
        EXPECT_EQ(mapped_stack->pop(), (10 - i) * (10 - i));
        EXPECT_EQ(empty_mapped_stack->pop(), 0);
    }
    EXPECT_TRUE(mapped_stack->empty());
    EXPECT_TRUE(empty_mapped_stack->empty());
    delete mapped_stack;
    delete empty_mapped_stack;
}

TEST(Stack, split) {
    //arrange
    Stack<int> stack;
    pair<Stack<int>**, int> result_of_splitting;
    Stack<int> **splitted_stack;
    int splitted_stack_size;

    //act
    stack.push(5);
    stack.push(10);
    stack.push(5);
    stack.push(10);
    stack.push(5);
    result_of_splitting = stack.split(10);
    splitted_stack = result_of_splitting.first;
    splitted_stack_size = result_of_splitting.second;

    //assert
    EXPECT_EQ(splitted_stack_size, 3);
    for(int i = 0; i != splitted_stack_size; ++i) {
        EXPECT_EQ(splitted_stack[i]->size(), 1);
        EXPECT_EQ(splitted_stack[i]->pop(), 5);
        EXPECT_TRUE(splitted_stack[i]->empty());
        delete splitted_stack[i];
    }
    delete[] splitted_stack;
}

TEST(Stack, splitEmptyStack) {
    //arrange
    Stack<int> stack;
    pair<Stack<int>**, int> result_of_splitting;
    Stack<int> **splitted_stack;
    int splitted_stack_size;

    //act
    result_of_splitting = stack.split(10);
    splitted_stack = result_of_splitting.first;
    splitted_stack_size = result_of_splitting.second;

    //assert
    EXPECT_EQ(splitted_stack_size, 1);
    EXPECT_EQ(splitted_stack[0]->size(), 0);
    delete splitted_stack[0];
    delete[] splitted_stack;
}

TEST(Stack, splitStackWithoutDelimiter) {
    //arrange
    Stack<int> stack;
    pair<Stack<int>**, int> result_of_splitting;
    Stack<int> **splitted_stack;
    int splitted_stack_size;
    //act
    stack.push(5);
    stack.push(10);
    stack.push(5);
    stack.push(10);
    result_of_splitting = stack.split(1000);
    splitted_stack = result_of_splitting.first;
    splitted_stack_size = result_of_splitting.second;
    //assert
    EXPECT_EQ(splitted_stack_size, 1);
    EXPECT_EQ(splitted_stack[0]->size(), 4);
    EXPECT_EQ(splitted_stack[0]->pop(), 10);
    EXPECT_EQ(splitted_stack[0]->pop(), 5);
    EXPECT_EQ(splitted_stack[0]->pop(), 10);
    EXPECT_EQ(splitted_stack[0]->pop(), 5);
    EXPECT_TRUE(splitted_stack[0]->empty());
    for(int i = 0; i != splitted_stack_size; ++i)
        delete splitted_stack[i];
    delete[] splitted_stack;
}

TEST(Stack, Where) {
    //arrange
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stack<int> stack(10, values);

    Stack<int>* evens = stack.where([](const int &x) { return x % 2 == 0; });
    EXPECT_EQ(evens->size(), 5);
    EXPECT_EQ(evens->pop(), 10);
    EXPECT_EQ(evens->pop(), 8);
    delete evens;

    Stack<int>* odds = stack.where([](const int &x) { return x % 2 == 1; });
    EXPECT_EQ(odds->size(), 5);
    EXPECT_EQ(odds->pop(), 9);
    EXPECT_EQ(odds->pop(), 7);
    delete odds;

    Stack<int>* all = stack.where([](const int &x) { return true; });
    EXPECT_EQ(all->size(), 10);
    EXPECT_EQ(all->pop(), 10);
    EXPECT_EQ(all->pop(), 9);
    delete all;

    Stack<int>* none = stack.where([](const int &x) { return false; });
    EXPECT_EQ(none->size(), 0);
    delete none;

    Stack<int>* empty = Stack<int>().where([](const int &x) { return true; });
    EXPECT_EQ(empty->size(), 0);
    delete empty;
}




