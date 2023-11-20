#include "containers/SmartArraySequence.hpp"
#include "containers/SmartListSequence.hpp"
#include "smart_pointers/SharedPtr.hpp"
#include "gtest/gtest.h"

using namespace sem3;

SharedPtr<SmartListSequence<std::string>> testListSequence() {
    auto sequence = make_shared<SmartListSequence<std::string>>();
    for (int i = 0; i < 10; i++) {
        sequence->append("TEST" + std::to_string(i));
    }
    return sequence;
}

TEST(SmartListSequence, DefaultConstructor) {
    // Arrange
    sem3::SmartListSequence<int> list;

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithSize) {
    // Arrange
    sem3::SmartListSequence<int> list(5);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
}

TEST(SmartListSequence, ConstructorWithZeroSize) {
    // Arrange
    sem3::SmartListSequence<int> list(0);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithNegativeSize) {
    EXPECT_THROW(sem3::SmartListSequence<int> list(-1), std::invalid_argument);
}

TEST(SmartListSequence, ConstructorWithAndItem) {
    // Arrange
    sem3::SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }
}

TEST(SmartListSequence, ConstructorWithZeroSizeAndItem) {
    // Arrange
    sem3::SmartListSequence<int> list(0, 5);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithNegativeSizeAndItem) {
    EXPECT_THROW(sem3::SmartListSequence<int> list(-1, 5), std::invalid_argument);
}

TEST(SmartListSequence, ConstructorWithSizeAndItems) {
    // Arrange
    auto items = make_shared<int[]>(5);
    for (int i = 0; i < 5; i++) {
        items[i] = i;
    }

    // Act
    sem3::SmartListSequence<int> list(5, items.get());

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), i);
    }
}

TEST(SmartListSequence, ConstructorWithZeroSizeAndItems) {
    // Arrange
    auto items = make_shared<int[]>(5);
    for (int i = 0; i < 5; i++) {
        items[i] = i;
    }

    // Act
    sem3::SmartListSequence<int> list(0, items.get());

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithNegativeSizeAndItems) {
    // Arrange
    auto items = make_shared<int[]>(5);
    for (int i = 0; i < 5; i++) {
        items[i] = i;
    }

    // Act

    // Assert
    EXPECT_THROW(sem3::SmartListSequence<int> list(-1, items.get()), std::invalid_argument);
}

TEST(SmartListSequence, ConstructorWithSmartLinkedList) {
    // Arrange
    SmartLinkedList<int> linkedList(5, 5);

    // Act
    SmartListSequence<int> list(linkedList);

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }
}

TEST(SmartListSequence, ConstructorWithZeroSmartLinkedList) {
    // Arrange
    SmartLinkedList<int> linkedList(0, 5);

    // Act
    SmartListSequence<int> list(linkedList);

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithSmartDynamicArray) {
    // Arrange
    SmartDynamicArray<int> array(5, 5);

    // Act
    SmartListSequence<int> list(array);

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }
}

TEST(SmartListSequence, ConstructorWithZeroSmartDynamicArray) {
    // Arrange
    SmartDynamicArray<int> array(0, 5);

    // Act
    SmartListSequence<int> list(array);

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithListSequence) {
    // Arrange
    lab2::ListSequence<int> listSequence(5, 5);

    // Act
    SmartListSequence<int> list(listSequence);

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }
}

TEST(SmartListSequence, ConstructorWithZeroListSequence) {
    // Arrange
    lab2::ListSequence<int> listSequence(0, 5);

    // Act
    SmartListSequence<int> list(listSequence);

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithSmartSequence) {
    // Arrange
    SmartSequence<int> *smartSequence = new SmartArraySequence<int>(5, 5);
    SharedPtr<SmartSequence<int>> smartSequencePtr(smartSequence);

    // Act
    SmartListSequence<int> list(smartSequencePtr.get());

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }
}

TEST(SmartListSequence, ConstructorWithZeroSmartSequence) {
    // Arrange
    SmartSequence<int> *smartSequence = new SmartArraySequence<int>(0, 5);
    SharedPtr<SmartSequence<int>> smartSequencePtr(smartSequence);

    // Act
    SmartListSequence<int> list(smartSequencePtr.get());

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, ConstructorWithSequence) {
    // Arrange
    Sequence<int> *sequence = new ArraySequence<int>(5, 5);

    // Act
    SmartListSequence<int> list(sequence);

    // Assert
    EXPECT_EQ(list.getSize(), 5);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }

    delete sequence;
}

