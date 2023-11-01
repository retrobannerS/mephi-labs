#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "Collections/Deque.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace lab2;
using namespace lab3;

TEST(Deque, DefaultConstructor) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_EQ(deque.size(), 0);
    EXPECT_TRUE(deque.empty());
}

TEST(Deque, ConstructorWithSize) {
    //arrange
    Deque<int> deque(5);

    //act&assert
    EXPECT_EQ(deque.size(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(deque.popBack(), 0);
    }
}

TEST(Deque, ConstructorWithSizeAndItem) {
    //arrange
    Deque<int> deque(5, 1);

    //act&assert
    EXPECT_EQ(deque.size(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(deque.popBack(), 1);
    }
}

TEST(Deque, ConstructorWithSizeAndItems) {
    //arrange
    int items[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, items);

    //act&assert
    EXPECT_EQ(deque.size(), 5);
    for(int item : items) {
        EXPECT_EQ(deque.popFront(), item);
    }
}

TEST(Deque, ConstructorWithDynamicArray) {
    //arrange
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> array(5, items);
    Deque<int> deque(array);

    //act&assert
    EXPECT_EQ(deque.size(), 5);
    for(int item : items) {
        EXPECT_EQ(deque.popFront(), item);
    }
}

TEST(Deque, ConstructorWithLinkedList) {
    //arrange
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(5, items);
    Deque<int> deque(list);

    //act&assert
    EXPECT_EQ(deque.size(), 5);
    for(int item : items) {
        EXPECT_EQ(deque.popFront(), item);
    }
}

TEST(Deque, ConstructorWithSequence) {
    //arrange
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(5, items);
    Sequence<int> *sequence_for_test = new ListSequence<int>(list);
    Deque<int> deque(sequence_for_test);

    //act&assert
    EXPECT_EQ(deque.size(), 5);
    for(int item : items) {
        EXPECT_EQ(deque.popFront(), item);
    }
    delete sequence_for_test;
}

TEST(Deque, CopyConstructor) {
    //arrange
    int items[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, items);

    //act
    Deque<int> deque_copy1(deque);
    Deque<int> deque_copy2 = deque;

    //assert
    EXPECT_EQ(deque_copy1.size(), 5);
    EXPECT_EQ(deque_copy2.size(), 5);
    for(int item : items) {
        EXPECT_EQ(deque_copy1.popFront(), item);
        EXPECT_EQ(deque_copy2.popFront(), item);
    }
}

TEST(Deque, PushFront) {
    //arrange
    Deque<int> deque;
    //act&assert
    deque.pushFront(1);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.back(), 1);
    EXPECT_EQ(deque.front(), 1);
    deque.pushFront(2);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.back(), 1);
    EXPECT_EQ(deque.front(), 2);
    deque.pushFront(3);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque.back(), 1);
    EXPECT_EQ(deque.front(), 3);
}

TEST(Deque, PushBack) {
    //arrange
    Deque<int> deque;
    //act&assert
    deque.pushBack(1);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.back(), 1);
    EXPECT_EQ(deque.front(), 1);
    deque.pushBack(2);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.back(), 2);
    EXPECT_EQ(deque.front(), 1);
    deque.pushBack(3);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque.back(), 3);
    EXPECT_EQ(deque.front(), 1);
}

TEST(Deque, PopFront) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.popFront(), 1);
    EXPECT_EQ(deque.size(), 4);
    EXPECT_EQ(deque.popFront(), 2);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque.popFront(), 3);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.popFront(), 4);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.popFront(), 5);
    EXPECT_EQ(deque.size(), 0);
}

TEST(Deque, EmptyPopFront) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_THROW(deque.popFront(), out_of_range);
}

TEST(Deque, PopBack) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.popBack(), 5);
    EXPECT_EQ(deque.size(), 4);
    EXPECT_EQ(deque.popBack(), 4);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque.popBack(), 3);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.popBack(), 2);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.popBack(), 1);
    EXPECT_EQ(deque.size(), 0);
}

