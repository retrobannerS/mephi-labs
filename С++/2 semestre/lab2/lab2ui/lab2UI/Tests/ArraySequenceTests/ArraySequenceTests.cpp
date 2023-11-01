#include <stdexcept>
#include <string>
#include "../../Options/Options.hpp"
#include "../UnitTest.hpp"
#include "../TestCluster.hpp"
#include "../../Data_Classes/LinkedList.hpp"
#include "../../Data_Classes/DynamicArray.hpp"
#include "../../Sequences/ArraySequence.hpp"
#include "../../Sequences/ListSequence.hpp"
#include "../../IEnumerators/IEnumerable.hpp"

test::TestCluster ArraySequenceTests("ArraySequence");

TEST(ArraySequenceTests, DefaultConstructor) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
}
ADD_TEST(ArraySequenceTests, DefaultConstructor);

TEST(ArraySequenceTests, ConstructorWithSize) {
    lab2::ArraySequence<int> arr(10);
    ASSERT(arr.GetSize() == 10);
    ASSERT(arr.GetCapacity() == 20);
    lab2::ArraySequence<int> arr3(0);
    ASSERT(arr3.GetSize() == 0);
    ASSERT(arr3.GetCapacity() == 0);
    bool flag = false;
    try {
        lab2::ArraySequence<int> arr2(-1);
    } catch (const std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, ConstructorWithSize);

TEST(ArraySequenceTests, ConstructorWithSizeAndItem) {
    lab2::ArraySequence<int> arr(10, 5);
    ASSERT(arr.GetSize() == 10);
    ASSERT(arr.GetCapacity() == 20);
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr.Get(i) == 5);
    }
    lab2::ArraySequence<int> arr3(0, 5);
    ASSERT(arr3.GetSize() == 0);
    ASSERT(arr3.GetCapacity() == 0);
    bool flag = false;
    try {
        lab2::ArraySequence<int> arr2(-1, 5);
    } catch (const std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, ConstructorWithSizeAndItem);

TEST(ArraySequenceTests, ConstructorWithSizeAndArray) {
    auto arr = new std::string[10];
    for (int i = 0; i < 10; ++i) {
        arr[i] = "Hello" + std::to_string(i);
    }
    lab2::ArraySequence<std::string> arr2(10, arr);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2.GetCapacity() == 20);
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr2.Get(i) == "Hello" + std::to_string(i));
    }
    bool flag = false;
    try {
        lab2::ArraySequence<std::string> arr3(-1, arr);
    } catch (const std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
    delete[] arr;
}
ADD_TEST(ArraySequenceTests, ConstructorWithSizeAndArray);

TEST(ArraySequenceTests, ConstructorWithDynamicArray) {
    lab2::DynamicArray<int> arr(10, 5);
    lab2::ArraySequence<int> arr2(arr);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2.GetCapacity() == 20);
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr2.Get(i) == 5);
    }


    lab2::DynamicArray<std::string> arr3(10);
    for (int i = 0; i < 10; ++i) {
        arr3.Set(i, "Hello" + std::to_string(i));
    }
    lab2::ArraySequence<std::string> arr4(arr3);
    ASSERT(arr4.GetSize() == 10);
    ASSERT(arr4.GetCapacity() == 20);
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr4.Get(i) == "Hello" + std::to_string(i));
    }
}
ADD_TEST(ArraySequenceTests, ConstructorWithDynamicArray);

TEST(ArraySequenceTests, ConstructorWithLinkedList) {
    lab2::LinkedList<int> list(10, 5);
    lab2::ArraySequence<int> arr2(list);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2.GetCapacity() == 20);
    for(int i = 0; i < 10; ++i) {
        ASSERT(arr2.Get(i) == 5);
    }
}
ADD_TEST(ArraySequenceTests, ConstructorWithLinkedList);

