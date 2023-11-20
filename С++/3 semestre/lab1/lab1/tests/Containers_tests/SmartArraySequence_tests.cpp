#include "containers/SmartArraySequence.hpp"
#include "gtest/gtest.h"

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

TEST(SmartArraySequence, GetMethod) {
    // Arrange
    auto sequence = testSequence();
    int index = 5;

    // Act

    // Assert
    EXPECT_EQ(sequence->get(index), "TEST" + std::to_string(index));
}

TEST(SmartArraySequence, GetMethodWithNegativeIndex) {
    // Arrange
    auto sequence = testSequence();
    int index = -5;

    // Act

    // Assert
    EXPECT_THROW(sequence->get(index), std::out_of_range);
}

TEST(SmartArraySequence, GetMethodWithIndexGreaterThanSize) {
    // Arrange
    auto sequence = testSequence();
    int index = sequence->getSize() + 5;

    // Act

    // Assert
    EXPECT_THROW(sequence->get(index), std::out_of_range);
}

TEST(SmartArraySequence, GetFirstMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_EQ(sequence->getFirst(), "TEST0");
}

TEST(SmartArraySequence, GetFirstMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act

    // Assert
    EXPECT_THROW(sequence->getFirst(), std::out_of_range);
}

TEST(SmartArraySequence, GetLastMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_EQ(sequence->getLast(), "TEST9");
}

TEST(SmartArraySequence, GetLastMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act

    // Assert
    EXPECT_THROW(sequence->getLast(), std::out_of_range);
}

TEST(SmartArraySequence, GetSizeMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_EQ(sequence->getSize(), 10);
}

TEST(SmartArraySequence, GetSizeMethodZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act

    // Assert
    EXPECT_EQ(sequence->getSize(), 0);
}

TEST(SmartArraySequence, GetCapacityMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_EQ(sequence->getCapacity(), 20);
}

TEST(SmartArraySequence, GetCapacityMethodZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>();

    // Act

    // Assert
    EXPECT_EQ(sequence->getCapacity(), 3);
}

TEST(SmartArraySequence, GetSubSequenceMethod) {
    // Arrange
    auto sequence = testSequence();
    int startIndex = 2;
    int endIndex = 5;

    // Act
    auto subSequence = sequence->getSubSequence(startIndex, endIndex);

    // Assert
    EXPECT_EQ(subSequence->getSize(), endIndex - startIndex);
    for (int i = 0; i < subSequence->getSize(); i++) {
        EXPECT_EQ(subSequence->get(i), "TEST" + std::to_string(i + startIndex));
    }
}

TEST(SmartArraySequence, GetSubSequenceMethodExceptions) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_THROW(sequence->getSubSequence(-1, 5), std::out_of_range);
    EXPECT_THROW(sequence->getSubSequence(2, 1), std::invalid_argument);
    EXPECT_THROW(sequence->getSubSequence(0, 11), std::out_of_range);
    EXPECT_THROW(sequence->getSubSequence(10, 10), std::out_of_range);
    EXPECT_THROW(sequence->getSubSequence(2, -1), std::out_of_range);
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

TEST(SmartArraySequence, InsertAtMethod) {
    // Arrange
    auto sequence = testSequence();
    int index = 5;
    std::string item = "TEST";

    // Act
    sequence->insertAt(index, item);

    // Assert
    EXPECT_EQ(sequence->getSize(), 11);
    EXPECT_EQ(sequence->getCapacity(), 20);
    for (int i = 0; i < index; i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }
    EXPECT_EQ(sequence->get(index), item);
    for (int i = index + 1; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i - 1));
    }
}

TEST(SmartArraySequence, InsertAtMethodExceptions) {
    // Arrange
    auto sequence = testSequence();
    auto sequence2 = make_shared<SmartArraySequence<std::string>>();

    // Act

    // Assert
    EXPECT_THROW(sequence->insertAt(-1, "TEST"), std::out_of_range);
    EXPECT_THROW(sequence->insertAt(11, "TEST"), std::out_of_range);
    EXPECT_THROW(sequence2->insertAt(1, "TEST"), std::out_of_range);
}