TEST(SmartListSequence, ConstructorWithZeroSequence) {
    // Arrange
    Sequence<int> *sequence = new ArraySequence<int>(0, 5);

    // Act
    SmartListSequence<int> list(sequence);

    // Assert
    EXPECT_EQ(list.getSize(), 0);

    delete sequence;
}

TEST(SmartListSequence, CopyConstructor) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act
    SmartListSequence<int> listCopy(list);

    // Assert
    EXPECT_EQ(listCopy.getSize(), 5);
    for (int i = 0; i < listCopy.getSize(); i++) {
        EXPECT_EQ(listCopy.get(i), 5);
    }
}

TEST(SmartListSequence, CopyConstructorZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);

    // Act
    SmartListSequence<int> listCopy(list);

    // Assert
    EXPECT_EQ(listCopy.getSize(), 0);
}

TEST(SmartListSequence, MoveConstructor) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act
    SmartListSequence<int> listCopy(std::move(list));

    // Assert
    EXPECT_EQ(listCopy.getSize(), 5);
    for (int i = 0; i < listCopy.getSize(); i++) {
        EXPECT_EQ(listCopy.get(i), 5);
    }
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, MoveConstructorZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);

    // Act
    SmartListSequence<int> listCopy(std::move(list));

    // Assert
    EXPECT_EQ(listCopy.getSize(), 0);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, AssignmentOperator) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    SmartListSequence<int> listCopy;

    // Act
    listCopy = list;

    // Assert
    EXPECT_EQ(listCopy.getSize(), 5);
    for (int i = 0; i < listCopy.getSize(); i++) {
        EXPECT_EQ(listCopy.get(i), 5);
    }
}

TEST(SmartListSequence, AssignmentOperatorZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);
    SmartListSequence<int> listCopy;

    // Act
    listCopy = list;

    // Assert
    EXPECT_EQ(listCopy.getSize(), 0);
}

TEST(SmartListSequence, MoveAssignmentOperator) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    SmartListSequence<int> listCopy;

    // Act
    listCopy = std::move(list);

    // Assert
    EXPECT_EQ(listCopy.getSize(), 5);
    for (int i = 0; i < listCopy.getSize(); i++) {
        EXPECT_EQ(listCopy.get(i), 5);
    }
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, MoveAssignmentOperatorZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);
    SmartListSequence<int> listCopy;

    // Act
    listCopy = std::move(list);

    // Assert
    EXPECT_EQ(listCopy.getSize(), 0);
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, GetMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), 5);
    }
}

TEST(SmartListSequence, GetMethodWithIndexOutOfBounds) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    EXPECT_THROW(list.get(5), std::out_of_range);
}

TEST(SmartListSequence, GetMethodWithNegativeIndex) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    EXPECT_THROW(list.get(-1), std::out_of_range);
}

TEST(SmartListSequence, GetFirstMethod) {
    // Arrange
    SmartListSequence<int> list;
    for (int i = 0; i < 5; i++) {
        list.append(i);
    }

    // Act

    // Assert
    EXPECT_EQ(list.getFirst(), 0);
}

TEST(SmartListSequence, GetFirstMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list;

    // Act

    // Assert
    EXPECT_THROW(list.getFirst(), std::out_of_range);
}

TEST(SmartListSequence, GetLastMethod) {
    // Arrange
    SmartListSequence<int> list;
    for (int i = 0; i < 5; i++) {
        list.append(i);
    }

    // Act

    // Assert
    EXPECT_EQ(list.getLast(), 4);
}

TEST(SmartListSequence, GetLastMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list;

    // Act

    // Assert
    EXPECT_THROW(list.getLast(), std::out_of_range);
}

TEST(SmartListSequence, GetSizeMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 5);
}

TEST(SmartListSequence, GetSizeMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);

    // Act

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, GetSubSequenceMethod) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>();
    for (int i = 0; i < 10; i++) {
        sequence->append("TEST" + std::to_string(i));
    }
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

TEST(SmartListSequence, GetSubSequenceMethodExceptions) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>();
    for (int i = 0; i < 10; i++) {
        sequence->append("TEST" + std::to_string(i));
    }

    // Act

    // Assert
    EXPECT_THROW(sequence->getSubSequence(-1, 5), std::out_of_range);
    EXPECT_THROW(sequence->getSubSequence(2, 1), std::invalid_argument);
    EXPECT_THROW(sequence->getSubSequence(0, 11), std::out_of_range);
    EXPECT_THROW(sequence->getSubSequence(10, 10), std::out_of_range);
    EXPECT_THROW(sequence->getSubSequence(2, -1), std::out_of_range);
}