TEST(ArraySequenceTests, ConstructorWithListSequence) {
    lab2::ListSequence<int> list(10, 5);
    lab2::ArraySequence<int> arr2(list);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2.GetCapacity() == 20);
    for(int i = 0; i < 10; ++i) {
        ASSERT(arr2.Get(i) == 5);
    }
}
ADD_TEST(ArraySequenceTests, ConstructorWithListSequence);

TEST(ArraySequenceTests, ConstructorWithSequence) {
    lab2::Sequence<int> *arr = new lab2::ArraySequence<int>(10, 5);
    lab2::ArraySequence<int> arr2(arr);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2.GetCapacity() == 20);
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr2.Get(i) == 5);
    }
    delete arr;
}
ADD_TEST(ArraySequenceTests, ConstructorWithSequence);

TEST(ArraySequenceTests, CopyConstructor) {
    lab2::ArraySequence<int> arr(10, 5);
    lab2::ArraySequence<int> arr2(arr);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2.GetCapacity() == 20);
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr2.Get(i) == 5);
    }
}
ADD_TEST(ArraySequenceTests, CopyConstructor);

TEST(ArraySequenceTests, SequenceConstructor) {
    lab2::Sequence<int>* seq = new lab2::ListSequence<int>;
    for (int i = 0; i < 10; ++i)
        seq->PushBack(i + 1);

    lab2::ArraySequence<int> arr(seq);
    ASSERT(arr.GetSize() == 10);
    ASSERT(arr.GetFirst() == 1);
    ASSERT(arr.GetLast() == 10);
}
ADD_TEST(ArraySequenceTests, SequenceConstructor);

TEST(ArraySequenceTests, Destructor) {
    auto *arr = new lab2::ArraySequence<std::string>(10, "Hello");
    delete arr;
}
ADD_TEST(ArraySequenceTests, Destructor);

TEST(ArraySequenceTests, GetFirst) {
    lab2::ArraySequence<int> arr;
    bool flag = false;
    try {
        arr.GetFirst();
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ArraySequence<int> arr2(10);
    ASSERT(arr2.GetFirst() == 0);
    lab2::ArraySequence<int> arr3(11, 5);
    ASSERT(arr3.GetFirst() == 5);
}
ADD_TEST(ArraySequenceTests, GetFirst);

TEST(ArraySequenceTests, GetLast) {
    lab2::ArraySequence<int> arr;
    bool flag = false;
    try {
        arr.GetLast();
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ArraySequence<int> arr2(10);
    ASSERT(arr2.GetLast() == 0);
    lab2::ArraySequence<int> arr3(11, 5);
    ASSERT(arr3.GetLast() == 5);
}
ADD_TEST(ArraySequenceTests, GetLast);

TEST(ArraySequenceTests, TryGetFirst) {
    lab2::ArraySequence<int> arr;
    lab2::Options<int> opt = arr.TryGetFirst();
    ASSERT(!opt.HasValue());
    bool flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(opt.ValueOr(122) == 122);
    lab2::ArraySequence<int> arr2(10);
    opt = arr2.TryGetFirst();
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 0);
    ASSERT(opt.ValueOr(122) == 0);
    int arr22[5] = {1, 2, 3, 4, 5};
    lab2::ArraySequence<int> arr3(11, arr22);
    opt = arr3.TryGetFirst();
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 1);
    ASSERT(opt.ValueOr(122) == 1);
}
ADD_TEST(ArraySequenceTests, TryGetFirst);

TEST(ArraySequenceTests, TryGetLast) {
    lab2::ArraySequence<int> arr;
    lab2::Options<int> opt = arr.TryGetLast();
    ASSERT(!opt.HasValue());
    bool flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(opt.ValueOr(122) == 122);
    lab2::ArraySequence<int> arr2(10);
    opt = arr2.TryGetLast();
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 0);
    ASSERT(opt.ValueOr(122) == 0);
    int arr22[5] = {1, 2, 3, 4, 5};
    lab2::ArraySequence<int> arr3(5, arr22);
    opt = arr3.TryGetLast();
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 5);
    ASSERT(opt.ValueOr(122) == 5);
}
ADD_TEST(ArraySequenceTests, TryGetLast);