TEST(SmartArraySequence, AppendMethod) {
    auto sequence = make_shared<SmartArraySequence<std::string>>();
    sequence->append("TEST");
    EXPECT_EQ(sequence->getSize(), 1);
    EXPECT_EQ(sequence->get(0), "TEST");
    EXPECT_EQ(sequence->getCapacity(), 3);
    sequence->append("TEST");
    sequence->append("TEST");
    EXPECT_EQ(sequence->getSize(), 3);
    EXPECT_EQ(sequence->get(0), "TEST");
    EXPECT_EQ(sequence->get(1), "TEST");
    EXPECT_EQ(sequence->get(2), "TEST");
    EXPECT_EQ(sequence->getCapacity(), 3);
    sequence->append("TEST");
    EXPECT_EQ(sequence->getSize(), 4);
    EXPECT_EQ(sequence->getCapacity(), 6);
}

TEST(SmartArraySequence, PrependMethod) {
    auto sequence = make_shared<SmartArraySequence<std::string>>();
    sequence->prepend("TEST");
    EXPECT_EQ(sequence->getSize(), 1);
    EXPECT_EQ(sequence->get(0), "TEST");
    EXPECT_EQ(sequence->getCapacity(), 3);
    sequence->prepend("TEST");
    sequence->prepend("TEST");
    EXPECT_EQ(sequence->getSize(), 3);
    EXPECT_EQ(sequence->get(0), "TEST");
    EXPECT_EQ(sequence->get(1), "TEST");
    EXPECT_EQ(sequence->get(2), "TEST");
    EXPECT_EQ(sequence->getCapacity(), 3);
    sequence->prepend("TEST");
    EXPECT_EQ(sequence->getSize(), 4);
    EXPECT_EQ(sequence->getCapacity(), 6);
}

TEST(SmartArraySequence, RemoveAtMethod) {
    // Arrange
    auto sequence = testSequence();
    int index = 5;

    // Act
    sequence->removeAt(index);

    // Assert
    EXPECT_EQ(sequence->getSize(), 9);
    EXPECT_EQ(sequence->getCapacity(), 20);
    for (int i = 0; i < index; i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }
    for (int i = index; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i + 1));
    }
}

TEST(SmartArraySequence, RemoveAtMethodExceptions) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_THROW(sequence->removeAt(-1), std::out_of_range);
    EXPECT_THROW(sequence->removeAt(10), std::out_of_range);
    EXPECT_THROW(sequence->removeAt(11), std::out_of_range);
}

TEST(SmartArraySequence, RemoveFirstMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act
    sequence->removeFirst();

    // Assert
    EXPECT_EQ(sequence->getSize(), 9);
    EXPECT_EQ(sequence->getCapacity(), 20);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i + 1));
    }

    // Act
    sequence->removeFirst();
    sequence->removeFirst();
    sequence->removeFirst();
    EXPECT_EQ(sequence->getSize(), 6);
    EXPECT_EQ(sequence->getCapacity(), 10);
}

TEST(SmartArraySequence, RemoveFirstMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act

    // Assert
    EXPECT_THROW(sequence->removeFirst(), std::out_of_range);
}

TEST(SmartArraySequence, RemoveLastMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act
    sequence->removeLast();

    // Assert
    EXPECT_EQ(sequence->getSize(), 9);
    EXPECT_EQ(sequence->getCapacity(), 20);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }

    // Act
    sequence->removeLast();
    sequence->removeLast();
    sequence->removeLast();
    EXPECT_EQ(sequence->getSize(), 6);
    EXPECT_EQ(sequence->getCapacity(), 10);
}

TEST(SmartArraySequence, RemoveLastMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act

    // Assert
    EXPECT_THROW(sequence->removeLast(), std::out_of_range);
}