TEST(Deque, EmptyPopBack) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_THROW(deque.popBack(), out_of_range);
}

TEST(Deque, tryPopFront) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.tryPopFront().Value(), 1);
    EXPECT_EQ(deque.size(), 4);
    EXPECT_EQ(deque.tryPopFront().Value(), 2);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque.tryPopFront().Value(), 3);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.tryPopFront().Value(), 4);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.tryPopFront().Value(), 5);
    EXPECT_EQ(deque.size(), 0);
}

TEST(Deque, EmptyTryPopFront) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_EQ(deque.tryPopFront().HasValue(), false);
}

TEST(Deque, tryPopBack) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.tryPopBack().Value(), 5);
    EXPECT_EQ(deque.size(), 4);
    EXPECT_EQ(deque.tryPopBack().Value(), 4);
    EXPECT_EQ(deque.size(), 3);
    EXPECT_EQ(deque.tryPopBack().Value(), 3);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.tryPopBack().Value(), 2);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.tryPopBack().Value(), 1);
    EXPECT_EQ(deque.size(), 0);
}

TEST(Deque, EmptyTryPopBack) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_EQ(deque.tryPopBack().HasValue(), false);
}

TEST(Deque, Front) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.front(), 1);
    deque.popFront();
    EXPECT_EQ(deque.front(), 2);
    deque.popFront();
    EXPECT_EQ(deque.front(), 3);
    deque.popFront();
    EXPECT_EQ(deque.front(), 4);
    deque.popFront();
    EXPECT_EQ(deque.front(), 5);
    deque.popFront();
}

TEST(Deque, EmptyFront) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_THROW(deque.front(), out_of_range);
}

TEST(Deque, Back) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.back(), 5);
    deque.popBack();
    EXPECT_EQ(deque.back(), 4);
    deque.popBack();
    EXPECT_EQ(deque.back(), 3);
    deque.popBack();
    EXPECT_EQ(deque.back(), 2);
    deque.popBack();
    EXPECT_EQ(deque.back(), 1);
    deque.popBack();
}

TEST(Deque, EmptyBack) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_THROW(deque.back(), out_of_range);
}

TEST(Deque, TryFront) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.tryFront().Value(), 1);
    deque.popFront();
    EXPECT_EQ(deque.tryFront().Value(), 2);
    deque.popFront();
    EXPECT_EQ(deque.tryFront().Value(), 3);
    deque.popFront();
    EXPECT_EQ(deque.tryFront().Value(), 4);
    deque.popFront();
    EXPECT_EQ(deque.tryFront().Value(), 5);
    deque.popFront();
}

TEST(Deque, EmptyTryFront) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_EQ(deque.tryFront().HasValue(), false);
}

TEST(Deque, TryBack) {
    //arrange
    int array_for_constructor[] = {1, 2, 3, 4, 5};
    Deque<int> deque(5, array_for_constructor);

    //act&assert
    EXPECT_EQ(deque.tryBack().Value(), 5);
    deque.popBack();
    EXPECT_EQ(deque.tryBack().Value(), 4);
    deque.popBack();
    EXPECT_EQ(deque.tryBack().Value(), 3);
    deque.popBack();
    EXPECT_EQ(deque.tryBack().Value(), 2);
    deque.popBack();
    EXPECT_EQ(deque.tryBack().Value(), 1);
    deque.popBack();
}

TEST(Deque, EmptyTryBack) {
    //arrange
    Deque<int> deque;

    //act&assert
    EXPECT_EQ(deque.tryBack().HasValue(), false);
}

