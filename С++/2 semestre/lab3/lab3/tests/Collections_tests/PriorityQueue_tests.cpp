#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "Collections/PriorityQueue.hpp"
#include "Options.hpp"
#include "gtest/gtest.h"
#include <string>

using namespace std;
using namespace lab2;
using namespace lab3;

TEST(PriorityQueue, DefaultConstructor) {
    //arrange
    PriorityQueue<int> pq;
    //act

    //assert
    EXPECT_EQ(pq.size(), 0);
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, ConstructorWithSize) {
    //arrange
    PriorityQueue<int> pq(10, 1);
    //act

    //assert
    EXPECT_EQ(pq.size(), 10);
    for(int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq.top(), make_pair(0, 1));
        pq.pop();
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, ConstructorWithSizeAndItem) {
    //arrange
    PriorityQueue<int> pq(10, 22, 1);
    //act

    //assert
    EXPECT_EQ(pq.size(), 10);
    for(int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq.top(), make_pair(22, 1));
        pq.pop();
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, ConstructorWithSizeAndArray) {
    //arrange
    pair<int, int> reverse[10] = {make_pair(0, 10), make_pair(1, 9),
                                   make_pair(2, 8), make_pair(3, 7),
                                   make_pair(4, 6),make_pair(5, 5),
                                   make_pair(6, 4), make_pair(7, 3),
                                   make_pair(8, 2), make_pair(9, 1)};
    PriorityQueue<int> pq(10, reverse);
    //act

    //assert
    EXPECT_EQ(pq.size(), 10);
    for(int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq.top(), make_pair(9-i, i + 1));
        pq.pop();
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, ConstructorWithDynamicArray) {
    //arrange
    DynamicArray<pair<int, int>> array(7);
    array[0] = make_pair(6, 8);
    array[1] = make_pair(5, 7);
    array[2] = make_pair(14, 16);
    array[3] = make_pair(4, 7);
    array[4] = make_pair(22, 33);
    array[5] = make_pair(3, 5);
    array[6] = make_pair(2, 4);
    PriorityQueue<int> pq(array);

    //act

    //assert
    EXPECT_EQ(pq.size(), 7);
    EXPECT_EQ(pq.top(), make_pair(2, 4));
    EXPECT_EQ(pq.pop(), 2);
    EXPECT_EQ(pq.top(), make_pair(3, 5));
    EXPECT_EQ(pq.pop(), 3);
    EXPECT_EQ(pq.top(), make_pair(5, 7));
    EXPECT_EQ(pq.pop(), 5);
    EXPECT_EQ(pq.top(), make_pair(4, 7));
    EXPECT_EQ(pq.pop(), 4);
    EXPECT_EQ(pq.top(), make_pair(6, 8));
    EXPECT_EQ(pq.pop(), 6);
    EXPECT_EQ(pq.top(), make_pair(14, 16));
    EXPECT_EQ(pq.pop(), 14);
    EXPECT_EQ(pq.top(), make_pair(22, 33));
    EXPECT_EQ(pq.pop(), 22);
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, ConstructorWithLinkedList) {
    //arrange
    LinkedList<pair<int, int>> list;
    list.PushBack(make_pair(6, 8));
    list.PushBack(make_pair(5, 7));
    list.PushBack(make_pair(14, 16));
    list.PushBack(make_pair(4, 7));
    list.PushBack(make_pair(22, 33));
    list.PushBack(make_pair(3, 5));
    list.PushBack(make_pair(2, 4));
    PriorityQueue<int> pq(list);

    //act

    //assert
    EXPECT_EQ(pq.size(), 7);
    EXPECT_EQ(pq.top(), make_pair(2, 4));
    EXPECT_EQ(pq.pop(), 2);
    EXPECT_EQ(pq.top(), make_pair(3, 5));
    EXPECT_EQ(pq.pop(), 3);
    EXPECT_EQ(pq.top(), make_pair(5, 7));
    EXPECT_EQ(pq.pop(), 5);
    EXPECT_EQ(pq.top(), make_pair(4, 7));
    EXPECT_EQ(pq.pop(), 4);
    EXPECT_EQ(pq.top(), make_pair(6, 8));
    EXPECT_EQ(pq.pop(), 6);
    EXPECT_EQ(pq.top(), make_pair(14, 16));
    EXPECT_EQ(pq.pop(), 14);
    EXPECT_EQ(pq.top(), make_pair(22, 33));
    EXPECT_EQ(pq.pop(), 22);
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, ConstructorWithSequence) {
    //arrange
    LinkedList<pair<int, int>> list;
    list.PushBack(make_pair(6, 8));
    list.PushBack(make_pair(5, 7));
    list.PushBack(make_pair(14, 16));
    list.PushBack(make_pair(4, 7));
    list.PushBack(make_pair(22, 33));
    list.PushBack(make_pair(3, 5));
    list.PushBack(make_pair(2, 4));
    Sequence<pair<int, int>> *seq = new ListSequence<pair<int, int>>(list);
    PriorityQueue<int> pq(seq);

    //act

    //assert
    EXPECT_EQ(pq.size(), 7);
    EXPECT_EQ(pq.top(), make_pair(2, 4));
    EXPECT_EQ(pq.pop(), 2);
    EXPECT_EQ(pq.top(), make_pair(3, 5));
    EXPECT_EQ(pq.pop(), 3);
    EXPECT_EQ(pq.top(), make_pair(5, 7));
    EXPECT_EQ(pq.pop(), 5);
    EXPECT_EQ(pq.top(), make_pair(4, 7));
    EXPECT_EQ(pq.pop(), 4);
    EXPECT_EQ(pq.top(), make_pair(6, 8));
    EXPECT_EQ(pq.pop(), 6);
    EXPECT_EQ(pq.top(), make_pair(14, 16));
    EXPECT_EQ(pq.pop(), 14);
    EXPECT_EQ(pq.top(), make_pair(22, 33));
    EXPECT_EQ(pq.pop(), 22);
    EXPECT_TRUE(pq.empty());
    delete seq;
}