TEST(SmartListSequence, SetMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act
    list.set(2, item);

    // Assert
    EXPECT_EQ(list.get(2), item);
}

TEST(SmartListSequence, SetMethodWithIndexOutOfBounds) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act

    // Assert
    EXPECT_THROW(list.set(5, item), std::out_of_range);
}

TEST(SmartListSequence, SetMethodWithNegativeIndex) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act

    // Assert
    EXPECT_THROW(list.set(-1, item), std::out_of_range);
}

TEST(SmartListSequence, SetMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);
    int item = 10;

    // Act

    // Assert
    EXPECT_THROW(list.set(0, item), std::out_of_range);
}

TEST(SmartListSequence, RangeSetMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act
    list.set(2, 4, item);

    // Assert
    for (int i = 2; i < 4; i++) {
        EXPECT_EQ(list.get(i), item);
    }
}

TEST(SmartListSequence, RangeSetMethodExcepts) {
    // Arrange
    SmartListSequence<int> list(10, 5);
    int item = 10;

    // Act

    // Assert
    EXPECT_THROW(list.set(-1, 5, item), std::out_of_range);
    EXPECT_THROW(list.set(2, 1, item), std::invalid_argument);
    EXPECT_THROW(list.set(0, 11, item), std::out_of_range);
    EXPECT_THROW(list.set(10, 10, item), std::out_of_range);
    EXPECT_THROW(list.set(2, -1, item), std::out_of_range);
}

TEST(SmartListSequence, InsertAtMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act
    list.insertAt(2, item);

    // Assert
    EXPECT_EQ(list.get(2), item);
    EXPECT_EQ(list.getSize(), 6);
}

TEST(SmartListSequence, InsertAtMethodWithIndexOutOfBounds) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act

    // Assert
    EXPECT_THROW(list.insertAt(6, item), std::out_of_range);
}

TEST(SmartListSequence, InsertAtMethodWithNegativeIndex) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act

    // Assert
    EXPECT_THROW(list.insertAt(-1, item), std::out_of_range);
}

TEST(SmartListSequence, AppendMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act
    list.append(item);

    // Assert
    EXPECT_EQ(list.get(list.getSize() - 1), item);
    EXPECT_EQ(list.getSize(), 6);
}

TEST(SmartListSequence, PrependMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    int item = 10;

    // Act
    list.prepend(item);

    // Assert
    EXPECT_EQ(list.get(0), item);
    EXPECT_EQ(list.getSize(), 6);
}

TEST(SmartListSequence, RemoveAtMethod) {
    // Arrange
    SmartListSequence<int> list;
    for (int i = 0; i < 5; i++) {
        list.append(i);
    }

    // Act
    list.removeAt(2);

    // Assert
    EXPECT_EQ(list.getSize(), 4);
    for (int i = 0; i < list.getSize(); i++) {
        if (i < 2) {
            EXPECT_EQ(list.get(i), i);
        } else {
            EXPECT_EQ(list.get(i), i + 1);
        }
    }
}

TEST(SmartListSequence, RemoveAtMethodWithIndexOutOfBounds) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    EXPECT_THROW(list.removeAt(5), std::out_of_range);
}

TEST(SmartListSequence, RemoveAtMethodWithNegativeIndex) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act

    // Assert
    EXPECT_THROW(list.removeAt(-1), std::out_of_range);
}

TEST(SmartListSequence, RemoveAtMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);

    // Act

    // Assert
    EXPECT_THROW(list.removeAt(0), std::out_of_range);
}

TEST(SmartListSequence, RemoveFirstMethod) {
    // Arrange
    SmartListSequence<int> list;
    for (int i = 0; i < 5; i++) {
        list.append(i);
    }

    // Act
    list.removeFirst();

    // Assert
    EXPECT_EQ(list.getSize(), 4);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), i + 1);
    }
}

TEST(SmartListSequence, RemoveFirstMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);

    // Act

    // Assert
    EXPECT_THROW(list.removeFirst(), std::out_of_range);
}

TEST(SmartListSequence, RemoveLastMethod) {
    // Arrange
    SmartListSequence<int> list;
    for (int i = 0; i < 5; i++) {
        list.append(i);
    }

    // Act
    list.removeLast();

    // Assert
    EXPECT_EQ(list.getSize(), 4);
    for (int i = 0; i < list.getSize(); i++) {
        EXPECT_EQ(list.get(i), i);
    }
}

