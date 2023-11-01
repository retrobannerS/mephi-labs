#include <stdexcept>
#include <string>
#include "../UnitTest.hpp"
#include "../TestCluster.hpp"
#include "../../Data_Classes/LinkedList.hpp"

test::TestCluster LinkedListTests("LinkedList");

TEST(LinkedListTests, DefaultConstructor) {
    lab2::LinkedList<int> list;
    ASSERT(list.GetSize() == 0);
}
ADD_TEST(LinkedListTests, DefaultConstructor);

TEST(LinkedListTests, ConstructorWithSize) {
    lab2::LinkedList<int> list(5);
    ASSERT(list.GetSize() == 5);
    ASSERT(list[0] == 0);
    ASSERT(list.Get(1) == 0);
    bool flag = false;
    try {
        list.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, ConstructorWithSize);

TEST(LinkedListTests, ConstructorWithSizeAndValue) {
    lab2::LinkedList<int> list(5, 5);
    ASSERT(list.GetSize() == 5);
    ASSERT(list[0] == 5);
    ASSERT(list.Get(1) == 5);
    bool flag = false;
    try {
        list.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, ConstructorWithSizeAndValue);

TEST(LinkedListTests, ConstructorWithSizeAndArray) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::LinkedList<int> list(5, arr);
    ASSERT(list.GetSize() == 5);
    ASSERT(list[0] == 1);
    ASSERT(list.Get(1) == 2);
    bool flag = false;
    try {
        list.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, ConstructorWithSizeAndArray);

TEST(LinkedListTests, CopyConstructor) {
    lab2::LinkedList<std::string> list;
    for(int i = 0; i < 5; ++i) {
        list.PushBack("test" + std::to_string(i));
    }
    ASSERT(list.GetSize() == 5);
    lab2::LinkedList<std::string> list2(list);
    ASSERT(list2.GetSize() == 5);
    for(int i = 0; i < 5; ++i) {
        ASSERT(list2[i] == "test" + std::to_string(i));
    }
}
ADD_TEST(LinkedListTests, CopyConstructor);

TEST(LinkedListTests, Destructor) {
    auto *list = new lab2::LinkedList<std::string>();
    for(int i = 0; i < 5; ++i) {
        list->PushBack("test" + std::to_string(i));
    }
    ASSERT(list->GetSize() == 5);
    delete list;
}
ADD_TEST(LinkedListTests, Destructor);

TEST(LinkedListTests, GetFirst) {
    lab2::LinkedList<int> list(5, 5);
    ASSERT(list.GetFirst() == 5);
    list.PushBack(6);
    ASSERT(list.GetFirst() == 5);
    lab2::LinkedList<int> list2;
    bool flag = false;
    try {
        list2.GetFirst();
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, GetFirst);

TEST(LinkedListTests, GetLast) {
    lab2::LinkedList<int> list(5, 5);
    ASSERT(list.GetLast() == 5);
    list.PushBack(6);
    ASSERT(list.GetLast() == 6);
    lab2::LinkedList<int> list2;
    bool flag = false;
    try {
        list2.GetLast();
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, GetLast);

TEST(LinkedListTests, Get) {
    lab2::LinkedList<int> list(5, 5);
    ASSERT(list.Get(0) == 5);
    ASSERT(list.Get(1) == 5);
    bool flag = false;
    try {
        list.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, Get);

TEST(LinkedListTests, GetSize) {
    lab2::LinkedList<int> list(5, 5);
    ASSERT(list.GetSize() == 5);
    lab2::LinkedList<int> list2;
    ASSERT(list2.GetSize() == 0);
}
ADD_TEST(LinkedListTests, GetSize);

TEST(LinkedListTests, GetSubList) {
    lab2::LinkedList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.PushBack(i);
    }

    lab2::LinkedList<int> sublist = list.GetSubList(3, 7);

    ASSERT(sublist.GetSize() == 5);

    for (int i = 0; i < 5; ++i) {
        ASSERT(sublist.Get(i) == i + 3);
    }

    lab2::LinkedList<int> fullList = list.GetSubList(0, 9);

    ASSERT(fullList.GetSize() == 10);

    for (int i = 0; i < 10; ++i) {
        ASSERT(fullList.Get(i) == i);
    }
    lab2::LinkedList<int> oneElement = list.GetSubList(5, 5);

    ASSERT(oneElement.GetSize() == 1);

    ASSERT(oneElement.Get(0) == 5);

    bool flag = false;
    try {
        lab2::LinkedList<int> badSublist = list.GetSubList(-1, 11);
    } catch (const std::out_of_range& e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        lab2::LinkedList<int> badSublist = list.GetSubList(8, 3);
    } catch (const std::out_of_range& e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, GetSubList);

TEST(LinkedListTests, Set1) {
    lab2::LinkedList<int> list(5, 5);
    list.Set(0, 6);
    ASSERT(list[0] == 6);
    list.Set(1, 7);
    ASSERT(list[1] == 7);
    bool flag = false;
    try {
        list.Set(5, 8);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Set(-1, 9);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(list.Get(0) == 6);
    ASSERT(list.Get(1) == 7);
}
ADD_TEST(LinkedListTests, Set1);

TEST(LinkedListTests, Set2) {
    lab2::LinkedList<int> list(5, 5);
    list.Set(1, 3, 2);
    ASSERT(list[0] == 5);
    ASSERT(list[1] == 2);
    ASSERT(list[3] == 2);
    ASSERT(list.Get(4) == 5);
    ASSERT(list[4] == 5);
    bool flag = false;
    try {
        list.Set(10, 5, 22);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Set(-1, 5, 22);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Set(0, 15, 22);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, Set2);

TEST(LinkedListTests, PushBack) {
    lab2::LinkedList<int> list;
    list.PushBack(5);
    ASSERT(list.GetSize() == 1);
    ASSERT(list[0] == 5);
    list.PushBack(6);
    ASSERT(list.GetSize() == 2);
    ASSERT(list[1] == 6);
    bool flag = false;
    try {
        list.Get(2);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, PushBack);

TEST(LinkedListTests, PushFront) {
    lab2::LinkedList<int> list;
    list.PushFront(5);
    ASSERT(list.GetSize() == 1);
    ASSERT(list[0] == 5);
    list.PushFront(6);
    ASSERT(list.GetSize() == 2);
    ASSERT(list[0] == 6);
    ASSERT(list[1] == 5);
    bool flag = false;
    try {
        list.Get(2);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, PushFront);

TEST(LinkedListTests, InsertAt) {
    lab2::LinkedList<int> list;
    list.InsertAt(0, 5);
    ASSERT(list.GetSize() == 1);
    ASSERT(list[0] == 5);
    list.InsertAt(0, 6);
    ASSERT(list.GetSize() == 2);
    ASSERT(list[0] == 6);
    ASSERT(list[1] == 5);
    list.InsertAt(1, 7);
    ASSERT(list.GetSize() == 3);
    ASSERT(list[0] == 6);
    ASSERT(list[1] == 7);
    ASSERT(list[2] == 5);
    bool flag = false;
    try {
        list.InsertAt(4, 8);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.InsertAt(-1, 9);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, InsertAt);

TEST(LinkedListTests, PopFrom) {
    lab2::LinkedList<int> list;
    bool flag = false;
    try {
        list.PopFrom(0);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    list.PushBack(5);
    list.PushBack(6);
    list.PushBack(7);
    list.PushBack(8);
    list.PushBack(9);
    list.PopFrom(0);
    ASSERT(list.GetSize() == 4);
    ASSERT(list[0] == 6);
    ASSERT(list[1] == 7);
    ASSERT(list[2] == 8);
    ASSERT(list[3] == 9);
    list.PopFrom(2);
    ASSERT(list.GetSize() == 3);
    ASSERT(list[0] == 6);
    ASSERT(list[1] == 7);
    ASSERT(list[2] == 9);
    flag = false;
    try {
        list.PopFrom(3);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.PopFrom(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, PopFrom);

TEST(LinkedListTests, PopBack) {
    lab2::LinkedList<int> list;
    bool flag = false;
    try {
        list.PopBack();
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    list.PushBack(5);
    list.PushBack(6);
    list.PushBack(7);
    list.PushBack(8);
    list.PushBack(9);
    list.PopBack();
    ASSERT(list.GetSize() == 4);
    ASSERT(list[0] == 5);
    ASSERT(list[1] == 6);
    ASSERT(list[2] == 7);
    ASSERT(list[3] == 8);
    list.PopBack();
    ASSERT(list.GetSize() == 3);
    ASSERT(list[0] == 5);
    ASSERT(list[1] == 6);
    ASSERT(list[2] == 7);
}
ADD_TEST(LinkedListTests, PopBack);

TEST(LinkedListTests, PopFront) {
    lab2::LinkedList<int> list;
    bool flag = false;
    try {
        list.PopFront();
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    list.PushBack(5);
    list.PushBack(6);
    list.PushBack(7);
    list.PushBack(8);
    list.PushBack(9);
    list.PopFront();
    ASSERT(list.GetSize() == 4);
    ASSERT(list[0] == 6);
    ASSERT(list[1] == 7);
    ASSERT(list[2] == 8);
    ASSERT(list[3] == 9);
    list.PopFront();
    ASSERT(list.GetSize() == 3);
    ASSERT(list[0] == 7);
    ASSERT(list[1] == 8);
    ASSERT(list[2] == 9);
}
ADD_TEST(LinkedListTests, PopFront);

TEST(LinkedListTests, OperatorSquareBrackets) {
    lab2::LinkedList<int> list;
    list.PushBack(5);
    ASSERT(list[0] == 5);
    list.PushBack(6);
    ASSERT(list[1] == 6);
    bool flag = false;
    try {
        list[2];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list[-1];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, OperatorSquareBrackets);

TEST(LinkedListTests, OperatorEqual) {
    lab2::LinkedList<int> list;
    list.PushBack(5);
    list.PushBack(6);
    lab2::LinkedList<int> list2;
    list2 = list;
    ASSERT(list2.GetSize() == 2);
    ASSERT(list2[0] == 5);
    ASSERT(list2[1] == 6);
    bool flag = false;
    try {
        list2[2];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, OperatorEqual);

TEST(LinkedListTests, OperatorPlus) {
    lab2::LinkedList<int> list1;
    for (int i = 0; i < 5; ++i) {
        list1.PushBack(i);
    }

    lab2::LinkedList<int> list2;
    for (int i = 5; i < 10; ++i) {
        list2.PushBack(i);
    }

    lab2::LinkedList<int> concatList = list1 + list2;
    ASSERT(concatList.GetSize() == 10);
    for (int i = 0; i < 10; ++i) {
        ASSERT(concatList.Get(i) == i);
    }

    ASSERT(list1.GetSize() == 5);
    for (int i = 0; i < 5; ++i) {
        ASSERT(list1.Get(i) == i);
    }
    ASSERT(list2.GetSize() == 5);
    for (int i = 5; i < 10; ++i) {
        ASSERT(list2.Get(i - 5) == i);
    }

    lab2::LinkedList<int> list3;
    for (int i = 0; i < 5; ++i) {
        list3.PushBack(i);
    }
    list3 = list3 + list3;
    ASSERT(list3.GetSize() == 10);
    for (int i = 0; i < 10; ++i) {
        ASSERT(list3.Get(i) == i % 5);
    }

    lab2::LinkedList<int> list4;
    list4 = list4 + list4;
    ASSERT(list4.GetSize() == 0);

    lab2::LinkedList<int> list5;
    list5 = list5 + list4;
    ASSERT(list5.GetSize() == 0);
}
ADD_TEST(LinkedListTests, OperatorPlus);

TEST(LinkedListTests, Concat) {
    lab2::LinkedList<int> list1;
    for (int i = 0; i < 5; ++i) {
        list1.PushBack(i);
    }

    lab2::LinkedList<int> list2;
    for (int i = 5; i < 10; ++i) {
        list2.PushBack(i);
    }

    lab2::LinkedList<int> concatList = list1.Concat(list2);
    ASSERT(concatList.GetSize() == 10);
    for (int i = 0; i < 10; ++i) {
        ASSERT(concatList.Get(i) == i);
    }

    ASSERT(list1.GetSize() == 5);
    for (int i = 0; i < 5; ++i) {
        ASSERT(list1.Get(i) == i);
    }
    ASSERT(list2.GetSize() == 5);
    for (int i = 0; i < 5; ++i) {
        ASSERT(list2.Get(i) == i + 5);
    }

    lab2::LinkedList<int> emptyList;
    lab2::LinkedList<int> concatWithEmpty = list1.Concat(emptyList);
    ASSERT(concatWithEmpty.GetSize() == 5);
    for (int i = 0; i < 5; ++i) {
        ASSERT(concatWithEmpty.Get(i) == i);
    }

    lab2::LinkedList<int> emptyConcat = emptyList.Concat(emptyList);
    ASSERT(emptyConcat.GetSize() == 0);

    lab2::LinkedList<int> list;
    list.PushBack(5);
    list.PushBack(6);
    lab2::LinkedList<int> list3;
    list3.PushBack(7);
    list3.PushBack(8);
    auto tmp = list.Concat(list3);
    ASSERT(tmp.GetSize() == 4);
    ASSERT(tmp[0] == 5);
    bool flag = false;
    try {
        tmp[4];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        tmp[-1];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(LinkedListTests, Concat);
