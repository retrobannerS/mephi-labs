#include "data_classes/SmartLinkedList.hpp"
#include "smart_pointers/SharedPtr.hpp"
#include "gtest/gtest.h"
#include <stdexcept>
#include <string>

using namespace sem3;

SharedPtr<SmartLinkedList<std::string>> testList() {
    auto list = make_shared<SmartLinkedList<std::string>>(5);

    for (int i = 0; i < 5; i++) {
        (*list)[i] = "TEST" + std::to_string(i);
    }
    return list;
}

TEST(SmartLinkedList, DefaultConstructor) {
    // Arrange
    SmartLinkedList<int> list;

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartLinkedList, ConstructorWithSize) {
    // Arrange
    SmartLinkedList<int> list(5);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list[i], 0);
    }
}

TEST(SmartLinkedList, ConstructorWithZeroSize) {
    // Arrange
    SmartLinkedList<int> list(0);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartLinkedList, ConstructorWithNegativeSize) {
    // Arrange

    // Act

    // Assert
    EXPECT_THROW(SmartLinkedList<int> list(-1), std::invalid_argument);
}

TEST(SmartLinkedList, ConstructorWithSizeAndItem) {
    // Arrange
    SmartLinkedList<int> list(5, 1);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list[i], 1);
    }
}

TEST(SmartLinkedList, ConstructorWithSizeAndItemZeroSize) {
    // Arrange
    SmartLinkedList<int> list(0, 1);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartLinkedList, ConstructorWithSizeAndItemNegativeSize) {
    // Arrange

    // Act

    // Assert
    EXPECT_THROW(SmartLinkedList<int> list(-1, 1), std::invalid_argument);
}

TEST(SmartLinkedList, ConstructorWithSizeAndItems) {
    // Arrange
    int items[] = {1, 2, 3, 4, 5};
    SmartLinkedList<int> list(5, items);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list[i], items[i]);
    }
}

TEST(SmartLinkedList, ConstructorWithSizeAndItemsZeroSize) {
    // Arrange
    int items[] = {1, 2, 3, 4, 5};
    SmartLinkedList<int> list(0, items);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartLinkedList, ConstructorWithSizeAndItemsNegativeSize) {
    // Arrange
    int items[] = {1, 2, 3, 4, 5};

    // Act

    // Assert
    EXPECT_THROW(SmartLinkedList<int> list(-1, items), std::invalid_argument);
}

TEST(SmartLinkedList, ConstructorWithSizeAndItemsWrongSize) {
    // Arrange
    int items[] = {1, 2, 3, 4, 5};

    // Act
    SmartLinkedList<int> list(3, items);

    // Assert
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(list[i], items[i]);
    }
}

TEST(SmartLinkedList, ConstructorWithSharedPtr) {
    // Arrange
    auto items = make_shared<int[]>(5);
    for (int i = 0; i < 5; i++) {
        items[i] = i + 1;
    }
    SmartLinkedList<int> list(5, items);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list[i], items[i]);
    }
}

TEST(SmartLinkedList, ConstructorWithSharedPtrZeroSize) {
    // Arrange
    auto items = make_shared<int[]>(0);
    SmartLinkedList<int> list(0, items);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartLinkedList, ConstructorWithSharedPtrNegativeSize) {
    // Arrange
    auto items = make_shared<int[]>(0);

    // Act

    // Assert
    EXPECT_THROW(SmartLinkedList<int> list(-1, items), std::invalid_argument);
}