TEST(ArraySequenceTests, GetSize) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    lab2::ArraySequence<int> arr2(10);
    ASSERT(arr2.GetSize() == 10);
    lab2::ArraySequence<int> arr3(11, 5);
    ASSERT(arr3.GetSize() == 11);
}
ADD_TEST(ArraySequenceTests, GetSize);

TEST(ArraySequenceTests, GetCapacity) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetCapacity() == 0);
    lab2::ArraySequence<int> arr2(10);
    ASSERT(arr2.GetCapacity() == 20);
    lab2::ArraySequence<int> arr3(11, 5);
    ASSERT(arr3.GetCapacity() == 22);
}
ADD_TEST(ArraySequenceTests, GetCapacity);

TEST(ArraySequenceTests, Get) {
    lab2::ArraySequence<int> arr;
    bool flag = false;
    try {
        arr.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ArraySequence<int> arr2(10);
    ASSERT(arr2.Get(0) == 0);
    ASSERT(arr2.Get(9) == 0);
    flag = false;
    try {
        arr2.Get(10);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ArraySequence<int> arr3(11, 5);
    ASSERT(arr3.Get(0) == 5);
    ASSERT(arr3.Get(10) == 5);
    flag = false;
    try {
        arr3.Get(11);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr3.Get(-1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, Get);

TEST(ArraySequenceTests, TryGet) {
    lab2::ArraySequence<int> arr;
    lab2::Options<int> opt = arr.TryGet(0);
    ASSERT(!opt.HasValue());
    bool flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(opt.ValueOr(122) == 122);
    lab2::ArraySequence<int> arr2(10);
    opt = arr2.TryGet(0);
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 0);
    ASSERT(opt.ValueOr(122) == 0);
    opt = arr2.TryGet(9);
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 0);
    ASSERT(opt.ValueOr(122) == 0);
    opt = arr2.TryGet(10);
    ASSERT(!opt.HasValue());
    flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(opt.ValueOr(122) == 122);
    lab2::ArraySequence<int> arr3(11, 5);
    opt = arr3.TryGet(0);
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 5);
    ASSERT(opt.ValueOr(122) == 5);
    opt = arr3.TryGet(10);
    ASSERT(opt.HasValue());
    ASSERT(opt.Value() == 5);
    ASSERT(opt.ValueOr(122) == 5);
    opt = arr3.TryGet(11);
    ASSERT(!opt.HasValue());
    flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(opt.ValueOr(122) == 122);
    opt = arr3.TryGet(-1);
    ASSERT(!opt.HasValue());
    flag = false;
    try {
        opt.Value();
    } catch (std::logic_error &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(opt.ValueOr(122) == 122);
}
ADD_TEST(ArraySequenceTests, TryGet);

TEST(ArraySequenceTests, GetSubSequence) {
    auto *seq = new lab2::ArraySequence<int>(10);
    for(int i = 0; i < 10; i++) {
        seq->Set(i, i * 10);
    }
    lab2::Sequence<int> *subSeq = seq->GetSubSequence(3, 7);
    ASSERT(subSeq->GetSize() == 5);
    for(int i = 0; i < 5; i++) {
        ASSERT(subSeq->Get(i) == (i + 3) * 10);
    }
    delete subSeq;

    subSeq = seq->GetSubSequence(0, 9);
    ASSERT(subSeq->GetSize() == 10);
    for(int i = 0; i < 10; i++) {
        ASSERT(subSeq->Get(i) == i * 10);
    }
    delete subSeq;

    bool flag = false;
    try {
        seq->GetSubSequence(0, 11);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        seq->GetSubSequence(-1, 9);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        seq->GetSubSequence(0, -1);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        seq->GetSubSequence(7, 3);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    delete seq;
}
ADD_TEST(ArraySequenceTests, GetSubSequence);

TEST(ArraySequenceTests, Set1) {
    lab2::ArraySequence<int> arr;
    bool flag = false;
    try {
        arr.Set(0, 5);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ArraySequence<int> arr2(10);
    arr2.Set(0, 5);
    ASSERT(arr2.Get(0) == 5);
    arr2.Set(9, 5);
    ASSERT(arr2.Get(9) == 5);
    flag = false;
    try {
        arr2.Set(10, 5);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    lab2::ArraySequence<int> arr3(11, 5);
    arr3.Set(0, 10);
    ASSERT(arr3.Get(0) == 10);
    arr3.Set(10, 10);
    ASSERT(arr3.Get(10) == 10);
    flag = false;
    try {
        arr3.Set(11, 10);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr3.Set(-1, 10);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, Set1);

TEST(ArraySequenceTests, Set2) {
    lab2::ArraySequence<int> a(10);
    a.Set(2, 5, 22);
    ASSERT(a.Get(1) == 0);
    ASSERT(a.Get(2) == 22);
    ASSERT(a.Get(6) == 22);
    ASSERT(a.Get(9) == 0);
    a.Set(0, 10, 22);
    ASSERT(a.Get(0) == 22);
    ASSERT(a.Get(9) == 22);

    //try exceptions
    bool flag = false;
    try {
        a.Set(-1, 5, 22);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        a.Set(10, 5, 22);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        a.Set(2, 0, 22);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        a.Set(2, -1, 22);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        a.Set(0, 11, 22);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, Set2);

TEST(ArraySequenceTests, PushBack) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    arr.PushBack(5);
    ASSERT(arr.GetSize() == 1);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 5);
    arr.PushBack(10);
    ASSERT(arr.GetSize() == 2);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    arr.PushBack(15);
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    ASSERT(arr.Get(2) == 15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    ASSERT(arr.Get(2) == 15);
    ASSERT(arr.Get(3) == 20);
}
ADD_TEST(ArraySequenceTests, PushBack);

TEST(ArraySequenceTests, PushFront) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    arr.PushFront(5);
    ASSERT(arr.GetSize() == 1);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 5);
    arr.PushFront(10);
    ASSERT(arr.GetSize() == 2);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 10);
    ASSERT(arr.Get(1) == 5);
    arr.PushFront(15);
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 15);
    ASSERT(arr.Get(1) == 10);
    ASSERT(arr.Get(2) == 5);
    arr.PushFront(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 20);
    ASSERT(arr.Get(1) == 15);
    ASSERT(arr.Get(2) == 10);
    ASSERT(arr.Get(3) == 5);
}
ADD_TEST(ArraySequenceTests, PushFront);

TEST(ArraySequenceTests, PopBack) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    bool flag = false;
    try {
        arr.PopBack();
    } catch (const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    ASSERT(arr.Get(2) == 15);
    ASSERT(arr.Get(3) == 20);
    arr.PopBack();
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    ASSERT(arr.Get(2) == 15);
    arr.PopBack();
    ASSERT(arr.GetSize() == 2);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    arr.PopBack();
    ASSERT(arr.GetSize() == 1);
    ASSERT(arr.GetCapacity() == 1);
    ASSERT(arr.Get(0) == 5);
    arr.PopBack();
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
}
ADD_TEST(ArraySequenceTests, PopBack);

TEST(ArraySequenceTests, PopFront) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    bool flag = false;
    try {
        arr.PopFront();
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 5);
    ASSERT(arr.Get(1) == 10);
    ASSERT(arr.Get(2) == 15);
    ASSERT(arr.Get(3) == 20);
    arr.PopFront();
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 10);
    ASSERT(arr.Get(1) == 15);
    ASSERT(arr.Get(2) == 20);
    arr.PopFront();
    ASSERT(arr.GetSize() == 2);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 15);
    ASSERT(arr.Get(1) == 20);
    arr.PopFront();
    ASSERT(arr.GetSize() == 1);
    ASSERT(arr.GetCapacity() == 1);
    ASSERT(arr.Get(0) == 20);
    arr.PopFront();
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
}
ADD_TEST(ArraySequenceTests, PopFront);