TEST(PriorityQueue, CopyConstructor) {
    //arrange
    pair<string, int> items[10] = {make_pair("1", 10), make_pair("2", 9),
                                   make_pair("3", 8), make_pair("4", 7),
                                   make_pair("5", 6),make_pair("6", 5),
                                   make_pair("7", 4), make_pair("8", 3),
                                   make_pair("9", 2), make_pair("10", 1)};
    PriorityQueue<string> pq1(10, items);

    //act
    PriorityQueue<string> pq2(pq1);

    //assert
    EXPECT_EQ(pq1.size(), pq2.size());
    for(int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq1.pop(), pq2.pop());
    }
    EXPECT_TRUE(pq1.empty());
    EXPECT_TRUE(pq2.empty());
}

TEST(PriorityQueue, Destructor) {
    //arrange
    auto *pq = new PriorityQueue<int>();
    //act
    pq->push(1, 1);
    pq->push(2, 2);
    pq->push(3, 3);
    pq->push(4, 4);
    pq->push(5, 5);
    //assert
    delete pq;
}

TEST(PriorityQueue, Push) {
    //arrange
    PriorityQueue<int> pq;
    //act
    pq.push(1, 1);
    pq.push(2, 2);
    pq.push(3, 3);
    pq.push(4, 4);
    pq.push(5, 5);
    //assert
    EXPECT_EQ(pq.size(), 5);
    EXPECT_FALSE(pq.empty());
    for(int i = 0; i != 5; ++i) {
        EXPECT_EQ(pq.pop(), i + 1);
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, Pop) {
    //arrange
    pair<int, int> items[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq(10, items);
    //act

    //assert
    for(int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq.pop(), 10-i);
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, EmptyPop) {
    //arrange
    PriorityQueue<int> pq;
    //act

    //assert
    EXPECT_THROW(pq.pop(), out_of_range);
}

TEST(PriorityQueue, tryPop) {
//arrange
    pair<int, int> items[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq(10, items);
    //act

    //assert
    for(int i = 0; i != 10; ++i) {
        Options<int> opt = pq.tryPop();
        EXPECT_EQ(opt.Value(), 10-i);
    }
    EXPECT_TRUE(pq.empty());
}

TEST(PriorityQueue, EmptyTryPop) {
    //arrange
    PriorityQueue<int> pq;
    //act
    Options<int> opt = pq.tryPop();
    //assert
    EXPECT_FALSE(opt.HasValue());
}

TEST(PriorityQueue, Top) {
    //arrange
    pair<int, int> items[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq(10, items);
    //act

    //assert
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq.top(), make_pair(10 - i, i + 1));
        pq.pop();
    }
}

TEST(PriorityQueue, EmptyTop) {
    //arrange
    PriorityQueue<int> pq;
    //act

    //assert
    EXPECT_THROW(pq.top(), out_of_range);
}

TEST(PriorityQueue, tryTop) {
    //arrange
    pair<int, int> items[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq(10, items);
    //act

    //assert
    for (int i = 0; i != 10; ++i) {
        Options<pair<int, int>> opt = pq.tryTop();
        EXPECT_EQ(opt.Value(), make_pair(10 - i, i + 1));
        pq.pop();
    }
}

TEST(PriorityQueue, EmptyTryTop) {
    //arrange
    PriorityQueue<int> pq;
    //act
    Options<pair<int, int>> opt = pq.tryTop();
    //assert
    EXPECT_FALSE(opt.HasValue());
}

TEST(PriorityQueue, Bottom) {
    //arrange
    pair<int, int> items[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq(10, items);
    //act

    //assert
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq.bottom(), make_pair(1, 10));
        pq.pop();
    }
}

TEST(PriorityQueue, EmptyBottom) {
    //arrange
    PriorityQueue<int> pq;
    //act

    //assert
    EXPECT_THROW(pq.bottom(), out_of_range);
}

TEST(PriorityQueue, TryBottom) {
    //arrange
    pair<int, int> items[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq(10, items);
    //act

    //assert
    for (int i = 0; i != 10; ++i) {
        Options<pair<int, int>> opt = pq.tryBottom();
        EXPECT_EQ(opt.Value(), make_pair(1, 10));
        pq.pop();
    }
}

TEST(PriorityQueue, EmptyTryBottom) {
    //arrange
    PriorityQueue<int> pq;
    //act
    Options<pair<int, int>> opt = pq.tryBottom();
    //assert
    EXPECT_FALSE(opt.HasValue());
}

TEST(PriorityQueue, Concat) {
    //arrange
    pair<int, int> items1[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                 make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    pair<int, int> items2[10] = {make_pair(11, 20), make_pair(12, 19), make_pair(13, 18), make_pair(14, 17), make_pair(15, 16),
                                 make_pair(16, 15), make_pair(17, 14), make_pair(18, 13), make_pair(19, 12), make_pair(20, 11)};
    PriorityQueue<int> pq1(10, items1);
    PriorityQueue<int> pq2(10, items2);
    //act
    PriorityQueue<int> *pq3 = pq1.concat(pq2);

    //assert
    EXPECT_EQ(pq3->size(), 20);
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq3->top(), make_pair(10 - i, i + 1));
        pq3->pop();
    }

    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq3->top(), make_pair(20 - i, i + 11));
        pq3->pop();
    }
    EXPECT_TRUE(pq3->empty());
    delete pq3;
}

