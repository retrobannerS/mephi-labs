#include "gtest/gtest.h"
#include "containers/SmartArraySequence.hpp"


using namespace sem3;

SharedPtr<SmartArraySequence<std::string>> testSequence() {
    auto sequence = make_shared<SmartArraySequence<std::string>>(10);
    for (int i = 0; i < sequence->getSize(); i++) {
        (*sequence)[i] = "TEST" + std::to_string(i);
    }
    return sequence;
}

TEST(SmartArraySequence, DefaultConstructor) {
    // Arrange
    SmartArraySequence<int> sequence;

    // Act

    // Assert
    EXPECT_EQ(sequence.getSize(), 0);
}

TEST(SmartArraySequence, ConstructorWithSize) {
    // Arrange
    int size = 10;

    // Act
    SmartArraySequence<int> sequence(size);

    // Assert
    EXPECT_EQ(sequence.getSize(), size);
}

TEST(SmartArraySequence, ConstructorWithZeroSize) {
    // Arrange
    int size = 0;

    // Act
    SmartArraySequence<int> sequence(size);

    // Assert
    EXPECT_EQ(sequence.getSize(), size);
}

TEST(SmartArraySequence, ConstructorWithNegativeSize) {
    // Arrange
    int size = -10;

    // Act

    // Assert
    EXPECT_THROW(SmartArraySequence<int> sequence(size), std::invalid_argument);
}

TEST(SmartArraySequence, ConstructorWithSizeAndItem) {
    // Arrange
    int size = 10;
    int item = 5;

    // Act
    SmartArraySequence<int> sequence(size, item);

    // Assert
    EXPECT_EQ(sequence.getSize(), size);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(sequence.get(i), item);
    }
}

TEST(SmartArraySequence, ConstructorWithZeroSizeAndItem) {
    // Arrange
    int size = 0;
    int item = 5;

    // Act
    SmartArraySequence<int> sequence(size, item);

    // Assert
    EXPECT_EQ(sequence.getSize(), size);
}

TEST(SmartArraySequence, ConstructorWithNegativeSizeAndItem) {
    // Arrange
    int size = -10;
    int item = 5;

    // Act

    // Assert
    EXPECT_THROW(SmartArraySequence<int> sequence(size, item), std::invalid_argument);
}

TEST(SmartArraySequence, ConstructorWithSizeAndItems) {
    // Arrange
    int size = 10;
    auto items = make_shared<int[]>(size);
    for (int i = 0; i < size; i++) {
        items[i] = i;
    }

    // Act
    SmartArraySequence<int> sequence(size, items.get());

    // Assert
    EXPECT_EQ(sequence.getSize(), size);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(sequence.get(i), items[i]);
    }
}

TEST(SmartArraySequence, ConstructorWithZeroSizeAndItems) {
    // Arrange
    int size = 0;
    auto items = make_shared<int[]>(size);
    for (int i = 0; i < size; i++) {
        items[i] = i;
    }

    // Act
    SmartArraySequence<int> sequence(size, items.get());

    // Assert
    EXPECT_EQ(sequence.getSize(), size);
}

TEST(SmartArraySequence, ConstructorWithNegativeSizeAndItems) {
    // Arrange
    int size = -10;
    auto items = make_shared<int[]>(10);
    for (int i = 0; i < size; i++) {
        items[i] = i;
    }

    // Act

    // Assert
    EXPECT_THROW(SmartArraySequence<int> sequence(size, items.get()), std::invalid_argument);
}

TEST(SmartArraySequence, ConstructorWithArray) {
    // Arrange
    auto array = make_shared<SmartDynamicArray<int>>(10);
    for (int i = 0; i < array->getSize(); i++) {
        (*array)[i] = i;
    }

    // Act
    SmartArraySequence<int> sequence(*array);

    // Assert
    EXPECT_EQ(sequence.getSize(), array->getSize());
    for (int i = 0; i < array->getSize(); i++) {
        EXPECT_EQ(sequence.get(i), (*array)[i]);
    }
}

TEST(SmartArraySequence, ConstructorWithZeroArray) {
    // Arrange
    auto array = make_shared<SmartDynamicArray<int>>(0);

    // Act
    SmartArraySequence<int> sequence(*array);

    // Assert
    EXPECT_EQ(sequence.getSize(), array->getSize());
}

TEST(SmartArraySequence, ConstructorWithList) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>();
    for (int i = 0; i < 10; i++) {
        list->append(i);
    }

    // Act
    SmartArraySequence<int> sequence(*list);

    // Assert
    EXPECT_EQ(sequence.getSize(), list->getSize());
    for (int i = 0; i < list->getSize(); i++) {
        EXPECT_EQ(sequence.get(i), list->get(i));
    }
}

TEST(SmartArraySequence, ConstructorWithZeroList) {
    // Arrange
    auto list = make_shared<SmartLinkedList<int>>();

    // Act
    SmartArraySequence<int> sequence(*list);

    // Assert
    EXPECT_EQ(sequence.getSize(), list->getSize());
}

TEST(SmartArraySequence, ConstructorWithArraySequence) {
    // Arrange
    auto array = make_shared<ArraySequence<int>>(10);
    for (int i = 0; i < array->GetSize(); i++) {
        (*array)[i] = i;
    }

    // Act
    SmartArraySequence<int> sequence(*array);

    // Assert
    EXPECT_EQ(sequence.getSize(), array->GetSize());
    for (int i = 0; i < array->GetSize(); i++) {
        EXPECT_EQ(sequence.get(i), (*array)[i]);
    }
}

TEST(SmartArraySequence, ConstructorWithZeroArraySequence) {
    // Arrange
    auto array = make_shared<ArraySequence<int>>(0);

    // Act
    SmartArraySequence<int> sequence(*array);

    // Assert
    EXPECT_EQ(sequence.getSize(), array->GetSize());
}



TEST(SmartArraySequence, SetMethod) {
    // Arrange
    auto sequence = testSequence();
    int index = 5;
    std::string item = "TEST";

    // Act
    sequence->set(index, item);

    // Assert
    EXPECT_EQ(sequence->get(index), item);
}