TEST(SmartLinkedList, CopyConstructor) {
    // Arrange
    auto list1 = testList();

    // Act
    SmartLinkedList<std::string> list2(*list1);

    // Assert
    EXPECT_EQ(list2.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, CopyConstructorZeroSize) {
    // Arrange
    SmartLinkedList<int> list1(0);

    // Act
    SmartLinkedList<int> list2(list1);

    // Assert
    EXPECT_EQ(list2.getSize(), 0);
}

TEST(SmartLinkedList, MoveConstructor) {
    // Arrange
    auto list1 = testList();

    // Act
    SmartLinkedList<std::string> list2(std::move(*list1));

    // Assert
    EXPECT_EQ(list1->getSize(), 0);
    EXPECT_EQ(list2.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, MoveConstructorZeroSize) {
    // Arrange
    SmartLinkedList<int> list1(0);

    // Act
    SmartLinkedList<int> list2(std::move(list1));

    // Assert
    EXPECT_EQ(list1.getSize(), 0);
    EXPECT_EQ(list2.getSize(), 0);
}

TEST(SmartLinkedList, CopyConstructorFromLinkedList) {
    // Arrange
    lab2::LinkedList<std::string> list1(5);
    for (int i = 0; i < 5; i++) {
        list1[i] = "TEST" + std::to_string(i);
    }

    // Act
    SmartLinkedList<std::string> list2(list1);

    // Assert
    EXPECT_EQ(list2.getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, CopyConstructorFromLinkedListZeroSize) {
    // Arrange
    lab2::LinkedList<int> list1(0);

    // Act
    SmartLinkedList<int> list2(list1);

    // Assert
    EXPECT_EQ(list2.getSize(), 0);
}

TEST(SmartLinkedList, Destructor) {
    // Arrange
    auto list = new SmartLinkedList<int>(5);

    // Act
    delete list;

    // Assert
}

TEST(SmartLinkedList, AssignmentOperator) {
    // Arrange
    auto list1 = testList();
    auto list2 = make_shared<SmartLinkedList<std::string>>(3);

    // Act
    *list2 = *list1;

    // Assert
    EXPECT_EQ(list2->getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ((*list2)[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, AssignmentOperatorZeroSize) {
    // Arrange
    auto list1 = make_shared<SmartLinkedList<int>>(0);
    auto list2 = make_shared<SmartLinkedList<int>>(3);

    // Act
    *list2 = *list1;

    // Assert
    EXPECT_EQ(list2->getSize(), 0);
}

TEST(SmartLinkedList, MoveAssignmentOperator) {
    // Arrange
    auto list1 = testList();
    auto list2 = make_shared<SmartLinkedList<std::string>>(3);

    // Act
    *list2 = std::move(*list1);

    // Assert
    EXPECT_EQ(list1->getSize(), 0);
    EXPECT_EQ(list2->getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ((*list2)[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, MoveAssignmentOperatorZeroSize) {
    // Arrange
    auto list1 = make_shared<SmartLinkedList<int>>(0);
    auto list2 = make_shared<SmartLinkedList<int>>(3);

    // Act
    *list2 = std::move(*list1);

    // Assert
    EXPECT_EQ(list1->getSize(), 0);
    EXPECT_EQ(list2->getSize(), 0);
}

TEST(SmartLinkedList, AssignmentOperatorFromLinkedList) {
    // Arrange
    lab2::LinkedList<std::string> list1(5);
    for (int i = 0; i < 5; i++) {
        list1[i] = "TEST" + std::to_string(i);
    }
    auto list2 = make_shared<SmartLinkedList<std::string>>(3);

    // Act
    *list2 = list1;

    // Assert
    EXPECT_EQ(list2->getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ((*list2)[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, AssignmentOperatorFromLinkedListZeroSize) {
    // Arrange
    lab2::LinkedList<int> list1(0);
    auto list2 = make_shared<SmartLinkedList<int>>(3);

    // Act
    *list2 = list1;

    // Assert
    EXPECT_EQ(list2->getSize(), 0);
}

TEST(SmartLinkedList, AssignmentOperatorFromLinkedListWrongSize) {
    // Arrange
    lab2::LinkedList<std::string> list1(5);
    for (int i = 0; i < 5; i++) {
        list1[i] = "TEST" + std::to_string(i);
    }
    auto list2 = make_shared<SmartLinkedList<std::string>>(3);

    // Act
    *list2 = list1;

    // Assert
    EXPECT_EQ(list2->getSize(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ((*list2)[i], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, GetMethod) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list->get(i), "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, GetMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW(list->get(0), std::out_of_range);
}

TEST(SmartLinkedList, GetMethodNegativeIndex) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->get(-1), std::out_of_range);
}

TEST(SmartLinkedList, GetMethodIndexOutOfRange) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->get(5), std::out_of_range);
}

TEST(SmartLinkedList, GetFirstMethod) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_EQ(list->getFirst(), "TEST0");
}

TEST(SmartLinkedList, GetFirstMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW(list->getFirst(), std::out_of_range);
}

TEST(SmartLinkedList, GetLastMethod) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_EQ(list->getLast(), "TEST4");
}

TEST(SmartLinkedList, GetLastMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW(list->getLast(), std::out_of_range);
}

TEST(SmartLinkedList, GetSizeMethod) {
    // Arrange
    auto list = testList();
    auto list2 = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_EQ(list->getSize(), 5);
    EXPECT_EQ(list2->getSize(), 0);
}

TEST(SmartLinkedList, GetSubListMethod) {
    // Arrange
    auto list = testList();

    // Act
    auto sublist = list->getSubList(1, 4);

    // Assert
    EXPECT_EQ(sublist.getSize(), 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(sublist[i], "TEST" + std::to_string(i + 1));
    }
}

TEST(SmartLinkedList, GetSubListMethodExceptions) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->getSubList(-1, 5), std::out_of_range);
    EXPECT_THROW(list->getSubList(2, 1), std::invalid_argument);
    EXPECT_THROW(list->getSubList(0, 6), std::out_of_range);
    EXPECT_THROW(list->getSubList(5, 5), std::out_of_range);
    EXPECT_THROW(list->getSubList(2, -1), std::out_of_range);
}

TEST(SmartLinkedList, SetMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->set(2, "TEST");

    // Assert
    EXPECT_EQ(list->get(2), "TEST");
    EXPECT_EQ(list->getSize(), 5);
    EXPECT_EQ(list->get(0), "TEST0");
    EXPECT_EQ(list->get(1), "TEST1");
    EXPECT_EQ(list->get(4), "TEST4");
}

TEST(SmartLinkedList, SetMethodExcepts) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->set(-1, "TEST"), std::out_of_range);
    EXPECT_THROW(list->set(5, "TEST"), std::out_of_range);
}

TEST(SmartLinkedList, SetMethodWithRange) {
    // Arrange
    auto list = testList();

    // Act
    list->set(1, 4, "TEST");

    // Assert
    EXPECT_EQ(list->get(1), "TEST");
    EXPECT_EQ(list->get(2), "TEST");
    EXPECT_EQ(list->get(3), "TEST");
    EXPECT_EQ(list->getSize(), 5);
    EXPECT_EQ(list->get(0), "TEST0");
    EXPECT_EQ(list->get(4), "TEST4");
}

TEST(SmartLinkedList, SetMethodWithRangeExcepts) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->set(-1, 4, "TEST"), std::out_of_range);
    EXPECT_THROW(list->set(2, 1, "TEST"), std::invalid_argument);
    EXPECT_THROW(list->set(0, 6, "TEST"), std::out_of_range);
    EXPECT_THROW(list->set(5, 5, "TEST"), std::out_of_range);
    EXPECT_THROW(list->set(2, -1, "TEST"), std::out_of_range);
}

TEST(SmartLinkedList, AppendMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->append("TEST");

    // Assert
    EXPECT_EQ(list->getSize(), 6);
    EXPECT_EQ(list->get(0), "TEST0");
    EXPECT_EQ(list->get(1), "TEST1");
    EXPECT_EQ(list->get(2), "TEST2");
    EXPECT_EQ(list->get(3), "TEST3");
    EXPECT_EQ(list->get(4), "TEST4");
    EXPECT_EQ(list->get(5), "TEST");
}

TEST(SmartLinkedList, AppendMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act
    list->append(1);

    // Assert
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), 1);
}

