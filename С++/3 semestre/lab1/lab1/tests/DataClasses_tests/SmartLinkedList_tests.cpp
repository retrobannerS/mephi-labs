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
    for(int i = 0; i < 5; i++) {
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
    for(int i = 0; i < 5; i++) {
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
    for(int i = 0; i < 5; i++) {
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
    for(int i = 0; i < 5; i++) {
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
    for(int i = 0; i < 5; i++) {
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
    for(int i = 0; i < 5; i++) {
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
    for(int i = 0; i < 5; i++) {
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