TEST(PriorityQueue, EmptyConcat) {
    //arrange
    PriorityQueue<int> pq1;
    PriorityQueue<int> pq2;
    //act
    PriorityQueue<int> *pq3 = pq1.concat(pq2);

    //assert
    EXPECT_TRUE(pq3->empty());
    delete pq3;
}

TEST(PriorityQueue, PlusEqual) {
    //arrange
    pair<int, int> items1[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                 make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq1(10, items1);

    //act
    PriorityQueue<int> *pq2 = pq1.concat(pq1);

    //assert
    EXPECT_EQ(pq2->size(), 20);
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq2->top(), make_pair(10 - i, i + 1));
        pq2->pop();
        EXPECT_EQ(pq2->top(), make_pair(10 - i, i + 1));
        pq2->pop();
    }
    EXPECT_TRUE(pq2->empty());
    delete pq2;
}

TEST(PriorityQueue, GetSubQueue) {
    //arrange
    pair<int, int> items1[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                 make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq1(10, items1);

    //act
    PriorityQueue<int> *pq2 = pq1.getSubQueue(5 , 8);

    //assert
    EXPECT_EQ(pq2->size(), 4);
    EXPECT_EQ(pq2->top(), make_pair(9, 2));
    pq2->pop();
    EXPECT_EQ(pq2->top(), make_pair(8, 3));
    pq2->pop();
    EXPECT_EQ(pq2->top(), make_pair(7, 4));
    pq2->pop();
    EXPECT_EQ(pq2->top(), make_pair(6, 5));
    pq2->pop();
    EXPECT_TRUE(pq2->empty());
    delete pq2;
}

TEST(PriorityQueue, OneGetSubQueue) {
    //arrange
    PriorityQueue<int> pq1;
    for(int i = 0; i != 10; ++i){
        pq1.push(i, i);
    }

    //act
    PriorityQueue<int> *pq2 = pq1.getSubQueue(9, 9);

    //assert
    EXPECT_TRUE(pq2->size() == 1);
    EXPECT_EQ(pq2->top(), make_pair(9, 9));
    pq2->pop();
    EXPECT_TRUE(pq2->empty());
    delete pq2;
}

TEST(PriorityQueue, InvalidGetSubQueue) {
    //arrange
    PriorityQueue<int> pq1;
    for(int i = 0; i != 10; ++i){
        pq1.push(i, i);
    }

    //act & assert
    EXPECT_THROW(pq1.getSubQueue(9, 8), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(10, 10), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(-1, 0), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(0, -1), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(10, 9), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(-1, 9), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(0, 10), out_of_range);
    EXPECT_THROW(pq1.getSubQueue(1, 0), out_of_range);
}

TEST(PriorityQueue, OperatorPlus) {
    //arrange
    pair<int, int> items1[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                 make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    pair<int, int> items2[10] = {make_pair(11, 20), make_pair(12, 19), make_pair(13, 18), make_pair(14, 17), make_pair(15, 16),
                                 make_pair(16, 15), make_pair(17, 14), make_pair(18, 13), make_pair(19, 12), make_pair(20, 11)};
    PriorityQueue<int> pq1(10, items1);
    PriorityQueue<int> pq2(10, items2);

    //act
    PriorityQueue<int> *pq3 = pq1 + pq2;

    //assert
    EXPECT_EQ(pq3->size(), 20);
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq3->top(), make_pair(10 - i, i + 1));
        pq3->pop();
    }

    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq3->top(), make_pair(20 - i, i + 11));
        pq3->pop();
    }
    EXPECT_TRUE(pq3->empty());
    delete pq3;
}