TEST(SmartArraySequence, OperatorSquareBrackets) {
    // Arrange
    auto sequence = testSequence();
    int index = 5;

    // Act
    (*sequence)[index + 1] = "TEST";

    // Assert
    EXPECT_EQ((*sequence)[index], "TEST" + std::to_string(index));
    EXPECT_EQ((*sequence)[index + 1], "TEST");
}

TEST(SmartArraySequence, OperatorSquareBracketsWithNegativeIndex) {
    // Arrange
    auto sequence = testSequence();
    int index = -5;

    // Act

    // Assert
    EXPECT_THROW((*sequence)[index], std::out_of_range);
}

TEST(SmartArraySequence, OperatorSquareBracketsWithIndexGreaterThanSize) {
    // Arrange
    auto sequence = testSequence();
    int index = sequence->getSize() + 5;

    // Act

    // Assert
    EXPECT_THROW((*sequence)[index], std::out_of_range);
}

TEST(SmartArraySequence, OperatorSquareBracketsWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    int index = 0;

    // Act

    // Assert
    EXPECT_THROW((*sequence)[index], std::out_of_range);
}

TEST(SmartArraySequence, OperatorPlus) {
    // Arrange
    auto sequence = testSequence();
    auto sequence2 = testSequence();

    // Act
    auto new_sequence = *sequence + *sequence2;

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence2->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence2->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, OperatorPlusWithZeroSize) {
    // Arrange
    auto sequence = testSequence();
    auto sequence2 = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    auto new_sequence = *sequence + *sequence2;

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence2->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence2->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, OperatorPlusWithSelf) {
    // Arrange
    auto sequence = testSequence();

    // Act
    auto new_sequence = *sequence + *sequence;

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, OperatorPlusWithZeroSelf) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    auto new_sequence = *sequence + *sequence;

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, ConcatMethod) {
    // Arrange
    auto sequence = testSequence();
    auto sequence2 = testSequence();

    // Act
    auto new_sequence = sequence->concat(*sequence2);

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence2->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence2->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, ConcatMethodWithZeroSize) {
    // Arrange
    auto sequence = testSequence();
    auto sequence2 = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    auto new_sequence = sequence->concat(*sequence2);

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence2->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence2->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, ConcatMethodWithSelf) {
    // Arrange
    auto sequence = testSequence();

    // Act
    SharedPtr<SmartSequence<std::string>> new_sequence = sequence->concat(*sequence);

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, ConcatMethodWithZeroSelf) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    auto new_sequence = sequence->concat(*sequence);

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize() + sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i));
    }
    for (int i = sequence->getSize(); i < new_sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i - sequence->getSize()));
    }
}

TEST(SmartArraySequence, ResizeMethod) {
    // Arrange
    auto sequence = testSequence();
    int newSize = 5;

    // Act
    sequence->resize(newSize);

    // Assert
    EXPECT_EQ(sequence->getSize(), newSize);
    EXPECT_EQ(sequence->getCapacity(), 10);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }

    // Act
    sequence->resize(10);
    EXPECT_EQ(sequence->getSize(), 10);
    EXPECT_EQ(sequence->getCapacity(), 20);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }
    for (int i = 5; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "");
    }
}

TEST(SmartArraySequence, ResizeMethodWithZeroSize) {
    // Arrange
    auto sequence = testSequence();
    int newSize = 0;

    // Act
    sequence->resize(newSize);

    // Assert
    EXPECT_EQ(sequence->getSize(), newSize);
    EXPECT_EQ(sequence->getCapacity(), 3);
}

TEST(SmartArraySequence, ResizeMethodWithNegativeSize) {
    // Arrange
    auto sequence = testSequence();
    int newSize = -5;

    // Act

    // Assert
    EXPECT_THROW(sequence->resize(newSize), std::invalid_argument);
}

TEST(SmartArraySequence, ResizeMethodWithItem) {
    // Arrange
    auto sequence = testSequence();
    int newSize = 5;
    std::string item = "TEST";

    // Act
    sequence->resize(newSize, item);

    // Assert
    EXPECT_EQ(sequence->getSize(), newSize);
    EXPECT_EQ(sequence->getCapacity(), 10);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }

    // Act
    sequence->resize(10, item);
    EXPECT_EQ(sequence->getSize(), 10);
    EXPECT_EQ(sequence->getCapacity(), 20);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }
    for (int i = 5; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), item);
    }
}

