#include "smart_pointers/UniquePtr.hpp"
#include "gtest/gtest.h"

using namespace sem3;

TEST(UniquePtrTests, MakeUnique) {
    // Arrange
    int expected_value = 42;


    // Act
    auto ptr = make_unique<int>(expected_value);

    // Assert
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(*ptr, expected_value);
}

TEST(UniquePtrTests, MakeUniqueForStructure) {
    // Arrange
    struct TestStruct {
        int id;
        std::string name;
    };
    int expected_id = 42;
    std::string expected_name = "Test";

    // Act
    auto ptr = make_unique<TestStruct>(TestStruct{expected_id, expected_name});

    // Assert
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr->id, expected_id);
    EXPECT_EQ(ptr->name, expected_name);
}

TEST(UniquePtrTests, MakeUniqueForCustomClass) {
    // Arrange
    class TestClass {
    public:
        TestClass(int id, std::string name) : id(id), name(name) {}
        TestClass(TestClass &other) = delete;
        int getId() const { return id; }
        std::string getName() const { return name; }
    private:
        int id;
        std::string name;
    };
    int expected_id = 42;
    std::string expected_name = "Test";

    // Act
    //auto ptr = make_unique<TestClass>(std::move(TestClass(expected_id, expected_name)));
    //auto ptr = make_unique<TestClass>(expected_id, expected_name);
    auto ptr = make_unique<TestClass>(expected_id, expected_name);

    // Assert
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr->getId(), expected_id);
    EXPECT_EQ(ptr->getName(), expected_name);
}

TEST(UniquePtrTests, MoveSemantics) {
    // Arrange
    UniquePtr<int> ptr1(new int(42));

    // Act
    UniquePtr<int> ptr2 = std::move(ptr1);

    // Assert
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrTests, NullptrAfterRelease) {
    // Arrange
    UniquePtr<int> ptr(new int(42));

    // Act
    int* raw_ptr = ptr.release();

    // Assert
    EXPECT_EQ(*raw_ptr, 42);
    EXPECT_EQ(ptr.get(), nullptr);

    // Clean up
    delete raw_ptr;
}

TEST(UniquePtrTests, EmptyConstructor) {
    // arrange

    // act
    UniquePtr<int> ptr1;

    // assert
    ASSERT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrTests, ConstructorWithPointer) {
    // arrange
    int *rawPtr = new int(42);

    // act
    UniquePtr<int> ptr(rawPtr);

    // assert
    ASSERT_EQ(ptr.get(), rawPtr);
}

TEST(UniquePtrTests, AssignOperatorWithNullptr) {
    // arrange
    int *rawPtr = new int(42);
    UniquePtr<int> ptr(rawPtr);

    // act
    ptr = nullptr;

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTests, ReleaseMethod) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    int *rawPtr = ptr.release();

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(*rawPtr, 42);
    delete rawPtr;
}

TEST(UniquePtrTests, ResetMethod) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    ptr.reset(new int(13));

    // assert
    ASSERT_EQ(*ptr, 13);
}

TEST(UniquePtrTests, ResetMethodWithNullptr) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    ptr.reset();

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrTests, SwapMethod) {
    // arrange
    int *rawPtr1 = new int(5);
    int *rawPtr2 = new int(10);
    UniquePtr<int> ptr1(rawPtr1);
    UniquePtr<int> ptr2(rawPtr2);

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(*ptr1, 10);
    ASSERT_EQ(*ptr2, 5);
}

TEST(UniquePtrTests, SwapMethodWithNullptr) {
    // arrange
    int *rawPtr1 = new int(5);
    UniquePtr<int> ptr1(rawPtr1);
    UniquePtr<int> ptr2(nullptr);

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(*ptr2, 5);
}

TEST(UniquePtrTests, GetMethod) {
    // arrange
    int *ptr1 = new int(5);
    UniquePtr<int> ptr1_(ptr1);

    // act
    int *ptr1_get = ptr1_.get();
    *ptr1_get = 2;

    // assert
    ASSERT_EQ(ptr1_get, ptr1);
    ASSERT_EQ(*ptr1_, 2);
}

TEST(UniquePtrTests, BooleanConversionOperator) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act & assert
    ASSERT_TRUE(ptr);
    ptr.reset();
    ASSERT_FALSE(ptr);
}

TEST(UniquePtrTests, DereferenceOperator) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act & assert
    ASSERT_EQ(*ptr, 42);
}