TEST(PriorityQueue, EmptyOperatorPlus) {
    //arrange
    PriorityQueue<int> pq1;
    PriorityQueue<int> pq2;

    //act
    PriorityQueue<int> *pq3 = pq1 + pq2;

    //assert
    EXPECT_TRUE(pq3->empty());
    delete pq3;
}

TEST(PriorityQueue, OperatorPlusEqual) {
    //arrange
    pair<int, int> items1[10] = {make_pair(1, 10), make_pair(2, 9), make_pair(3, 8), make_pair(4, 7), make_pair(5, 6),
                                 make_pair(6, 5), make_pair(7, 4), make_pair(8, 3), make_pair(9, 2), make_pair(10, 1)};
    PriorityQueue<int> pq1(10, items1);

    //act
    PriorityQueue<int> *pq3 = pq1 + pq1;

    //assert
    EXPECT_EQ(pq3->size(), 20);
    for (int i = 0; i != 10; ++i) {
        EXPECT_EQ(pq3->top(), make_pair(10 - i, i + 1));
        pq3->pop();
        EXPECT_EQ(pq3->top(), make_pair(10 - i, i + 1));
        pq3->pop();
    }
    EXPECT_TRUE(pq3->empty());
    delete pq3;
}

TEST(PriorityQueue, Map) {
    //arrange
    auto pow2 = [](const int &x) { return x * x; };
    auto pow3 = [](const int &x) { return x * x * x; };
    PriorityQueue<int> pq1;
    for (int i = 0; i != 5; ++i) {
        pq1.push(i, i);
    }

    //act
    PriorityQueue<int> *pq2 = pq1.map(pow2);
    PriorityQueue<int> *pq3 = pq1.map(pow3);

    //assert
    EXPECT_EQ(pq2->size(), 5);
    EXPECT_EQ(pq3->size(), 5);
    for (int i = 0; i != 5; ++i) {
        EXPECT_EQ(pq2->top(), make_pair(i * i, i));
        pq2->pop();
        EXPECT_EQ(pq3->top(), make_pair(i * i * i, i));
        pq3->pop();
    }
    delete pq2;
    delete pq3;
}