TEST(SmartLinkedList, PrependMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->prepend("TEST");

    // Assert
    EXPECT_EQ(list->getSize(), 6);
    EXPECT_EQ(list->get(0), "TEST");
    EXPECT_EQ(list->get(1), "TEST0");
    EXPECT_EQ(list->get(2), "TEST1");
    EXPECT_EQ(list->get(3), "TEST2");
    EXPECT_EQ(list->get(4), "TEST3");
    EXPECT_EQ(list->get(5), "TEST4");
}

TEST(SmartLinkedList, PrependMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act
    list->prepend(1);

    // Assert
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), 1);
}

TEST(SmartLinkedList, InsertAtMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->insertAt(2, "TEST");
    list->insertAt(0, "TEST");
    list->insertAt(6, "TEST");

    // Assert
    EXPECT_EQ(list->getSize(), 8);
    EXPECT_EQ(list->get(0), "TEST");
    EXPECT_EQ(list->get(1), "TEST0");
    EXPECT_EQ(list->get(2), "TEST1");
    EXPECT_EQ(list->get(3), "TEST");
    EXPECT_EQ(list->get(4), "TEST2");
    EXPECT_EQ(list->get(5), "TEST3");
    EXPECT_EQ(list->get(6), "TEST");
    EXPECT_EQ(list->get(7), "TEST4");
}