TEST(SmartArraySequence, ResizeMethodWithZeroSizeAndItem) {
    // Arrange
    auto sequence = testSequence();
    int newSize = 0;
    std::string item = "TEST";

    // Act
    sequence->resize(newSize, item);

    // Assert
    EXPECT_EQ(sequence->getSize(), newSize);
    EXPECT_EQ(sequence->getCapacity(), 3);
}

TEST(SmartArraySequence, ResizeMethodWithNegativeSizeAndItem) {
    // Arrange
    auto sequence = testSequence();
    int newSize = -5;
    std::string item = "TEST";

    // Act

    // Assert
    EXPECT_THROW(sequence->resize(newSize, item), std::invalid_argument);
}

TEST(SmartArraySequence, ReserveMethod) {
    // Arrange
    auto sequence = testSequence();
    int newCapacity = 30;

    // Act
    sequence->reserve(newCapacity);

    // Assert
    EXPECT_EQ(sequence->getSize(), 10);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }

    // Act
    sequence->reserve(10);

    // Assert
    EXPECT_EQ(sequence->getSize(), 10);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(sequence->get(i), "TEST" + std::to_string(i));
    }

    // Act & Assert
    sequence->reserve(30);
    EXPECT_EQ(sequence->getSize(), 10);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
    sequence->append("TEST");
    EXPECT_EQ(sequence->getSize(), 11);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
    sequence->append("TEST");
    EXPECT_EQ(sequence->getSize(), 12);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
    sequence->append("TEST");
    EXPECT_EQ(sequence->getSize(), 13);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
    sequence->reserve(50);
    EXPECT_EQ(sequence->getSize(), 13);
    EXPECT_EQ(sequence->getCapacity(), 50);
    sequence->removeFirst();
    EXPECT_EQ(sequence->getSize(), 12);
    EXPECT_EQ(sequence->getCapacity(), 25);
}

TEST(SmartArraySequence, ReserveMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    int newCapacity = 30;

    // Act
    sequence->reserve(newCapacity);

    // Assert
    EXPECT_EQ(sequence->getSize(), 0);
    EXPECT_EQ(sequence->getCapacity(), newCapacity);
}

TEST(SmartArraySequence, ReserveMethodWithNegativeSize) {
    // Arrange
    auto sequence = testSequence();
    int newCapacity = -30;

    // Act

    // Assert
    EXPECT_THROW(sequence->reserve(newCapacity), std::invalid_argument);
}

TEST(SmartArraySequence, ClearMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act
    sequence->clear();

    // Assert
    EXPECT_EQ(sequence->getSize(), 0);
    EXPECT_EQ(sequence->getCapacity(), 3);
}

TEST(SmartArraySequence, EmptyMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act

    // Assert
    EXPECT_FALSE(sequence->empty());

    // Act
    sequence->clear();

    // Assert
    EXPECT_TRUE(sequence->empty());
}

TEST(SmartArraySequence, FindMethod) {
    // Arrange
    auto sequence = testSequence();
    std::string item = "TEST5";

    // Act

    // Assert
    EXPECT_EQ(sequence->find(item), 5);
}

TEST(SmartArraySequence, FindMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    std::string item = "TEST5";

    // Act

    // Assert
    EXPECT_THROW(sequence->find(item), std::invalid_argument);
}

TEST(SmartArraySequence, MapMethod) {
    // Arrange
    auto sequence = testSequence();
    auto function = [](const std::string &item) -> std::string { return item + "TEST"; };

    // Act
    auto new_sequence = sequence->map(function);
    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i) + "TEST");
    }
}

TEST(SmartArraySequence, MapMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    auto function = [](const std::string &item) -> std::string { return item + "TEST"; };

    // Act
    auto new_sequence = sequence->map(function);
    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize());
}

