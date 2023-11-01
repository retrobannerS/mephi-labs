#include <gtest/gtest.h>
#include "Algos/hanoi/hanoi.h"
using namespace lab3;


bool isStackOrdered(const Stack<int>& stack) {
    int lastItem = INT_MAX;
    for (auto& item : stack) {
        if (item > lastItem) {
            return false;
        }
        lastItem = item;
    }
    return true;
}

TEST(HanoiTest, TestHanoi) {
    Stack<int> stack1;
    Stack<int> stack2;
    Stack<int> stack3;

    for (int i = 5; i > 0; --i) {
        stack1.push(i);
    }

    hanoi(5, stack1, stack2, stack3);

    EXPECT_TRUE(stack1.empty());
    EXPECT_FALSE(stack2.empty());
    EXPECT_TRUE(stack3.empty());

    EXPECT_TRUE(isStackOrdered(stack2));
}

TEST(HanoiTest, Hanoi2) {
    lab3::hanoi2(5, 'a', 'b', 'c');
}