TEST(Deque, Split) {
    //arrange
    int array_for_constructor[] = {1, 20, 15, 10, 1, 4, 1};
    Deque<int> deque(7, array_for_constructor);

    //act
    pair<Deque<int> **, int> splitted_pair = deque.split(1);
    auto splitted_deques = splitted_pair.first;
    int splitted_deques_count = splitted_pair.second;

    //assert
    EXPECT_EQ(splitted_deques_count, 4);
    EXPECT_EQ(splitted_deques[0]->size(), 0);
    EXPECT_EQ(splitted_deques[1]->size(), 3);
    EXPECT_EQ(splitted_deques[2]->size(), 1);
    EXPECT_EQ(splitted_deques[3]->size(), 0);
    EXPECT_EQ(splitted_deques[1]->popFront(), 20);
    EXPECT_EQ(splitted_deques[1]->popFront(), 15);
    EXPECT_EQ(splitted_deques[1]->popFront(), 10);
    EXPECT_EQ(splitted_deques[2]->popFront(), 4);
    for(int i = 0; i != splitted_deques_count; ++i) {
        EXPECT_TRUE(splitted_deques[i]->empty());
        delete splitted_deques[i];
    }
    delete[] splitted_deques;
}

TEST(Deque, SplitEmpty) {
    //arrange
    Deque<int> deque;

    //act
    pair<Deque<int> **, int> splitted_pair = deque.split(1);
    auto splitted_deques = splitted_pair.first;
    int splitted_deques_count = splitted_pair.second;

    //assert
    EXPECT_EQ(splitted_deques_count, 1);
    EXPECT_TRUE(splitted_deques[0]->empty());
    delete splitted_deques[0];
    delete[] splitted_deques;
}

TEST(Deque, SplitWithNoDelim) {
    //arrange
    int array_for_constructor[] = {1, 20, 15, 10, 1, 4, 1};
    Deque<int> deque(7, array_for_constructor);

    //act
    pair<Deque<int> **, int> splitted_pair = deque.split(100);
    auto splitted_deques = splitted_pair.first;
    int splitted_deques_count = splitted_pair.second;

    //assert
    EXPECT_EQ(splitted_deques_count, 1);
    EXPECT_EQ(splitted_deques[0]->size(), 7);
    EXPECT_EQ(splitted_deques[0]->popFront(), 1);
    EXPECT_EQ(splitted_deques[0]->popFront(), 20);
    EXPECT_EQ(splitted_deques[0]->popFront(), 15);
    EXPECT_EQ(splitted_deques[0]->popFront(), 10);
    EXPECT_EQ(splitted_deques[0]->popFront(), 1);
    EXPECT_EQ(splitted_deques[0]->popFront(), 4);
    EXPECT_EQ(splitted_deques[0]->popFront(), 1);
    EXPECT_TRUE(splitted_deques[0]->empty());
    delete splitted_deques[0];
    delete[] splitted_deques;
}

TEST(Deque, where) {
    //arrange
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Deque<int> stack(10, values);

    Deque<int>* evens = stack.where([](const int &x) { return x % 2 == 0; });
    EXPECT_EQ(evens->size(), 5);
    EXPECT_EQ(evens->popBack(), 10);
    EXPECT_EQ(evens->popBack(), 8);
    delete evens;

    Deque<int>* odds = stack.where([](const int &x) { return x % 2 == 1; });
    EXPECT_EQ(odds->size(), 5);
    EXPECT_EQ(odds->popFront(), 1);
    EXPECT_EQ(odds->popFront(), 3);
    delete odds;

    Deque<int>* all = stack.where([](const int &x) { return true; });
    EXPECT_EQ(all->size(), 10);
    EXPECT_EQ(all->popBack(), 10);
    EXPECT_EQ(all->popBack(), 9);
    delete all;

    Deque<int>* none = stack.where([](const int &x) { return false; });
    EXPECT_EQ(none->size(), 0);
    delete none;

    Deque<int>* empty = Deque<int>().where([](const int &x) { return true; });
    EXPECT_EQ(empty->size(), 0);
    delete empty;
}