TEST(SmartLinkedList, InsertAtMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act
    list->insertAt(0, 1);

    // Assert
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->get(0), 1);
}

TEST(SmartLinkedList, InsertAtMethodNegativeIndex) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->insertAt(-1, "TEST"), std::out_of_range);
}

TEST(SmartLinkedList, InsertAtMethodIndexOutOfRange) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->insertAt(6, "TEST"), std::out_of_range);
}

TEST(SmartLinkedList, RemoveAtMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->removeAt(2);
    list->removeAt(0);
    list->removeAt(2);

    // Assert
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->get(0), "TEST1");
    EXPECT_EQ(list->get(1), "TEST3");
}

TEST(SmartLinkedList, RemoveAtMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW(list->removeAt(0), std::out_of_range);
}

TEST(SmartLinkedList, RemoveAtMethodNegativeIndex) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->removeAt(-1), std::out_of_range);
}

TEST(SmartLinkedList, RemoveAtMethodIndexOutOfRange) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW(list->removeAt(5), std::out_of_range);
}

TEST(SmartLinkedList, RemoveFirstMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->removeFirst();

    // Assert
    EXPECT_EQ(list->getSize(), 4);
    EXPECT_EQ(list->get(0), "TEST1");
    EXPECT_EQ(list->get(1), "TEST2");
    EXPECT_EQ(list->get(2), "TEST3");
    EXPECT_EQ(list->get(3), "TEST4");
}

TEST(SmartLinkedList, RemoveFirstMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW(list->removeFirst(), std::out_of_range);
}

TEST(SmartLinkedList, RemoveLastMethod) {
    // Arrange
    auto list = testList();

    // Act
    list->removeLast();

    // Assert
    EXPECT_EQ(list->getSize(), 4);
    EXPECT_EQ(list->get(0), "TEST0");
    EXPECT_EQ(list->get(1), "TEST1");
    EXPECT_EQ(list->get(2), "TEST2");
    EXPECT_EQ(list->get(3), "TEST3");
}

TEST(SmartLinkedList, RemoveLastMethodZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW(list->removeLast(), std::out_of_range);
}

TEST(SmartLinkedList, ArrayOperator) {
    // Arrange
    auto list = testList();

    // Act
    (*list)[2] = "TEST";

    // Assert
    EXPECT_EQ((*list)[2], "TEST");
    EXPECT_EQ(list->getSize(), 5);
    EXPECT_EQ((*list)[0], "TEST0");
    EXPECT_EQ((*list)[1], "TEST1");
    EXPECT_EQ((*list)[3], "TEST3");
    EXPECT_EQ((*list)[4], "TEST4");
}