TEST(ArraySequenceTests, InsertAt) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    arr.InsertAt(0, 5);
    ASSERT(arr.GetSize() == 1);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 5);
    arr.InsertAt(0, 10);
    ASSERT(arr.GetSize() == 2);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 10);
    ASSERT(arr.Get(1) == 5);
    arr.InsertAt(1, 15);
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 3);
    ASSERT(arr.Get(0) == 10);
    ASSERT(arr.Get(1) == 15);
    ASSERT(arr.Get(2) == 5);
    arr.InsertAt(2, 20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Get(0) == 10);
    ASSERT(arr.Get(1) == 15);
    ASSERT(arr.Get(3) == 5);
    ASSERT(arr.Get(2) == 20);
}
ADD_TEST(ArraySequenceTests, InsertAt);

TEST(ArraySequenceTests, PlusOperator) {
    lab2::ArraySequence<int> arr1(4);
    lab2::ArraySequence<int> arr2(4);
    arr1.Set(0, 4, 5);
    arr2.Set(0, 4, 10);
    auto arr3 = dynamic_cast<lab2::ArraySequence<int> *>(arr1 + arr2);
    ASSERT(arr3->GetSize() == 8);
    ASSERT(arr3->GetCapacity() == 16);
    ASSERT(arr3->Get(0) == 5);
    ASSERT(arr3->Get(1) == 5);
    ASSERT(arr3->Get(7) == 10);
}
ADD_TEST(ArraySequenceTests, PlusOperator);