TEST(SmartArraySequence, WhereMethod) {
    // Arrange
    auto sequence = testSequence();
    auto function = [](const std::string &item) -> bool { return item == "TEST5"; };

    // Act
    auto new_sequence = sequence->where(function);
    // Assert
    EXPECT_EQ(new_sequence->getSize(), 1);
    EXPECT_EQ(new_sequence->get(0), "TEST5");
}

TEST(SmartArraySequence, WhereMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    auto function = [](const std::string &item) -> bool { return item == "TEST5"; };

    // Act
    auto new_sequence = sequence->where(function);
    // Assert
    EXPECT_EQ(new_sequence->getSize(), 0);
}

TEST(SmartArraySequence, ReduceMethod) {
    // Arrange
    auto sequence = testSequence();
    auto function = [](const std::string &item1, const std::string &item2) -> std::string { return item1 + item2; };

    // Act
    auto result = sequence->reduce(function, "");
    // Assert
    EXPECT_EQ(result, "TEST0TEST1TEST2TEST3TEST4TEST5TEST6TEST7TEST8TEST9");
}

TEST(SmartArraySequence, ReduceMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    auto function = [](const std::string &item1, const std::string &item2) -> std::string { return item1 + item2; };

    // Act
    auto result = sequence->reduce(function, "");
    // Assert
    EXPECT_EQ(result, "");
}

TEST(SmartArraySequence, TryGetMethod) {
    // Arrange
    auto sequence = testSequence();
    int index = 5;

    // Act
    auto result = sequence->tryGet(index);

    // Assert
    EXPECT_EQ(result.HasValue(), true);
    EXPECT_EQ(result.Value(), "TEST" + std::to_string(index));
}

TEST(SmartArraySequence, TryGetMethodWithNegativeIndex) {
    // Arrange
    auto sequence = testSequence();
    int index = -5;

    // Act
    auto result = sequence->tryGet(index);

    // Assert
    EXPECT_EQ(result.HasValue(), false);
}

TEST(SmartArraySequence, TryGetMethodWithIndexGreaterThanSize) {
    // Arrange
    auto sequence = testSequence();
    int index = sequence->getSize() + 5;

    // Act
    auto result = sequence->tryGet(index);

    // Assert
    EXPECT_EQ(result.HasValue(), false);
}

TEST(SmartArraySequence, TryGetMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    int index = 0;

    // Act
    auto result = sequence->tryGet(index);

    // Assert
    EXPECT_EQ(result.HasValue(), false);
}

TEST(SmartArraySequence, TryGetFirstMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act
    auto result = sequence->tryGetFirst();

    // Assert
    EXPECT_EQ(result.HasValue(), true);
    EXPECT_EQ(result.Value(), "TEST0");
}

TEST(SmartArraySequence, TryGetFirstMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    auto result = sequence->tryGetFirst();

    // Assert
    EXPECT_EQ(result.HasValue(), false);
}

TEST(SmartArraySequence, TryGetLastMethod) {
    // Arrange
    auto sequence = testSequence();

    // Act
    auto result = sequence->tryGetLast();

    // Assert
    EXPECT_EQ(result.HasValue(), true);
    EXPECT_EQ(result.Value(), "TEST9");
}

TEST(SmartArraySequence, TryGetLastMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);

    // Act
    auto result = sequence->tryGetLast();

    // Assert
    EXPECT_EQ(result.HasValue(), false);
}

TEST(SmartArraySequence, TryFindMethod) {
    // Arrange
    auto sequence = testSequence();
    std::string item = "TEST5";

    // Act
    auto result = sequence->tryFind(item);

    // Assert
    EXPECT_EQ(result.HasValue(), true);
    EXPECT_EQ(result.Value(), 5);
}

TEST(SmartArraySequence, TryFindMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartArraySequence<std::string>>(0);
    std::string item = "TEST5";

    // Act
    auto result = sequence->tryFind(item);

    // Assert
    EXPECT_EQ(result.HasValue(), false);
}