TEST(SmartLinkedList, ArrayOperatorZeroSize) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>(0);

    // Act

    // Assert
    EXPECT_THROW((*list)[0], std::out_of_range);
}

TEST(SmartLinkedList, ArrayOperatorNegativeIndex) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW((*list)[-1], std::out_of_range);
}

TEST(SmartLinkedList, ArrayOperatorIndexOutOfRange) {
    // Arrange
    auto list = testList();

    // Act

    // Assert
    EXPECT_THROW((*list)[5], std::out_of_range);
}

TEST(SmartLinkedList, ConcatOperator) {
    // Arrange
    auto list1 = testList();
    auto list2 = testList();

    // Act
    auto list3 = *list1 + *list2;

    // Assert
    EXPECT_EQ(list3.getSize(), 10);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list3[i], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list3[i + 5], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, ConcatOperatorZeroSize) {
    // Arrange
    auto list1 = make_shared<SmartLinkedList<int>>(0);
    auto list2 = make_shared<SmartLinkedList<int>>(0);

    // Act
    auto list3 = *list1 + *list2;

    // Assert
    EXPECT_EQ(list3.getSize(), 0);
}

TEST(SmartLinkedList, ManyConcatOperators) {
    // Arrange
    auto list1 = testList();
    auto list2 = testList();
    auto list3 = testList();
    auto list4 = testList();
    auto list5 = testList();

    // Act
    auto list6 = *list1 + *list2 + *list3 + *list4 + *list5;

    // Assert
    EXPECT_EQ(list6.getSize(), 25);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 5], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 10], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 15], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 20], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, ConcatOperatorWithSelf) {
    // Arrange
    auto list1 = testList();

    // Act
    auto list2 = *list1 + *list1;

    // Assert
    EXPECT_EQ(list2.getSize(), 10);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i + 5], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, ConcatOperatorWithSelfZeroSize) {
    // Arrange
    auto list1 = make_shared<SmartLinkedList<int>>(0);

    // Act
    auto list2 = *list1 + *list1;

    // Assert
    EXPECT_EQ(list2.getSize(), 0);
}

TEST(SmartLinkedList, ConcatMethod) {
    // Arrange
    auto list1 = testList();
    auto list2 = testList();

    // Act
    auto list3 = list1->concat(*list2);

    // Assert
    EXPECT_EQ(list3.getSize(), 10);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list3[i], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list3[i + 5], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, ConcatMethodZeroSize) {
    // Arrange
    auto list1 = make_shared<SmartLinkedList<int>>(0);
    auto list2 = make_shared<SmartLinkedList<int>>(0);

    // Act
    auto list3 = list1->concat(*list2);

    // Assert
    EXPECT_EQ(list3.getSize(), 0);
}

TEST(SmartLinkedList, ManyConcatMethods) {
    // Arrange
    auto list1 = testList();
    auto list2 = testList();
    auto list3 = testList();
    auto list4 = testList();
    auto list5 = testList();

    // Act
    auto list6 = list1->concat(*list2).concat(*list3).concat(*list4).concat(*list5);

    // Assert
    EXPECT_EQ(list6.getSize(), 25);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 5], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 10], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 15], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list6[i + 20], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, ConcatMethodWithSelf) {
    // Arrange
    auto list1 = testList();

    // Act
    auto list2 = list1->concat(*list1);

    // Assert
    EXPECT_EQ(list2.getSize(), 10);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i], "TEST" + std::to_string(i));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(list2[i + 5], "TEST" + std::to_string(i));
    }
}

TEST(SmartLinkedList, ConcatMethodWithSelfZeroSize) {
    // Arrange
    auto list1 = make_shared<SmartLinkedList<int>>(0);

    // Act
    auto list2 = list1->concat(*list1);

    // Assert
    EXPECT_EQ(list2.getSize(), 0);
}
