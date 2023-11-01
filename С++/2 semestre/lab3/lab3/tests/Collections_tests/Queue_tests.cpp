#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "Collections/Queue.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace lab2;
using namespace lab3;

TEST(Queue, DefaultConstructor) {
    //arrange
    Queue<int> queue;

    //assert
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.empty());
}

TEST(Queue, ConstructorWithSize){
    //arrange
    Queue<int> queue(5);

    //assert
    EXPECT_EQ(queue.size(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(queue.pop(), 0);
    }
}

TEST(Queue, ConstructorWithSizeAndItem) {
    //arrange
    Queue<int> queue(5, 5);

    //assert
    EXPECT_EQ(queue.size(), 5);
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(queue.pop(), 5);
    }
}

TEST(Queue, ConstructorWithSizeAndArray) {
    //arrange
    int array[5] = {1, 2, 3, 4, 5};
    //act
    Queue<int> queue(5, array);
    //assert
    EXPECT_EQ(queue.size(), 5);
    for(int i : array) {
        EXPECT_EQ(queue.pop(), i);
    }
}

TEST(Queue, ConstructorWithDynamicArray) {
    //arrange
    int array[5] = {1, 2, 3, 4, 5};
    DynamicArray<int> dynamicArray(5, array);
    //act
    Queue<int> queue(dynamicArray);
    //assert
    EXPECT_EQ(queue.size(), 5);
    for(int i : array) {
        EXPECT_EQ(queue.pop(), i);
    }
}

TEST(Queue, ConstructorWithLinkedList) {
    //arrange
    int array[5] = {1, 2, 3, 4, 5};
    LinkedList<int> linkedList(5, array);
    //act
    Queue<int> queue(linkedList);
    //assert
    EXPECT_EQ(queue.size(), 5);
    for(int i : array) {
        EXPECT_EQ(queue.pop(), i);
    }
}

TEST(Queue, ConstructorWithSequence) {
    //arrange
    int array[5] = {1, 2, 3, 4, 5};
    Sequence<int> *sequence = new ListSequence<int>(5, array);
    //act
    Queue<int> queue(sequence);
    //assert
    EXPECT_EQ(queue.size(), 5);
    for(int i : array) {
        EXPECT_EQ(queue.pop(), i);
    }
    delete sequence;
}

TEST(Queue, Destructor) {
    //arrange
    int array[5] = {1, 2, 3, 4, 5};
    //act
    auto *queue = new Queue<int>(5, array);
    //assert
    EXPECT_EQ(queue->size(), 5);
    for(int i : array) {
        EXPECT_EQ(queue->pop(), i);
    }
    delete queue;
}

TEST(Queue, Push) {
    //arrange
    Queue<int> queue;
    //act&assert
    queue.push(1);
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 1);
    queue.push(2);
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 2);
    queue.push(3);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.front(), 1);
    EXPECT_EQ(queue.back(), 3);
}

TEST(Queue, Pop) {
    //arrange
    Queue<int> queue;
    //act
    queue.push(1);
    queue.push(2);
    queue.push(3);
    //assert
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.pop(), 1);

    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.pop(), 2);

    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.pop(), 3);

    EXPECT_EQ(queue.size(), 0);
}

TEST(Queue, PopEmpty) {
    //arrange
    Queue<int> queue;
    //act&assert
    EXPECT_THROW(queue.pop(), out_of_range);
}

TEST(Queue, tryPop) {
    //arrange
    Queue<int> queue;
    Options<int> options;

    //act
    queue.push(1);
    queue.push(2);
    queue.push(3);

    //assert
    options = queue.tryPop();
    EXPECT_TRUE(options.HasValue());
    EXPECT_EQ(options.Value(), 1);
    options = queue.tryPop();
    EXPECT_TRUE(options.HasValue());
    EXPECT_EQ(options.Value(), 2);
    options = queue.tryPop();
    EXPECT_TRUE(options.HasValue());
    EXPECT_EQ(options.Value(), 3);
    EXPECT_TRUE(queue.empty());
}

TEST(Queue, tryPopEmpty) {
    //arrange
    Queue<int> queue;
    Options<int> options;

    //act&assert
    options = queue.tryPop();
    EXPECT_FALSE(options.HasValue());
}

TEST(Queue, Front) {
    //arrange
    Queue<int> queue;
    //act
    queue.push(1);
    queue.push(2);
    queue.push(3);
    //assert
    EXPECT_EQ(queue.front(), 1);
    queue.pop();
    EXPECT_EQ(queue.front(), 2);
    queue.pop();
    EXPECT_EQ(queue.front(), 3);
    queue.pop();
}

TEST(Queue, FrontEmpty) {
    //arrange
    Queue<int> queue;
    //act&assert
    EXPECT_THROW(queue.front(), out_of_range);
}

