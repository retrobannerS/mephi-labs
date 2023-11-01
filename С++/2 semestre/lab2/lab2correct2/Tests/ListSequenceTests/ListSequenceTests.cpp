#include <stdexcept>
#include "../../Options/Options.hpp"
#include "../UnitTest.hpp"
#include "../TestCluster.hpp"
#include "../../Data_Classes/LinkedList.hpp"
#include "../../Data_Classes/DynamicArray.hpp"
#include "../../Sequences/ArraySequence.hpp"
#include "../../Sequences/ListSequence.hpp"
#include "../../IEnumerators/IEnumerable.hpp"

test::TestCluster ListSequenceTests("ListSequenceTests");

TEST(ListSequenceTests, DefaultConstructor) {
    lab2::ListSequence<int> list;
    ASSERT(list.GetSize() == 0);
    list.PushFront(1);
    ASSERT(list.GetSize() == 1);
    ASSERT(list.GetFirst() == 1);
    ASSERT(list.GetLast() == 1);
    ASSERT(list.Get(0) == 1);
}
ADD_TEST(ListSequenceTests, DefaultConstructor);

TEST(ListSequenceTests, ConstructorWithSize) {
    lab2::ListSequence<int> list(5);
    ASSERT(list.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Get(i) == 0);
    }
    ASSERT(list.GetFirst() == 0);
    ASSERT(list.GetLast() == 0);
    list.PushBack(1);
    ASSERT(list.GetSize() == 6);
    ASSERT(list.GetLast() == 1);
}
ADD_TEST(ListSequenceTests, ConstructorWithSize);

TEST(ListSequenceTests, ConstructorWithSizeAndItem) {
    lab2::ListSequence<int> list(5, 5);
    ASSERT(list.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Get(i) == 5);
    }
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, ConstructorWithSizeAndItem);

TEST(ListSequenceTests, ConstructorWithSizeAndArray) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    ASSERT(list.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Get(i) == arr[i]);
    }
    ASSERT(list.GetFirst() == 1);
    ASSERT(list.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, ConstructorWithSizeAndArray);

TEST(ListSequenceTests, DestructorWithDynamicArray) {
    lab2::DynamicArray<int> arr(5, 5);
    lab2::ListSequence<int> list(arr);
    ASSERT(list.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Get(i) == 5);
    }
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, DestructorWithDynamicArray);

TEST(ListSequenceTests, ConstructorWithLinkedList) {
    lab2::LinkedList<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);
    lab2::ListSequence<int> list2(list);
    ASSERT(list2.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list2.Get(i) == i + 1);
    }
    ASSERT(list2.GetFirst() == 1);
    ASSERT(list2.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, ConstructorWithLinkedList);

TEST(ListSequenceTests, SeqConstructor) {
    auto *arr = new lab2::ArraySequence<int>(5, 5);
    lab2::ListSequence<int> list(arr);
    ASSERT(list.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Get(i) == 5);
    }
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
    delete arr;
}
ADD_TEST(ListSequenceTests, SeqConstructor);

TEST(ListSequenceTests, ConstructorWithArraySequence) {
    lab2::ArraySequence<int> arr(5, 5);
    lab2::ListSequence<int> list(arr);
    ASSERT(list.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Get(i) == 5);
    }
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, ConstructorWithArraySequence);

TEST(ListSequenceTests, CopyConstructor) {
    lab2::ListSequence<int> list(5, 5);
    lab2::ListSequence<int> list2 = list;
    ASSERT(list2.GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list2.Get(i) == 5);
    }
    ASSERT(list2.GetFirst() == 5);
    ASSERT(list2.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, CopyConstructor);

TEST(ListSequenceTests, Destructor) {
    auto *list = new lab2::ListSequence<int>(5, 5);
    ASSERT(list->GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list->Get(i) == 5);
    }
    ASSERT(list->GetFirst() == 5);
    ASSERT(list->GetLast() == 5);
    delete list;
}
ADD_TEST(ListSequenceTests, Destructor);