TEST(ArraySequenceTests, SquareBrackets) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    bool flag = false;
    try {
        arr[0];
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr[0] == 5);
    ASSERT(arr[1] == 10);
    ASSERT(arr[2] == 15);
    ASSERT(arr[3] == 20);
    arr[0] = 25;
    ASSERT(arr[0] == 25);
    arr[1] = 30;
    ASSERT(arr[1] == 30);
    arr[2] = 35;
    ASSERT(arr[2] == 35);
    arr[3] = 40;
    ASSERT(arr[3] == 40);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
}
ADD_TEST(ArraySequenceTests, SquareBrackets);

TEST(ArraySequenceTests, OperatorEqual) {
    lab2::ArraySequence<std::string> arr(10);
    for (int i = 0; i < 10; ++i) {
        arr.Set(i, "Hello" + std::to_string(i));
    }
    lab2::ArraySequence<std::string> arr2 = arr;

    ASSERT(arr.GetSize() == arr2.GetSize());
    ASSERT(arr.GetCapacity() == arr2.GetCapacity());
    for (int i = 0; i < 10; ++i) {
        ASSERT(arr.Get(i) == arr2.Get(i));
    }
}
ADD_TEST(ArraySequenceTests, OperatorEqual);

TEST(ArraySequenceTests, Concat) {
    lab2::ArraySequence<int> arr1;
    lab2::ArraySequence<int> arr2;
    auto *arr3 = arr1.Concat(arr2);
    ASSERT(arr3->GetSize() == 0);
//    ASSERT(arr3->GetCapacity() == 0);
    arr1.PushBack(5);
    arr1.PushBack(10);
    arr1.PushBack(15);
    arr1.PushBack(20);
    ASSERT(arr1.GetSize() == 4);
    ASSERT(arr1.GetCapacity() == 6);
    arr2.PushBack(25);
    arr2.PushBack(30);
    arr2.PushBack(35);
    arr2.PushBack(40);
    ASSERT(arr2.GetSize() == 4);
    ASSERT(arr2.GetCapacity() == 6);
    delete arr3;
    arr3 = dynamic_cast<lab2::ArraySequence<int> *>(arr1.Concat(arr2));
    ASSERT(arr3->GetSize() == 8);
//    ASSERT(arr3->GetCapacity() == 16);
    ASSERT(arr3->Get(0) == 5);
    ASSERT(arr3->Get(1) == 10);
    ASSERT(arr3->Get(2) == 15);
    ASSERT(arr3->Get(3) == 20);
    ASSERT(arr3->Get(4) == 25);
    ASSERT(arr3->Get(5) == 30);
    ASSERT(arr3->Get(6) == 35);
    ASSERT(arr3->Get(7) == 40);
    delete arr3;
}
ADD_TEST(ArraySequenceTests, Concat);