TEST(SmartListSequence, RemoveLastMethodWithZeroSize) {
    // Arrange
    SmartListSequence<int> list(0, 5);

    // Act

    // Assert
    EXPECT_THROW(list.removeLast(), std::out_of_range);
}

TEST(SmartListSequence, EmptyMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);
    SmartListSequence<int> emptyList;

    // Act

    // Assert
    EXPECT_FALSE(list.empty());
    EXPECT_TRUE(emptyList.empty());
}

TEST(SmartListSequence, ClearMethod) {
    // Arrange
    SmartListSequence<int> list(5, 5);

    // Act
    list.clear();

    // Assert
    EXPECT_EQ(list.getSize(), 0);
}

TEST(SmartListSequence, OperatorSquareBrackets) {
    // Arrange
    auto sequence = testListSequence();
    int index = 5;

    // Act
    (*sequence)[index + 1] = "TEST";

    // Assert
    EXPECT_EQ((*sequence)[index], "TEST" + std::to_string(index));
    EXPECT_EQ((*sequence)[index + 1], "TEST");
}

TEST(SmartListSequence, OperatorSquareBracketsWithNegativeIndex) {
    // Arrange
    auto sequence = testListSequence();
    int index = -5;

    // Act

    // Assert
    EXPECT_THROW((*sequence)[index], std::out_of_range);
}

TEST(SmartListSequence, OperatorSquareBracketsWithIndexGreaterThanSize) {
    // Arrange
    auto sequence = testListSequence();
    int index = sequence->getSize() + 5;

    // Act

    // Assert
    EXPECT_THROW((*sequence)[index], std::out_of_range);
}

TEST(SmartListSequence, OperatorSquareBracketsWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);
    int index = 0;

    // Act

    // Assert
    EXPECT_THROW((*sequence)[index], std::out_of_range);
}