TEST(PriorityQueue, EmptyMap) {
    //arrange
    auto pow2 = [](const int &x) { return x * x; };
    PriorityQueue<int> pq1;

    //act
    PriorityQueue<int> *pq2 = pq1.map(pow2);

    //assert
    EXPECT_TRUE(pq2->empty());
    delete pq2;
}

TEST(PriorityQueue, Split) {
    //arrange
    PriorityQueue<int> pq1;
    pq1.push(1, 1);
    pq1.push(2, 2);
    pq1.push(3, 3);
    pq1.push(1, 1);
    pq1.push(5, 5);
    pq1.push(6, 6);
    pq1.push(1, 1);
    pq1.push(8, 8);
    pq1.push(1, 1);

    //act
    pair<PriorityQueue<int> **, int> splitted_pair = pq1.split(make_pair(1, 1));
    auto **splitted_queues = splitted_pair.first;
    int splitted_queues_size = splitted_pair.second;

    //assert
    EXPECT_EQ(splitted_queues_size, 5);
    EXPECT_EQ(splitted_queues[0]->size(), 0);
    EXPECT_EQ(splitted_queues[1]->size(), 2);
    EXPECT_EQ(splitted_queues[2]->size(), 2);
    EXPECT_EQ(splitted_queues[3]->size(), 1);
    EXPECT_EQ(splitted_queues[4]->size(), 0);
    EXPECT_EQ(splitted_queues[1]->top(), make_pair(2, 2));
    splitted_queues[1]->pop();
    EXPECT_EQ(splitted_queues[1]->top(), make_pair(3, 3));
    splitted_queues[1]->pop();
    EXPECT_EQ(splitted_queues[2]->top(), make_pair(5, 5));
    splitted_queues[2]->pop();
    EXPECT_EQ(splitted_queues[2]->top(), make_pair(6, 6));
    splitted_queues[2]->pop();
    EXPECT_EQ(splitted_queues[3]->top(), make_pair(8, 8));
    splitted_queues[3]->pop();
    for(int i = 0; i != 5; ++i) {
        EXPECT_TRUE(splitted_queues[i]->empty());
        delete splitted_queues[i];
    }
    delete[] splitted_queues;
}

TEST(PriorityQueue, EmptySplit) {
    //arrange
    PriorityQueue<int> pq1;

    //act
    pair<PriorityQueue<int> **, int> splitted_pair = pq1.split(make_pair(1, 1));
    auto **splitted_queues = splitted_pair.first;
    int splitted_queues_size = splitted_pair.second;

    //assert
    EXPECT_EQ(splitted_queues_size, 1);
    EXPECT_EQ(splitted_queues[0]->size(), 0);
    EXPECT_TRUE(splitted_queues[0]->empty());
    delete splitted_queues[0];
    delete[] splitted_queues;
}