TEST(ArraySequenceTests, Map) {
    auto add = [](const int &a) { return a + 1; };
    auto mult = [](const int &a) { return a * 2; };
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    bool flag = false;
    try {
        arr.Map(add);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr.Map(mult);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    auto *arr2 = dynamic_cast<lab2::ArraySequence<int> *>(arr.Map(add));
    ASSERT(arr2->GetSize() == 4);
    ASSERT(arr2->GetCapacity() == 8);
    ASSERT(arr2->Get(0) == 6);
    ASSERT(arr2->Get(1) == 11);
    ASSERT(arr2->Get(2) == 16);
    ASSERT(arr2->Get(3) == 21);
    delete arr2;
    arr2 = dynamic_cast<lab2::ArraySequence<int> *>(arr.Map(mult));
    ASSERT(arr2->GetSize() == 4);
    ASSERT(arr2->GetCapacity() == 8);
    ASSERT(arr2->Get(0) == 10);
    ASSERT(arr2->Get(1) == 20);
    ASSERT(arr2->Get(2) == 30);
    ASSERT(arr2->Get(3) == 40);
    delete arr2;
}
ADD_TEST(ArraySequenceTests, Map);

TEST(ArraySequenceTests, Reduce) {
    auto add = [](const int &a, const int &b) { return a + b; };
    auto mult = [](const int &a, const int &b) { return a * b; };
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    bool flag = false;
    try {
        arr.Reduce(add);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr.Reduce(mult);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(arr.Reduce(add) == 50);
    ASSERT(arr.Reduce(mult) == 15000);
}
ADD_TEST(ArraySequenceTests, Reduce);

TEST(ArraySequenceTests, Find) {
    lab2::ArraySequence<int> arr;
    for(int i = 0; i != 10; ++i) {
        arr.PushBack(5 * i);
    }
    for(int i = 0; i != 10; ++i) {
        arr.PushBack(5 * i);
    }
    for(int i = 0; i != 10; ++i) {
        ASSERT(arr.Find(5 * i) == i);
    }
    bool flag = false;
    try {
        arr.Find(100);
    } catch (std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, Find);

TEST(ArraySequenceTests, TryFind) {
    lab2::ArraySequence<int> arr;
    for(int i = 0; i != 10; ++i) {
        arr.PushBack(5 * i);
    }
    for(int i = 0; i != 10; ++i) {
        arr.PushBack(5 * i);
    }
    for(int i = 0; i != 10; ++i) {
        lab2::Options<int> opt = arr.TryFind(5 * i);
        ASSERT(opt.HasValue());
        ASSERT(opt.Value() == i);
    }
    lab2::Options<int> opt = arr.TryFind(100);
    ASSERT(!opt.HasValue());
}
ADD_TEST(ArraySequenceTests, TryFind);

TEST(ArraySequenceTests, Zip) {
    auto sqs = new lab2::ArraySequence<lab2::Sequence<int>*>();
    auto arr1 = new lab2::ArraySequence<int>(3, 3);
    auto arr2 = new lab2::ArraySequence<int>(5, 5);
    auto arr3 = new lab2::ArraySequence<int>(7, 7);
    sqs->PushBack(arr1);
    sqs->PushBack(arr2);
    sqs->PushBack(arr3);
    auto zipped = lab2::ArraySequence<int>::Zip(sqs);
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
ADD_TEST(ArraySequenceTests, Zip);

TEST(ArraySequenceTests, ZeroZip) {
    auto sqs = new lab2::ArraySequence<lab2::Sequence<int>*>();
    auto zipped = lab2::ArraySequence<int>::Zip(sqs);
    ASSERT(zipped->GetSize() == 0);
    delete sqs;
    delete zipped;
}
ADD_TEST(ArraySequenceTests, ZeroZip);

TEST(ArraySequenceTests, OneZip) {
    auto sqs = new lab2::ArraySequence<lab2::Sequence<int>*>;
    auto arr1 = new lab2::ArraySequence<int>(5, 7);
    sqs->PushBack(arr1);
    auto zipped = lab2::ArraySequence<int>::Zip(sqs);
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
ADD_TEST(ArraySequenceTests, OneZip);

TEST(ArraySequenceTests, Split) {
    lab2::ArraySequence<int> arr;
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    arr.PushBack(10);
    arr.PushBack(25);

    int delim = 10;

    auto parts = arr.Split(delim);
    int parts_count = parts.second;
    auto sequences = parts.first;

    ASSERT(parts_count == 3);

    ASSERT(sequences[0]->GetSize() == 1);
    ASSERT(sequences[0]->Get(0) == 5);

    // Проверяем вторую подпоследовательность
    ASSERT(sequences[1]->GetSize() == 2);
    ASSERT(sequences[1]->Get(0) == 15);
    ASSERT(sequences[1]->Get(1) == 20);

    // Проверяем третью подпоследовательность
    ASSERT(sequences[2]->GetSize() == 1);
    ASSERT(sequences[2]->Get(0) == 25);

    delete[] sequences;

    // Проверяем случай, когда разделитель отсутствует
    int missingDelim = 100;
    parts = arr.Split(missingDelim);
    parts_count = parts.second;
    sequences = parts.first;

    ASSERT(parts_count == 1);
    ASSERT(sequences[0]->GetSize() == arr.GetSize());
    for (int i = 0; i < arr.GetSize(); ++i) {
        ASSERT(sequences[0]->Get(i) == arr.Get(i));
    }

    delete[] sequences;

    // Проверяем случай с пустым массивом
    lab2::ArraySequence<int> emptyArr;
    parts = arr.Split(missingDelim);
    parts_count = parts.second;
    sequences = parts.first;
    delete[] sequences;

    ASSERT(parts_count == 1);
}
ADD_TEST(ArraySequenceTests, Split);

TEST(ArraySequenceTests, SliceWithPositiveIndexes) {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    lab2::ArraySequence<int> seq(10, arr);
    seq.Slice(3, 5, lab2::ArraySequence<int>(5, 5));
    ASSERT(seq.GetSize() == 10);
    for(int i = 0; i != 10; ++i) {
        if(i < 3 || i > 7) {
            ASSERT(seq.Get(i) == i);
        } else {
            ASSERT(seq.Get(i) == 5);
        }
    }
}
ADD_TEST(ArraySequenceTests, SliceWithPositiveIndexes);

TEST(ArraySequenceTests, SliceWithNegativeIndexes) {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    lab2::ArraySequence<int> seq(10, arr);
    seq.Slice(-5, 4, lab2::ArraySequence<int>(4, 5));
    ASSERT(seq.GetSize() == 10);
    for(int i = 0; i != 10; ++i) {
        if(i < 2 or i > 5) {
            ASSERT(seq.Get(i) == i);
        } else {
            ASSERT(seq.Get(i) == 5);
        }
    }
}
ADD_TEST(ArraySequenceTests, SliceWithNegativeIndexes);

TEST(ArraySequenceTests, InvalidSlice) {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    lab2::ArraySequence<int> seq(10, arr);
    bool flag = false;
    try {
        seq.Slice(3, 10, lab2::ArraySequence<int>(10, 5));
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    try{
        seq.Slice(3, -1, lab2::ArraySequence<int>(10, 5));
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    try{
        seq.Slice(10, 2, lab2::ArraySequence<int>(10, 5));
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, InvalidSlice);

TEST(ArraySequenceTests, Empty) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    ASSERT(arr.Empty());
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    ASSERT(!arr.Empty());
}
ADD_TEST(ArraySequenceTests, Empty);

TEST(ArraySequenceTests, Clear) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    bool flag = false;
    try {
        arr.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    arr.Clear();
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    try {
        arr.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    arr.Clear();
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
    flag = false;
    try {
        arr.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, Clear);

TEST(ArraySequenceTests, Resize1) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    arr.Resize(5);
    ASSERT(arr.GetSize() == 5);
    ASSERT(arr.GetCapacity() == 10);
    ASSERT(arr.Get(4) == 0);
    arr.Resize(3);
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 5);
    ASSERT(arr.Get(2) == 0);
    arr.Resize(0);
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
    arr.Resize(10);
    ASSERT(arr.GetSize() == 10);
    ASSERT(arr.GetCapacity() == 20);
    ASSERT(arr.Get(9) == 0);
    arr.Resize(0);
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
}
ADD_TEST(ArraySequenceTests, Resize1);

TEST(ArraySequenceTests, Resize2) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    arr.Resize(5, 5);
    ASSERT(arr.GetSize() == 5);
    ASSERT(arr.GetCapacity() == 10);
    ASSERT(arr.Get(4) == 5);
    arr.Resize(3, 10);
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr.GetCapacity() == 5);
    ASSERT(arr.Get(2) == 5);
    arr.Resize(0, 15);
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
    bool flag = false;
    try {
        arr.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.Resize(10, 20);
    ASSERT(arr.GetSize() == 10);
    ASSERT(arr.GetCapacity() == 20);
    ASSERT(arr.Get(9) == 20);
    arr.Resize(0, 25);
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 3);
    flag = false;
    try {
        arr.Get(0);
    } catch (std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(ArraySequenceTests, Resize2);

TEST(ArraySequenceTests, Reserve) {
    lab2::ArraySequence<int> arr;
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 0);
    arr.Reserve(5);
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 5);
    arr.Reserve(10);
    ASSERT(arr.GetSize() == 0);
    ASSERT(arr.GetCapacity() == 10);
    arr.PushBack(5);
    arr.PushBack(10);
    arr.PushBack(15);
    arr.PushBack(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    arr.Reserve(5);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 6);
    arr.Reserve(20);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 20);
    arr.Reserve(3);
    ASSERT(arr.GetSize() == 4);
    ASSERT(arr.GetCapacity() == 20);
}
ADD_TEST(ArraySequenceTests, Reserve);

TEST(ArraySequenceTests, Iterator) {
    int arr1[10] = {1, 2, 3, 4, 5, 6, 7, 8 ,9, 10};
    lab2::ArraySequence<int> arr(10, arr1);
    lab2::IEnumerable<int> ien(&arr);
    for(auto &x:ien) {
        ASSERT(x == arr1[x - 1]);
        x = 25;
    }
    for(auto x:ien) {
        ASSERT(x == 25);
    }
}
ADD_TEST(ArraySequenceTests, Iterator);

TEST(ArraySequenceTests, EmptyIterator) {
    lab2::ArraySequence<int> arr;
    lab2::IEnumerable<int> ien(&arr);
    for(auto &x:ien) {
        ASSERT(false);
    }
    for(auto x:ien) {
        ASSERT(false);
    }
}
ADD_TEST(ArraySequenceTests, EmptyIterator);