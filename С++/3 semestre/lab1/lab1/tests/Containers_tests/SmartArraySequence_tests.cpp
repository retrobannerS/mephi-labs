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

TEST(SmartArraySequence, ConstructorWithSmartSequence) {
    // Arrange
    auto test_sequence = make_shared<SmartArraySequence<int>>(10);
    SmartSequence<int> *sequence = test_sequence.get();

    // Act
    SmartArraySequence<int> new_sequence(sequence);

    // Assert
    EXPECT_EQ(new_sequence.getSize(), sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence.get(i), sequence->get(i));
    }
}

TEST(SmartArraySequence, ConstructorWithZeroSmartSequence) {
    // Arrange
    auto test_sequence = make_shared<SmartArraySequence<int>>(0);
    SmartSequence<int> *sequence = test_sequence.get();

    // Act
    SmartArraySequence<int> new_sequence(sequence);

    // Assert
    EXPECT_EQ(new_sequence.getSize(), sequence->getSize());
}

TEST(SmartArraySequence, ConstructorWithSequence) {
    // Arrange
    auto test_sequence = make_shared<ArraySequence<int>>(10);
    Sequence<int> *sequence = test_sequence.get();

    // Act
    SmartArraySequence<int> new_sequence(sequence);

    // Assert
    EXPECT_EQ(new_sequence.getSize(), sequence->GetSize());
    for (int i = 0; i < sequence->GetSize(); i++) {
        EXPECT_EQ(new_sequence.get(i), sequence->Get(i));
    }
}

TEST(SmartArraySequence, ConstructorWithZeroSequence) {
    // Arrange
    auto test_sequence = make_shared<ArraySequence<int>>(0);
    Sequence<int> *sequence = test_sequence.get();

    // Act
    SmartArraySequence<int> new_sequence(sequence);

    // Assert
    EXPECT_EQ(new_sequence.getSize(), sequence->GetSize());
}

TEST(SmartArraySequence, CopyConstructor) {
    // Arrange
    auto sequence = testSequence();

    // Act
    SmartArraySequence<std::string> new_sequence(*sequence);

    // Assert
    EXPECT_EQ(new_sequence.getSize(), sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence.get(i), sequence->get(i));
    }
}

TEST(SmartArraySequence, CopyConstructorWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    SmartArraySequence<std::string> new_sequence(*sequence);

    // Assert
    EXPECT_EQ(new_sequence.getSize(), sequence->getSize());
}

TEST(SmartArraySequence, MoveConstructor) {
    // Arrange
    auto sequence = testSequence();

    // Act
    SmartArraySequence<std::string> new_sequence(std::move(*sequence));

    // Assert
    EXPECT_EQ(new_sequence.getSize(), 10);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence.get(i), "TEST" + std::to_string(i));
    }
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(SmartArraySequence, MoveConstructorWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    SmartArraySequence<std::string> new_sequence(std::move(*sequence));

    // Assert
    EXPECT_EQ(new_sequence.getSize(), 0);
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(SmartArraySequence, AssignmentOperator) {
    // Arrange
    auto sequence = testSequence();
    auto new_sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    *new_sequence = *sequence;

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
}

TEST(SmartArraySequence, AssignmentOperatorWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    auto new_sequence = make_shared<SmartArraySequence<std::string>>(10);

    // Act
    *new_sequence = *sequence;

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize());
}

TEST(SmartArraySequence, MoveAssignmentOperator) {
    // Arrange
    auto sequence = testSequence();
    auto new_sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    *new_sequence = std::move(*sequence);

    // Assert
    EXPECT_EQ(new_sequence->getSize(), 10);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), "TEST" + std::to_string(i));
    }
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(SmartArraySequence, MoveAssignmentOperatorWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    auto new_sequence = make_shared<SmartArraySequence<std::string>>(10);

    // Act
    *new_sequence = std::move(*sequence);

    // Assert
    EXPECT_EQ(new_sequence->getSize(), 0);
    EXPECT_EQ(sequence->getSize(), 0);
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

TEST(SmartArraySequence, SetMethodWithNegativeIndex) {
    // Arrange
    auto sequence = testSequence();
    int index = -5;
    std::string item = "TEST";

    // Act

    // Assert
    EXPECT_THROW(sequence->set(index, item), std::out_of_range);
}

TEST(SmartArraySequence, SetMethodWithIndexGreaterThanSize) {
    // Arrange
    auto sequence = testSequence();
    int index = sequence->getSize() + 5;
    std::string item = "TEST";

    // Act

    // Assert
    EXPECT_THROW(sequence->set(index, item), std::out_of_range);
}

TEST(SmartArraySequence, SetMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    int index = 0;
    std::string item = "TEST";

    // Act

    // Assert
    EXPECT_THROW(sequence->set(index, item), std::out_of_range);
}

TEST(SmartArraySequence, RangeSetMethod) {
    // Arrange
    auto sequence = testSequence();
    int startIndex = 2;
    int endIndex = 5;
    std::string item = "TEST";

    // Act
    sequence->set(startIndex, endIndex, item);

    // Assert
    for (int i = 0; i < startIndex; i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }
    for (int i = startIndex; i < endIndex; i++) {
        EXPECT_EQ(sequence->get(i), item);
    }
    for (int i = endIndex; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }
}

TEST(SmartArraySequence, RangeSetMethodExceptions) {
    // Arrange
    auto sequence = testSequence();


    // Assert
    EXPECT_THROW(sequence->set(-1, 5, "TEST10"), std::out_of_range);
    EXPECT_THROW(sequence->set(2, 1, "TEST10"), std::invalid_argument);
    EXPECT_THROW(sequence->set(0, 11, "TEST10"), std::out_of_range);
    EXPECT_THROW(sequence->set(10, 10, "TEST10"), std::out_of_range);
    EXPECT_THROW(sequence->set(2, -1, "TEST10"), std::out_of_range);
}