TEST(UniquePtrTests, ArrowOperator) {
    // arrange
    struct Foo {
        int bar;
    };
    UniquePtr<Foo> ptr(new Foo{42});

    // act & assert
    ASSERT_EQ(ptr->bar, 42);
}

TEST(UniquePtrTests, BooleanOperators) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(42));
    UniquePtr<int> ptr3(new int(13));
    UniquePtr<int> null_ptr;
    nullptr_t other_null_ptr;

    // act
    int *test_ptr1 = new int(3);
    UniquePtr<int> real_ptr1(test_ptr1);
    int *test_ptr2 = new int(4);
    UniquePtr<int> real_ptr2(test_ptr2);

    // assert
    ASSERT_NE(ptr1, ptr2);
    ASSERT_NE(ptr1, ptr3);
    ASSERT_EQ(ptr1, ptr1);
    ASSERT_NE(ptr1, null_ptr);
    ASSERT_NE(ptr1, other_null_ptr);
    ASSERT_NE(other_null_ptr, ptr1);
    ASSERT_EQ(null_ptr, other_null_ptr);
    ASSERT_EQ(other_null_ptr, null_ptr);
    ASSERT_EQ(test_ptr1, real_ptr1.get());
    ASSERT_EQ(real_ptr1.get(), test_ptr1);
    ASSERT_NE(test_ptr1, real_ptr2.get());
}

TEST(UniquePtrTests, SwapFunction) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(13));

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(*ptr1, 13);
    ASSERT_EQ(*ptr2, 42);
}

TEST(UniquePtrTests, MoveConstructor) {
    // arrange
    UniquePtr<int> ptr1(new int(42));

    // act
    UniquePtr<int> ptr2(std::move(ptr1));

    // assert
    EXPECT_EQ(*ptr2, 42);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrTests, AssignmentOperatorForDifferentObjects) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(13));

    // act
    ptr1 = std::move(ptr2);

    // assert
    EXPECT_EQ(*ptr1, 13);
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(UniquePtrTests, AssignmentOperatorForSameObject) {
    // arrange
    UniquePtr<int> ptr(new int(42));

    // act
    ptr = std::move(ptr);

    // assert
    EXPECT_EQ(*ptr, 42);
}

TEST(UniquePtrTests, AssignmentOperatorForEmptyObject) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2;

    // act
    ptr1 = std::move(ptr2);

    // assert
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(UniquePtrArrayTests, EmptyConstructor) {
    // arrange

    // act
    UniquePtr<int[]> ptr1;

    // assert
    ASSERT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrArrayTests, ConstructorWithPointer) {
    // arrange
    int *rawPtr = new int[42];

    // act
    UniquePtr<int[]> ptr(rawPtr);

    // assert
    ASSERT_EQ(ptr.get(), rawPtr);
}

TEST(UniquePtrArrayTests, AssignOperatorWithNullptr) {
    // arrange
    int *rawPtr = new int[42];
    UniquePtr<int[]> ptr(rawPtr);

    // act
    ptr = nullptr;

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrArrayTests, ReleaseMethod) {
    // arrange
    int *rawPtr = new int[42];
    for (int i = 0; i != 42; ++i) {
        rawPtr[i] = i;
    }
    UniquePtr<int[]> ptr(rawPtr);

    // act
    int *testPtr = ptr.release();

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(testPtr[0], 0);
    ASSERT_EQ(testPtr[1], 1);
    delete[] testPtr;
}

TEST(UniquePtrArrayTests, ResetMethod) {
    // arrange
    UniquePtr<int[]> ptr(new int[42]);
    int *rawPtr = new int[1];
    rawPtr[0] = 515;

    // act
    ptr.reset(rawPtr);

    // assert
    ASSERT_EQ(ptr[0], 515);
}