TEST(Queue, tryFront) {
    //arrange
    Queue<int> queue;
    Options<int> options;

    //act
    queue.push(1);
    queue.push(2);
    queue.push(3);

    //assert
    options = queue.tryFront();
    EXPECT_TRUE(options.HasValue());
    EXPECT_EQ(options.Value(), 1);
    queue.pop();
    options = queue.tryFront();
    EXPECT_TRUE(options.HasValue());
    EXPECT_EQ(options.Value(), 2);
    queue.pop();
    options = queue.tryFront();
    EXPECT_TRUE(options.HasValue());
    EXPECT_EQ(options.Value(), 3);
    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(Queue, tryFrontEmpty) {
    //arrange
    Queue<int> queue;
    Options<int> options;

    //act&assert
    options = queue.tryFront();
    EXPECT_FALSE(options.HasValue());
}

TEST(Queue, Back) {
    //arrange
    Queue<int> queue;
    //act
    queue.push(1);
    queue.push(2);
    queue.push(3);
    //assert
    EXPECT_EQ(queue.back(), 3);
    queue.pop();
    EXPECT_EQ(queue.back(), 3);
    queue.pop();
    EXPECT_EQ(queue.back(), 3);
}

TEST(Queue, BackEmpty) {
    //arrange
    Queue<int> queue;
    //act&assert
    EXPECT_THROW(queue.back(), out_of_range);
}

TEST(Queue, tryBack) {
    //arrange
    Queue<int> queue;
    Options<int> options1;
    Options<int> options2;
    Options<int> options3;

    //act
    queue.push(1);
    queue.push(2);
    queue.push(3);

    //assert
    options1 = queue.tryBack();
    EXPECT_TRUE(options1.HasValue());
    EXPECT_EQ(options1.Value(), 3);
    queue.pop();
    options2 = queue.tryBack();
    EXPECT_TRUE(options2.HasValue());
    EXPECT_EQ(options2.Value(), 3);
    queue.pop();
    options3 = queue.tryBack();
    EXPECT_TRUE(options3.HasValue());
    EXPECT_EQ(options3.Value(), 3);
    queue.pop();
    EXPECT_TRUE(queue.empty());
}

TEST(Queue, tryBackEmpty) {
    //arrange
    Queue<int> queue;
    Options<int> options;

    //act&assert
    options = queue.tryBack();
    EXPECT_FALSE(options.HasValue());
}

TEST(Queue, Concat) {
    //arrange
    int arr_for_constructor1[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr_for_constructor2[10] = {11,12,13,14,15,16,17,18,19,20};
    Queue<int> queue1(10, arr_for_constructor1);
    Queue<int> queue2(10, arr_for_constructor2);

    //act
    Queue<int> *queue_result = queue1.concat(queue2);

    //assert
    EXPECT_EQ(queue_result->size(), 20);
    for(int i = 0; i < 20; i++)
        EXPECT_EQ(queue_result->pop(), i+1);
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, ConcatEmpty) {
    //arrange
    Queue<int> queue1;
    Queue<int> queue2;

    //act
    Queue<int> *queue_result = queue1.concat(queue2);

    //assert
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, GetSubQueue) {
    //arrange
    int arr_for_constructor[10] = {1,2,3,4,5,6,7,8,9,10};
    Queue<int> queue(10, arr_for_constructor);

    //act
    Queue<int> *queue_result = queue.getSubQueue(3, 7);

    //assert
    EXPECT_EQ(queue_result->size(), 5);
    for(int i = 0; i < 5; i++)
        EXPECT_EQ(queue_result->pop(), i+4);
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, OneGetSubQueue) {
    //arrange
    int arr_for_constructor[10] = {1,2,3,4,5,6,7,8,9,10};
    Queue<int> queue(10, arr_for_constructor);

    //act
    Queue<int> *queue_result = queue.getSubQueue(3, 3);

    //assert
    EXPECT_EQ(queue_result->size(), 1);
    EXPECT_EQ(queue_result->pop(), 4);
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, EmptyGetSubQueue) {
    //arrange
    Queue<int> queue;

    //act&assert
    EXPECT_THROW(queue.getSubQueue(0, 0), out_of_range);
}

TEST(Queue, OperatorPlus) {
    //arrange
    int arr_for_constructor1[10] = {1,2,3,4,5,6,7,8,9,10};
    int arr_for_constructor2[10] = {11,12,13,14,15,16,17,18,19,20};
    Queue<int> queue1(10, arr_for_constructor1);
    Queue<int> queue2(10, arr_for_constructor2);

    //act
    Queue<int> *queue_result = queue1 + queue2;

    //assert
    EXPECT_EQ(queue_result->size(), 20);
    for(int i = 0; i < 20; i++)
        EXPECT_EQ(queue_result->pop(), i+1);
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, OperatorPlusEmpty) {
    //arrange
    Queue<int> queue1;
    Queue<int> queue2;

    //act
    Queue<int> *queue_result = queue1 + queue2;

    //assert
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, ValidMap) {
    //arrange
    int arr_for_constructor[10] = {1,2,3,4,5,6,7,8,9,10};
    Queue<int> queue(10, arr_for_constructor);
    auto pow2 = [](const int &x){return x*x;};

    //act
    Queue<int> *queue_result = queue.map(pow2);

    //assert
    EXPECT_EQ(queue_result->size(), 10);
    for(int i = 0; i < 10; i++)
        EXPECT_EQ(queue_result->pop(), (i+1) * (i+1));
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, EmptyMap) {
    //arrange
    Queue<int> queue;
    auto pow2 = [](const int &x){return x*x;};

    //act
    Queue<int> *queue_result = queue.map(pow2);

    //assert
    EXPECT_TRUE(queue_result->empty());
    delete queue_result;
}

TEST(Queue, Split) {
    //arrange
    int arr_for_constructor[10] = {10, 5, 15, 25, 30, 5, 10 , 5};
    Queue<int> queue(8, arr_for_constructor);
    int delim = 5;
    std::pair<Queue<int>**, int> result;
    Queue<int> **result_queues;
    int result_queues_size;

    //act
    result = queue.split(delim);
    result_queues = result.first;
    result_queues_size = result.second;

    //assert
    EXPECT_EQ(result_queues_size, 4);
    EXPECT_EQ(result_queues[0]->size(), 1);
    EXPECT_EQ(result_queues[1]->size(), 3);
    EXPECT_EQ(result_queues[2]->size(), 1);
    EXPECT_EQ(result_queues[3]->size(), 0);
    EXPECT_EQ(result_queues[0]->pop(), 10);
    EXPECT_EQ(result_queues[1]->pop(), 15);
    EXPECT_EQ(result_queues[1]->pop(), 25);
    EXPECT_EQ(result_queues[1]->pop(), 30);
    EXPECT_EQ(result_queues[2]->pop(), 10);
    for(int i = 0; i != result_queues_size; ++i) {
        EXPECT_TRUE(result_queues[i]->empty());
        delete result_queues[i];
    }
    delete[] result_queues;
}

TEST(Queue, EmptySplit) {
    //arrange
    Queue<int> queue;
    int delim = 5;
    std::pair<Queue<int>**, int> result;
    Queue<int> **result_queues;
    int result_queues_size;

    //act
    result = queue.split(delim);
    result_queues = result.first;
    result_queues_size = result.second;

    //assert
    EXPECT_EQ(result_queues_size, 1);
    delete result_queues[0];
    delete[] result_queues;
}

TEST(Queue, SplitByEmptyDelim) {
    //arrange
    int arr_for_constructor[10] = {10, 5, 15, 25, 30, 5, 10 , 5};
    Queue<int> queue(8, arr_for_constructor);
    int delim = 0;
    std::pair<Queue<int>**, int> result;
    Queue<int> **result_queues;
    int result_queues_size;

    //act
    result = queue.split(delim);
    result_queues = result.first;
    result_queues_size = result.second;

    //assert
    EXPECT_EQ(result_queues_size, 1);
    EXPECT_EQ(result_queues[0]->size(), 8);
    for(int i = 0; i != 8; ++i) {
        EXPECT_EQ(result_queues[0]->pop(), arr_for_constructor[i]);
    }
    delete result_queues[0];
    delete[] result_queues;
}


TEST(Queue, Where) {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Queue<int> queue(10, values);

    Queue<int>* evens = queue.where([](const int &x) { return x % 2 == 0; });
    EXPECT_EQ(evens->size(), 5);
    EXPECT_EQ(evens->pop(), 2);
    EXPECT_EQ(evens->pop(), 4);
    delete evens;

    Queue<int>* odds = queue.where([](const int &x) { return x % 2 == 1; });
    EXPECT_EQ(odds->size(), 5);
    EXPECT_EQ(odds->pop(), 1);
    EXPECT_EQ(odds->pop(), 3);
    delete odds;

    Queue<int>* all = queue.where([](const int &x) { return true; });
    EXPECT_EQ(all->size(), 10);
    EXPECT_EQ(all->pop(), 1);
    EXPECT_EQ(all->pop(), 2);
    delete all;

    Queue<int>* none = queue.where([](const int &x) { return false; });
    EXPECT_EQ(none->size(), 0);
    delete none;

    Queue<int>* empty = Queue<int>().where([](const int &x) { return true; });
    EXPECT_EQ(empty->size(), 0);
    delete empty;
}