TEST(SmartListSequence, OperatorPlus) {
    // Arrange
    auto sequence = testListSequence();
    auto sequence2 = testListSequence();

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

TEST(SmartListSequence, OperatorPlusWithZeroSize) {
    // Arrange
    auto sequence = testListSequence();
    auto sequence2 = make_shared<SmartListSequence<std::string>>(0);

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

TEST(SmartListSequence, OperatorPlusWithSelf) {
    // Arrange
    auto sequence = testListSequence();

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

TEST(SmartListSequence, OperatorPlusWithZeroSelf) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

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

TEST(SmartListSequence, ConcatMethod) {
    // Arrange
    auto sequence = testListSequence();
    auto sequence2 = testListSequence();

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

TEST(SmartListSequence, ConcatMethodWithZeroSize) {
    // Arrange
    auto sequence = testListSequence();
    auto sequence2 = make_shared<SmartListSequence<std::string>>(0);

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

TEST(SmartListSequence, ConcatMethodWithSelf) {
    // Arrange
    auto sequence = testListSequence();

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

TEST(SmartListSequence, ConcatMethodWithZeroSelf) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

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

TEST(SmartListSequence, FindMethod) {
    // Arrange
    auto sequence = testListSequence();
    int index = 5;

    // Act
    int findIndex = sequence->find("TEST" + std::to_string(index));

    // Assert
    EXPECT_EQ(findIndex, index);
}

TEST(SmartListSequence, FindMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);
    int index = 5;

    // Act

    // Assert
    EXPECT_THROW(sequence->find("TEST" + std::to_string(index)), std::invalid_argument);
}

TEST(SmartListSequence, FindMethodWithItemNotFound) {
    // Arrange
    auto sequence = testListSequence();
    std::string item = "TEST";

    // Act

    // Assert
    EXPECT_THROW(sequence->find(item), std::invalid_argument);
}

TEST(SmartListSequence, MapMethod) {
    // Arrange
    auto sequence = testListSequence();

    // Act
    auto new_sequence = sequence->map([](const std::string &item) { return item + "TEST"; });

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize());
    for (int i = 0; i < sequence->getSize(); i++) {
        EXPECT_EQ(new_sequence->get(i), sequence->get(i) + "TEST");
    }
}

TEST(SmartListSequence, MapMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

    // Act
    auto new_sequence = sequence->map([](const std::string &item) { return item + "TEST"; });

    // Assert
    EXPECT_EQ(new_sequence->getSize(), sequence->getSize());
}

TEST(SmartListSequence, WhereMethod) {
    // Arrange
    auto sequence = testListSequence();

    // Act
    auto new_sequence = sequence->where([](const std::string &item) { return item == "TEST5"; });

    // Assert
    EXPECT_EQ(new_sequence->getSize(), 1);
    EXPECT_EQ(new_sequence->get(0), "TEST5");
}

TEST(SmartListSequence, WhereMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

    // Act
    auto new_sequence = sequence->where([](const std::string &item) { return item == "TEST5"; });

    // Assert
    EXPECT_EQ(new_sequence->getSize(), 0);
}

TEST(SmartListSequence, ReduceMethod) {
    // Arrange
    auto sequence = testListSequence();

    // Act
    auto result = sequence->reduce(
        [](const std::string &accumulator, const std::string &item) { return accumulator + item; }, "");

    // Assert
    EXPECT_EQ(result, "TEST0TEST1TEST2TEST3TEST4TEST5TEST6TEST7TEST8TEST9");
}

TEST(SmartListSequence, ReduceMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

    // Act
    auto result = sequence->reduce(
        [](const std::string &accumulator, const std::string &item) { return accumulator + item; }, "");

    // Assert
    EXPECT_EQ(result, "");
}

TEST(SmartListSequence, ReduceMethodWithInitialValue) {
    // Arrange
    auto sequence = testListSequence();

    // Act
    auto result = sequence->reduce(
        [](const std::string &accumulator, const std::string &item) { return accumulator + item; }, "TEST");

    // Assert
    EXPECT_EQ(result, "TESTTEST0TEST1TEST2TEST3TEST4TEST5TEST6TEST7TEST8TEST9");
}

TEST(SmartListSequence, TryGetMethod) {
    // Arrange
    auto sequence = testListSequence();
    int index = 5;

    // Act
    auto item = sequence->tryGet(index);

    // Assert
    EXPECT_EQ(item.Value(), "TEST" + std::to_string(index));
}

TEST(SmartListSequence, TryGetMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);
    int index = 5;

    // Act
    auto item = sequence->tryGet(index);

    // Assert
    EXPECT_FALSE(item.HasValue());
}

TEST(SmartListSequence, TryGetMethodWithIndexOutOfBounds) {
    // Arrange
    auto sequence = testListSequence();
    int index = sequence->getSize() + 5;

    // Act
    auto item = sequence->tryGet(index);

    // Assert
    EXPECT_FALSE(item.HasValue());
}

TEST(SmartListSequence, TryGetMethodWithNegativeIndex) {
    // Arrange
    auto sequence = testListSequence();
    int index = -5;

    // Act
    auto item = sequence->tryGet(index);

    // Assert
    EXPECT_FALSE(item.HasValue());
}

TEST(SmartListSequence, TryGetFirstMethod) {
    // Arrange
    auto sequence = testListSequence();

    // Act
    auto item = sequence->tryGetFirst();

    // Assert
    EXPECT_EQ(item.Value(), "TEST0");
}

TEST(SmartListSequence, TryGetFirstMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

    // Act
    auto item = sequence->tryGetFirst();

    // Assert
    EXPECT_FALSE(item.HasValue());
}

TEST(SmartListSequence, TryGetLastMethod) {
    // Arrange
    auto sequence = testListSequence();

    // Act
    auto item = sequence->tryGetLast();

    // Assert
    EXPECT_EQ(item.Value(), "TEST9");
}

TEST(SmartListSequence, TryGetLastMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);

    // Act
    auto item = sequence->tryGetLast();

    // Assert
    EXPECT_FALSE(item.HasValue());
}

TEST(SmartListSequence, TryFindMethod) {
    // Arrange
    auto sequence = testListSequence();
    int index = 5;

    // Act
    auto item = sequence->tryFind("TEST" + std::to_string(index));

    // Assert
    EXPECT_EQ(item.Value(), index);
}

TEST(SmartListSequence, TryFindMethodWithZeroSize) {
    // Arrange
    auto sequence = make_shared<SmartListSequence<std::string>>(0);
    int index = 5;

    // Act
    auto item = sequence->tryFind("TEST" + std::to_string(index));

    // Assert
    EXPECT_FALSE(item.HasValue());
}

TEST(SmartListSequence, TryFindMethodWithItemNotFound) {
    // Arrange
    auto sequence = testListSequence();
    std::string item = "TEST";

    // Act
    auto findIndex = sequence->tryFind(item);

    // Assert
    EXPECT_FALSE(findIndex.HasValue());
}