TEST(ListSequenceTests, GetFirst) {
    lab2::ListSequence<int> list1;
    bool flag = false;
    try {
        list1.GetFirst();
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ListSequence<int> list(5, 5);
    ASSERT(list.GetFirst() == 5);
}
ADD_TEST(ListSequenceTests, GetFirst);

TEST(ListSequenceTests, GetLast) {
    lab2::ListSequence<int> list1;
    bool flag = false;
    try {
        list1.GetLast();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ListSequence<int> list(5, 5);
    ASSERT(list.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, GetLast);

TEST(ListSequenceTests, TryGetFirst) {
    lab2::ListSequence<int> list1;
    lab2::Options<int> opt = list1.TryGetFirst();
    ASSERT(opt.HasValue() == false);
    ASSERT(opt.ValueOr(22) == 22);
    bool flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    opt = list.TryGetFirst();
    ASSERT(opt.HasValue() == true);
    ASSERT(opt.Value() == 1);
    ASSERT(opt.ValueOr(22) == 1);
}
ADD_TEST(ListSequenceTests, TryGetFirst);

TEST(ListSequenceTests, TryGetLast) {
    lab2::ListSequence<int> list1;
    lab2::Options<int> opt = list1.TryGetLast();
    ASSERT(opt.HasValue() == false);
    ASSERT(opt.ValueOr(22) == 22);
    bool flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    opt = list.TryGetLast();
    ASSERT(opt.HasValue() == true);
    ASSERT(opt.Value() == 5);
    ASSERT(opt.ValueOr(22) == 5);
}
ADD_TEST(ListSequenceTests, TryGetLast);

TEST(ListSequenceTests, Get) {
    lab2::ListSequence<int> list1;
    bool flag = false;
    try {
        list1.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ListSequence<int> list(5, 5);
    ASSERT(list.Get(0) == 5);
    ASSERT(list.Get(4) == 5);
    flag = false;
    try {
        list.Get(5);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, Get);

TEST(ListSequenceTests, TryGet) {
    lab2::ListSequence<int> list1;
    lab2::Options<int> opt = list1.TryGet(0);
    ASSERT(opt.HasValue() == false);
    ASSERT(opt.ValueOr(22) == 22);
    bool flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    opt = list.TryGet(0);
    ASSERT(opt.HasValue() == true);
    ASSERT(opt.Value() == 1);
    ASSERT(opt.ValueOr(22) == 1);
    opt = list.TryGet(4);
    ASSERT(opt.HasValue() == true);
    ASSERT(opt.Value() == 5);
    ASSERT(opt.ValueOr(22) == 5);
    opt = list.TryGet(5);
    ASSERT(opt.HasValue() == false);
    ASSERT(opt.ValueOr(22) == 22);
    opt = list.TryGet(-1);
    ASSERT(opt.HasValue() == false);
}
ADD_TEST(ListSequenceTests, TryGet);

TEST(ListSequenceTests, GetSize) {
    lab2::ListSequence<int> list;
    ASSERT(list.GetSize() == 0);
    lab2::ListSequence<int> list2(5, 5);
    ASSERT(list2.GetSize() == 5);
}
ADD_TEST(ListSequenceTests, GetSize);

TEST(ListSequenceTests, GetSubsequence) {
    lab2::ListSequence<int> list(5, 5);
    auto *list2 = dynamic_cast<lab2::ListSequence<int> *>(list.GetSubSequence(0, 4));
    ASSERT(list2->GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(list2->Get(i) == 5);
    }
    ASSERT(list2->GetFirst() == 5);
    ASSERT(list2->GetLast() == 5);
    delete list2;
    bool flag = false;
    try {
        list.GetSubSequence(0, 5);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.GetSubSequence(5, 0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.GetSubSequence(-1, 5);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.GetSubSequence(0, -1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.GetSubSequence(2, 0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, GetSubsequence);

TEST(ListSequenceTests, Set1) {
    lab2::ListSequence<int> list(5, 5);
    list.Set(0, 1);
    ASSERT(list.Get(0) == 1);
    list.Set(4, 1);
    ASSERT(list.Get(4) == 1);
    ASSERT(list.Get(1) == 5);
    ASSERT(list.Get(2) == 5);
    ASSERT(list.Get(3) == 5);
    bool flag = false;
    try {
        list.Set(5, 1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Set(-1, 1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, Set1);

TEST(ListSequenceTests, Set2) {
    lab2::ListSequence<int> list(10);
    list.Set(2, 3, 5);
    ASSERT(list.Get(0) == 0);
    ASSERT(list.Get(1) == 0);
    ASSERT(list.Get(2) == 5);
    ASSERT(list.Get(3) == 5);
    ASSERT(list.Get(4) == 5);
    ASSERT(list.Get(5) == 0);
    ASSERT(list.GetSize() == 10);
}
ADD_TEST(ListSequenceTests, Set2);

TEST(ListSequenceTests, PushBack) {
    lab2::ListSequence<int> list;
    list.PushBack(5);
    ASSERT(list.GetSize() == 1);
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
    list.PushBack(6);
    ASSERT(list.GetSize() == 2);
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 6);
    list.PushBack(7);
    ASSERT(list.GetSize() == 3);
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 7);
}
ADD_TEST(ListSequenceTests, PushBack);

TEST(ListSequenceTests, PushFront) {
    lab2::ListSequence<int> list;
    list.PushFront(5);
    ASSERT(list.GetSize() == 1);
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
    list.PushFront(6);
    ASSERT(list.GetSize() == 2);
    ASSERT(list.GetFirst() == 6);
    ASSERT(list.GetLast() == 5);
    list.PushFront(7);
    ASSERT(list.GetSize() == 3);
    ASSERT(list.GetFirst() == 7);
    ASSERT(list.GetLast() == 5);
}
ADD_TEST(ListSequenceTests, PushFront);

TEST(ListSequenceTests, InsertAt) {
    lab2::ListSequence<int> list;
    list.InsertAt(0, 5);
    ASSERT(list.GetSize() == 1);
    ASSERT(list.GetFirst() == 5);
    ASSERT(list.GetLast() == 5);
    list.InsertAt(0, 6);
    ASSERT(list.GetSize() == 2);
    ASSERT(list.GetFirst() == 6);
    ASSERT(list.GetLast() == 5);
    list.InsertAt(1, 7);
    ASSERT(list.GetSize() == 3);
    ASSERT(list.GetFirst() == 6);
    ASSERT(list.GetLast() == 5);
    ASSERT(list.Get(1) == 7);
    bool flag = false;
    try {
        list.InsertAt(4, 1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.InsertAt(-1, 1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, InsertAt);

TEST(ListSequenceTests, PopFront) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    list.PopFront();
    ASSERT(list.GetSize() == 4);
    for (int i = 0; i < 4; i++) {
        ASSERT(list.Get(i) == i + 2);
    }
    list.PopFront();
    ASSERT(list.GetSize() == 3);
    for (int i = 0; i < 3; i++) {
        ASSERT(list.Get(i) == i + 3);
    }
    list.PopFront();
    ASSERT(list.GetSize() == 2);
    for (int i = 0; i < 2; i++) {
        ASSERT(list.Get(i) == i + 4);
    }
    list.PopFront();
    ASSERT(list.GetSize() == 1);
    ASSERT(list.Get(0) == 5);

    list.PopFront();
    ASSERT(list.GetSize() == 0);
    bool flag = false;
    try {
        list.PopFront();
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, PopFront);

TEST(ListSequenceTests, PopBack) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    list.PopBack();
    ASSERT(list.GetSize() == 4);
    for (int i = 0; i < 4; i++) {
        ASSERT(list.Get(i) == i + 1);
    }
    list.PopBack();
    ASSERT(list.GetSize() == 3);
    for (int i = 0; i < 3; i++) {
        ASSERT(list.Get(i) == i + 1);
    }
    list.PopBack();
    ASSERT(list.GetSize() == 2);
    for (int i = 0; i < 2; i++) {
        ASSERT(list.Get(i) == i + 1);
    }
    list.PopBack();
    ASSERT(list.GetSize() == 1);
    ASSERT(list.Get(0) == 1);

    list.PopBack();
    ASSERT(list.GetSize() == 0);
    bool flag = false;
    try {
        list.PopBack();
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, PopBack);

TEST(ListSequenceTests, PopFrom) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    bool flag = false;
    try {
        list.PopFrom(-1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.PopFrom(5);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    list.PopFrom(0);
    ASSERT(list.GetSize() == 4);
    for (int i = 0; i < 4; i++) {
        ASSERT(list.Get(i) == i + 2);
    }
    list.PopFrom(1);
    ASSERT(list.GetSize() == 3);
    ASSERT(list.Get(0) == 2);
    ASSERT(list.Get(1) == 4);
    ASSERT(list.Get(2) == 5);
    list.PopFrom(2);
    ASSERT(list.GetSize() == 2);
    ASSERT(list.Get(0) == 2);
    ASSERT(list.Get(1) == 4);
    list.PopFrom(1);
    ASSERT(list.GetSize() == 1);
    ASSERT(list.Get(0) == 2);
    list.PopFrom(0);
    ASSERT(list.GetSize() == 0);
    flag = false;
    try {
        list.PopFrom(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.PopFrom(1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, PopFrom);

TEST(ListSequenceTests, OperatorIndex) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    ASSERT(list[0] == 1);
    ASSERT(list[1] == 2);
    ASSERT(list[2] == 3);
    ASSERT(list[3] == 4);
    ASSERT(list[4] == 5);
    bool flag = false;
    try {
        list[5];
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list[-1];
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    list[1] = 25;
    ASSERT(list.Get(1) == 25);
}
ADD_TEST(ListSequenceTests, OperatorIndex);

TEST(ListSequenceTests, OperatorEqual) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list1(5, arr);
    lab2::ListSequence<int> list2;
    list2 = list1;
    ASSERT(list1.GetSize() == list2.GetSize());
    for (int i = 0; i < 5; i++) {
        ASSERT(list1.Get(i) == list2.Get(i));
    }
    list1[0] = 25;
    ASSERT(list1[0] != list2[0]);
    ASSERT(list1.GetSize() == list2.GetSize());
    for (int i = 1; i < 5; i++) {
        ASSERT(list1.Get(i) == list2.Get(i));
    }
}
ADD_TEST(ListSequenceTests, OperatorEqual);

TEST(ListSequenceTests, OperatorPlus) {
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {6, 7, 8, 9, 10};
    lab2::ListSequence<int> list1(5, arr1);
    lab2::ListSequence<int> list2(5, arr2);
    lab2::Sequence<int> *list3 = list1 + list2;
    ASSERT(list3->GetSize() == 10);
    for (int i = 0; i < 10; i++) {
        ASSERT(list3->Get(i) == i + 1);
    }
    lab2::Sequence<int> *tmp = list1 + list1;
    ASSERT(list1.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        ASSERT(list1.Get(i) == i + 1);
    }
    ASSERT(tmp->GetSize() == 10);
    for (int i = 0; i < 10; i++) {
        ASSERT(tmp->Get(i) == i % 5 + 1);
    }
    delete tmp;
    delete list3;
}
ADD_TEST(ListSequenceTests, OperatorPlus);

TEST(ListSequenceTests, Concat) {
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[5] = {6, 7, 8, 9, 10};
    lab2::ListSequence<int> list1(5, arr1);
    lab2::ListSequence<int> list2(5, arr2);
    lab2::Sequence<int>* list3 = list1.Concat(list2);
    ASSERT(list3->GetSize() == 10);
    for (int i = 0; i < 10; i++) {
        ASSERT(list3->Get(i) == i + 1);
    }
    lab2::Sequence<int> *tmp = list1.Concat(list1);
    ASSERT(tmp->GetSize() == 10);
    for (int i = 0; i < 10; i++) {
        ASSERT(tmp->Get(i) == i % 5 + 1);
    }
    delete tmp;
    delete list3;
}
ADD_TEST(ListSequenceTests, Concat);

TEST(ListSequenceTests, Map) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    auto Square = [](const int &x) { return x * x; };
    lab2::Sequence<int> *list2 = list.Map(Square);
    ASSERT(list2->GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        ASSERT(list2->Get(i) == (i + 1) * (i + 1));
    }
    delete list2;
}
ADD_TEST(ListSequenceTests, Map);

TEST(ListSequenceTests, Reduce) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    auto mult = [](const int &x, const int &y) { return x * y; };
    auto Sum = [](const int &x, const int &y) { return x + y; };
    ASSERT(list.Reduce(Sum) == 15);
    ASSERT(list.Reduce(mult) == 120);
    lab2::ListSequence<int> list2;
    bool flag = false;
    try {
        list2.Reduce(mult);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, Reduce);

TEST(ListSequenceTests, Find) {
    lab2::ListSequence<int> list;
    bool flag = false;
    try {
        list.Find(1);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
    for(int i = 0; i != 5; ++i) {
        list.PushBack(5 * i);
    }
    for(int i = 0; i != 5; ++i) {
        list.PushBack(5 * i);
    }
    for(int i = 0; i != 5; ++i) {
        ASSERT(list.Find(5 * i) == i);
    }
    try {
        list.Find(-1);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, Find);

TEST(ListSequenceTests, TryFind) {
    lab2::ListSequence<int> list;
    lab2::Options<int> opt = list.TryFind(1);
    ASSERT(!opt.HasValue());
    for(int i = 0; i != 5; ++i) {
        list.PushBack(5 * i);
    }
    for(int i = 0; i != 5; ++i) {
        list.PushBack(5 * i);
    }
    for(int i = 0; i != 5; ++i) {
        opt = list.TryFind(5 * i);
        ASSERT(opt.HasValue());
        ASSERT(opt.Value() == i);
    }
    opt = list.TryFind(-1);
    ASSERT(!opt.HasValue());
}
ADD_TEST(ListSequenceTests, TryFind);

TEST(ListSequenceTests, Zip) {
    auto sqs = new lab2::ListSequence<lab2::Sequence<int>*>();
    auto arr1 = new lab2::ListSequence<int>(3, 3);
    auto arr2 = new lab2::ListSequence<int>(5, 5);
    auto arr3 = new lab2::ListSequence<int>(7, 7);
    sqs->PushBack(arr1);
    sqs->PushBack(arr2);
    sqs->PushBack(arr3);
    auto zipped = lab2::ListSequence<int>::Zip(sqs);
    ASSERT(zipped->GetSize() == 3);
    for(int i = 0; i != 3; ++i) {
        ASSERT(zipped->Get(i)->GetSize() == 3);
        ASSERT(zipped->Get(i)->Get(0) == 3);
        ASSERT(zipped->Get(i)->Get(1) == 5);
        ASSERT(zipped->Get(i)->Get(2) == 7);
    }
    for(int i = 0; i != 3; ++i) {
        delete zipped->Get(i);
        delete sqs->Get(i);
    }
    delete sqs;
    delete zipped;
}
ADD_TEST(ListSequenceTests, Zip);

TEST(ListSequenceTests, ZeroZip) {
    auto sqs = new lab2::ListSequence<lab2::Sequence<int>*>();
    auto zipped = lab2::ListSequence<int>::Zip(sqs);
    ASSERT(zipped->GetSize() == 0);
    delete sqs;
    delete zipped;
}
ADD_TEST(ListSequenceTests, ZeroZip);

TEST(ListSequenceTests, OneZip) {
    auto sqs = new lab2::ListSequence<lab2::Sequence<int>*>;
    auto arr1 = new lab2::ListSequence<int>(5, 7);
    sqs->PushBack(arr1);
    auto zipped = lab2::ListSequence<int>::Zip(sqs);
    ASSERT(zipped->GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(zipped->Get(i)->GetSize() == 1);
        ASSERT(zipped->Get(i)->Get(0) == 7);
        delete zipped->Get(i);
    }
    delete zipped;
    delete sqs->Get(0);
    delete sqs;
}
ADD_TEST(ListSequenceTests, OneZip);

TEST(ListSequenceTests, EmptySplit) {
    lab2::ListSequence<int> list;
    auto tmp1 = list.Split(0);
    auto seq1 = tmp1.first;
    auto size1 = tmp1.second;
    ASSERT(size1 == 1);
    ASSERT(seq1[0]->Empty());
    for(int i = 0; i != size1; ++i) {
        delete seq1[i];
    }
    delete seq1;
}
ADD_TEST(ListSequenceTests, EmptySplit);

TEST(ListSequenceTests, SimpleSplit) {
    lab2::ListSequence<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(2);
    list.PushBack(5);
    auto tmp1 = list.Split(2);
    auto seq1 = tmp1.first;
    auto size1 = tmp1.second;
    ASSERT(size1 == 3);
    for(int i = 0; i != 2; ++i) {
        ASSERT(seq1[i]->GetSize() == 1);
        ASSERT(seq1[i]->Get(0) == 2 * i + 1);
    }
    for(int i = 0; i != size1; ++i) {
        delete seq1[i];
    }
    delete seq1;
}
ADD_TEST(ListSequenceTests, SimpleSplit);

TEST(ListSequenceTests, SplitWithWrongDelim) {
    lab2::ListSequence<int> list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    list.PushBack(4);
    list.PushBack(5);
    auto tmp1 = list.Split(6);
    auto seq1 = tmp1.first;
    auto size1 = tmp1.second;
    ASSERT(size1 == 1);
    ASSERT(seq1[0]->GetSize() == 5);
    for(int i = 0; i != 5; ++i) {
        ASSERT(seq1[0]->Get(i) == i + 1);
    }
    for(int i = 0; i != size1; ++i) {
        delete seq1[i];
    }
    delete seq1;
}
ADD_TEST(ListSequenceTests, SplitWithWrongDelim);

TEST(ListSequenceTests, EmptySlice) {
    lab2::ListSequence<int> list;
    bool flag = false;
    try {
        list.Slice(0, 0, lab2::ListSequence<int>());
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Slice(0, 1, lab2::ListSequence<int>());
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, EmptySlice);

TEST(ListSequenceTests, SliceWithPositiveIndexes) {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8 ,9, 10};
    lab2::ListSequence<int> list(10, arr);
    list.Slice(2, 5, lab2::ArraySequence<int>(5));
    ASSERT(list.GetSize() == 10);
    for(int i = 0; i != 10; ++i) {
        if(i < 2 || i > 6) {
            ASSERT(list.Get(i) == i + 1);
        } else {
            ASSERT(list.Get(i) == 0);
        }
    }
    bool flag = false;
    try {
        list.Slice(0, 11, lab2::ArraySequence<int>(11));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Slice(0, -1, lab2::ListSequence<int>());
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Slice(5, 2, lab2::ArraySequence<int>(5));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Slice(10, 2, lab2::ArraySequence<int>(2));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, SliceWithPositiveIndexes);

TEST(ListSequenceTests, SliceWithNegativeIndexes) {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8 ,9, 10};
    lab2::ListSequence<int> list(10, arr);
    list.Slice(-2, 5, lab2::ArraySequence<int>(5));
    ASSERT(list.GetSize() == 10);
    for(int i = 0; i != 10; ++i) {
        if(i < 4 || i > 8) {
            ASSERT(list.Get(i) == i + 1);
        } else {
            ASSERT(list.Get(i) == 0);
        }
    }
    bool flag = false;
    try {
        list.Slice(-11, 2, lab2::ArraySequence<int>(2));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Slice(0, -1, lab2::ArraySequence<int>(2));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        list.Slice(-5, 11, lab2::ArraySequence<int>(11));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    try {
        list.Slice(-5, 2, lab2::ArraySequence<int>(5));
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ListSequenceTests, SliceWithNegativeIndexes);

TEST(ListSequenceTests, Empty) {
    lab2::ListSequence<int> list;
    ASSERT(list.Empty());
    list.PushBack(1);
    ASSERT(!list.Empty());
    list.PopFrom(0);
    ASSERT(list.Empty());
}
ADD_TEST(ListSequenceTests, Empty);

TEST(ListSequenceTests, Clear) {
    int arr[5] = {1, 2, 3, 4, 5};
    lab2::ListSequence<int> list(5, arr);
    list.Clear();
    ASSERT(list.GetSize() == 0);
    ASSERT(list.Empty());
}
ADD_TEST(ListSequenceTests, Clear);

TEST(ListSequenceTests, Iterators) {
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8 ,9, 10};
    auto *list = new lab2::ListSequence<int>(10, arr);
    lab2::IEnumerable<int> enumerable(list);
    for(auto &x : enumerable) {
        ASSERT(x == arr[x - 1]);
        x = 13;

    }
    for(const auto &x : enumerable) {
        ASSERT(x == 13);
    }
    delete list;
}
ADD_TEST(ListSequenceTests, Iterators);

TEST(ListSequenceTests, EmptyIterators) {
    lab2::ListSequence<int> list;
    lab2::IEnumerable<int> enumerable(&list);
    for(auto &x : enumerable) {
        ASSERT(false);
    }
    for(const auto &x : enumerable) {
        ASSERT(false);
    }
}
ADD_TEST(ListSequenceTests, EmptyIterators);