TEST(UniquePtrArrayTests, ResetMethodWithNullptr) {
    // arrange
    UniquePtr<int[]> ptr(new int[42]);

    // act
    ptr.reset();

    // assert
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(UniquePtrArrayTests, SwapMethod) {
    // arrange
    int *rawPtr1 = new int[5];
    int *rawPtr2 = new int[10];
    UniquePtr<int[]> ptr1(rawPtr1);
    UniquePtr<int[]> ptr2(rawPtr2);

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(ptr1.get(), rawPtr2);
    ASSERT_EQ(ptr2.get(), rawPtr1);
}

TEST(UniquePtrArrayTests, SwapMethodWithNullptr) {
    // arrange
    int *rawPtr1 = new int[5];
    UniquePtr<int[]> ptr1(rawPtr1);
    UniquePtr<int[]> ptr2(nullptr);

    // act
    swap(ptr1, ptr2);

    // assert
    ASSERT_EQ(ptr1.get(), nullptr);
    ASSERT_EQ(ptr2.get(), rawPtr1);
}

TEST(UniquePtrArrayTests, GetMethod) {
    // arrange
    int *rawPtr = new int[5];
    UniquePtr<int[]> ptr(rawPtr);

    // act
    int *ptr_get = ptr.get();

    // assert
    ASSERT_EQ(ptr_get, rawPtr);
}

TEST(UniquePtrArrayTests, BooleanConversionOperator) {
    // arrange
    UniquePtr<int[]> ptr(new int[42]);

    // act & assert
    ASSERT_TRUE(ptr);
    ptr.reset();
    ASSERT_FALSE(ptr);
}

TEST(UniquePtrArrayTests, ArraySubscriptOperator) {
    // arrange
    UniquePtr<int[]> ptr(new int[5]{10, 20, 30, 40, 50});

    // act & assert
    ASSERT_EQ(ptr[0], 10);
    ASSERT_EQ(ptr[1], 20);
    ASSERT_EQ(ptr[2], 30);
    ASSERT_EQ(ptr[3], 40);
    ASSERT_EQ(ptr[4], 50);
}

TEST(UniquePtrArrayTests, BooleanOperators) {
    // arrange
    UniquePtr<int[]> ptr1(new int[5]{10, 20, 30, 40, 50});
    UniquePtr<int[]> ptr2(new int[5]{10, 20, 30, 40, 50});
    UniquePtr<int[]> ptr3(new int[5]{50, 40, 30, 20, 10});
    UniquePtr<int[]> null_ptr;
    nullptr_t other_null_ptr;

    // act
    int *test_ptr1 = new int[3]{1, 2, 3};
    UniquePtr<int[]> real_ptr1(test_ptr1);
    int *test_ptr2 = new int[4]{4, 5, 6, 7};
    UniquePtr<int[]> real_ptr2(test_ptr2);

    // assert
    ASSERT_NE(ptr1, ptr2);
    ASSERT_NE(ptr1, ptr3);
    ASSERT_EQ(ptr1, ptr1);
    ASSERT_NE(ptr1, null_ptr);
    ASSERT_NE(ptr1, other_null_ptr);
    ASSERT_NE(other_null_ptr, ptr1);
    ASSERT_EQ(null_ptr, other_null_ptr);
    ASSERT_EQ(other_null_ptr, null_ptr);
    ASSERT_EQ(test_ptr1, real_ptr1.get());
    ASSERT_EQ(real_ptr1.get(), test_ptr1);
    ASSERT_NE(test_ptr1, real_ptr2.get());
}

TEST(UniquePtrArrayTests, MoveConstructor) {
    // arrange
    UniquePtr<int[]> ptr1(new int[2]{42, 43});

    // act
    UniquePtr<int[]> ptr2(std::move(ptr1));

    // assert
    EXPECT_EQ(ptr2[0], 42);
    EXPECT_EQ(ptr2[1], 43);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(UniquePtrArrayTests, AssignmentOperatorForDifferentObjects) {
    // arrange
    UniquePtr<int[]> ptr1(new int[2]{42, 43});
    UniquePtr<int[]> ptr2(new int[2]{13, 14});

    // act
    ptr1 = std::move(ptr2);

    // assert
    EXPECT_EQ(ptr1[0], 13);
    EXPECT_EQ(ptr1[1], 14);
    EXPECT_EQ(ptr2.get(), nullptr);
}

TEST(UniquePtrArrayTests, AssignmentOperatorForSameObject) {
    // arrange
    UniquePtr<int[]> ptr(new int[2]{42, 43});

    // act
    ptr = std::move(ptr);

    // assert
    EXPECT_EQ(ptr[0], 42);
    EXPECT_EQ(ptr[1], 43);
}

TEST(UniquePtrArrayTests, AssignmentOperatorForEmptyObject) {
    // arrange
    UniquePtr<int[]> ptr1(new int[2]{42, 43});
    UniquePtr<int[]> ptr2;

    // act
    ptr1 = std::move(ptr2);

    // assert
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr2.get(), nullptr);
}