TEST(PriorityQueue, where) {
    //arrange
    auto is_even = [](const int &x) { return x % 2 == 0; };
    PriorityQueue<int> pq1;
    for (int i = 0; i != 10; ++i) {
        pq1.push(i, i);
    }

    //act
    PriorityQueue<int> *pq2 = pq1.where(is_even);

    //assert
    EXPECT_EQ(pq2->size(), 5);
    for (int i = 0; i != 5; ++i) {
        EXPECT_EQ(pq2->top(), make_pair(i * 2, i * 2));
        pq2->pop();
    }
    delete pq2;
}

TEST(PriorituQueue, SplitWithoutDelim) {
    //arrange
    PriorityQueue<int> pq1;
    pq1.push(1, 1);
    pq1.push(2, 2);
    pq1.push(3, 3);
    pq1.push(1, 1);
    pq1.push(5, 5);
    pq1.push(6, 6);
    pq1.push(1, 1);
    pq1.push(8, 8);
    pq1.push(1, 1);

    //act
    pair<PriorityQueue<int> **, int> splitted_pair = pq1.split(make_pair(10, 10));
    auto **splitted_queues = splitted_pair.first;
    int splitted_queues_size = splitted_pair.second;

    //assert
    EXPECT_EQ(splitted_queues_size, 1);
    EXPECT_EQ(splitted_queues[0]->size(), 9);
    EXPECT_EQ(splitted_queues[0]->top(), make_pair(1, 1));
    splitted_queues[0]->pop();
    EXPECT_EQ(splitted_queues[0]->top(), make_pair(1, 1));
    splitted_queues[0]->pop();
    EXPECT_EQ(splitted_queues[0]->bottom(), make_pair(8, 8));
    delete splitted_queues[0];
    delete[] splitted_queues;
}

TEST(PriorityQueue, BaseReduce) {
    //arrange
    PriorityQueue<int> pq(10, 1);
    auto add = [](const pair<int, int> &a, const pair<int, int> &b) { return make_pair(a.first + b.first, a.second + b.second); };

    //act
    pair<int, int> result = pq.reduce(add);

    //assert
    EXPECT_EQ(result, make_pair(0, 10));
}

TEST(PriorityQueue, EmptyBaseReduce) {
    //arrange
    PriorityQueue<int> pq0;
    PriorityQueue<int> pq1(1, 1);
    PriorityQueue<int> pq2(2, 1);
    auto add = [](const pair<int, int> &a, const pair<int, int> &b) { return make_pair(a.first + b.first, a.second + b.second); };

    //act & assert
    EXPECT_THROW(pq0.reduce(add), invalid_argument);
    EXPECT_THROW(pq1.reduce(add), invalid_argument);
    EXPECT_EQ(pq2.reduce(add), make_pair(0, 2));
}

TEST(PriorityQueue, OwnReduce) {
    //arrange
    auto add = [] (const string &a, const string &b) { return a + b; };
    pair<string, int> array_for_constructor[3] = {{"Hello", 1}, {", ", 2}, {"world!", 3}};
    PriorityQueue<string> pq(3, array_for_constructor);

    //act
    string result = pq.reduce(add);

    //assert
    EXPECT_EQ(result, "Hello, world!");
}

TEST(PriorityQueue, EmptyOneAndTwoOwnReduce) {
    //arrange
    PriorityQueue<int> pq;
    PriorityQueue<int> pq1(1, 1);
    PriorityQueue<int> pq2(2, 1);
    auto add = [](const int &a, const int &b) { return a + b; };

    //act & assert
    EXPECT_THROW(pq.reduce(add), invalid_argument);
    EXPECT_THROW(pq1.reduce(add), invalid_argument);
    EXPECT_EQ(pq2.reduce(add), 0);
}