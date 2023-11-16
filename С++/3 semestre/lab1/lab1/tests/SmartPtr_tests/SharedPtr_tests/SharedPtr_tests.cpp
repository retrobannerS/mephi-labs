#include "smart_pointers/SharedPtr.hpp"
#include "gtest/gtest.h"

#include <vector>

using namespace sem3;

TEST(SharedPtrTests, MakeShared) {
    // arrange & act
    auto ptr = make_shared<int>(10);

    // assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, 10);
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(SharedPtrTests, MakeSharedWithMultipleArguments) {
    // arrange & act
    auto ptr = make_shared<std::pair<int, std::string>>(10, "test");

    // assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr->first, 10);
    EXPECT_EQ(ptr->second, "test");
    EXPECT_EQ(ptr.use_count(), 1);
}

class CustomClass {
public:
    CustomClass(int x, std::string y) : x_(x), y_(y) {}

    int getX() const { return x_; }
    std::string getY() const { return y_; }

private:
    int x_;
    std::string y_;
};

TEST(SharedPtrTests, CustomClass) {
    // arrange & act
    auto ptr = make_shared<CustomClass>(10, "test");

    // assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(ptr->getX(), 10);
    EXPECT_EQ(ptr->getY(), "test");
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(SharedPtrTests, CustomClassCopy) {
    // arrange
    auto ptr1 = make_shared<CustomClass>(10, "test");

    // act
    SharedPtr<CustomClass> ptr2 = ptr1;

    // assert
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(ptr2->getX(), 10);
    EXPECT_EQ(ptr2->getY(), "test");
    EXPECT_EQ(ptr2.use_count(), 2);
    EXPECT_EQ(ptr1.use_count(), 2);
}

TEST(SharedPtrTests, CustomClassMove) {
    // arrange
    auto ptr1 = make_shared<CustomClass>(10, "test");

    // act
    SharedPtr<CustomClass> ptr2 = std::move(ptr1);

    // assert
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(ptr2->getX(), 10);
    EXPECT_EQ(ptr2->getY(), "test");
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.use_count(), 0);
}

TEST(SharedPtrTests, EmptyConstructor) {
    //arrange
    SharedPtr<int> ptr;

    //act

    //assert
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrTests, Constructor) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, 10);
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(SharedPtrTests, ConstructorWithNullptr) {
    //arrange
    SharedPtr<int> ptr(nullptr);

    //assert
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrTests, CopyConstructor) {
    //arrange
    SharedPtr<int> original(new int(10));

    //act
    SharedPtr<int> copy = original;

    //assert
    EXPECT_NE(copy.get(), nullptr);
    EXPECT_EQ(*copy, 10);
    EXPECT_EQ(copy.use_count(), 2);
    EXPECT_EQ(original.use_count(), 2);
}

TEST(SharedPtrTests, CopyConstructorWithNullptr) {
    //arrange
    SharedPtr<int> original(nullptr);

    //act
    SharedPtr<int> copy = original;

    //assert
    EXPECT_EQ(copy.get(), nullptr);
    EXPECT_EQ(copy.use_count(), 0);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrTests, MoveConstructor) {
    //arrange
    SharedPtr<int> original(new int(10));

    //act
    SharedPtr<int> moved(std::move(original));

    //assert
    EXPECT_NE(moved.get(), nullptr);
    EXPECT_EQ(*moved, 10);
    EXPECT_EQ(moved.use_count(), 1);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrTests, MoveConstructorWithNullptr) {
    //arrange
    SharedPtr<int> original(nullptr);

    //act
    SharedPtr<int> moved(std::move(original));

    //assert
    EXPECT_EQ(moved.get(), nullptr);
    EXPECT_EQ(moved.use_count(), 0);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrTests, DestructorDecreasesCount) {
    //arrange
    SharedPtr<int>* ptr = new SharedPtr<int>(new int(10));
    SharedPtr<int> ptr2 = *ptr;
    EXPECT_EQ(ptr2.use_count(), 2);

    //act
    delete ptr; // This should call the destructor

    //assert
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrTests, AssignmentOperator) {
    //arrange
    SharedPtr<int> original(new int(10));
    SharedPtr<int> copy;

    //act
    copy = original;

    //assert
    EXPECT_NE(copy.get(), nullptr);
    EXPECT_EQ(*copy, 10);
    EXPECT_EQ(copy.use_count(), 2);
    EXPECT_EQ(original.use_count(), 2);
}

TEST(SharedPtrTests, AssignmentOperatorWithNullptr) {
    //arrange
    SharedPtr<int> original(nullptr);
    SharedPtr<int> copy;

    //act
    copy = original;

    //assert
    EXPECT_EQ(copy.get(), nullptr);
    EXPECT_EQ(copy.use_count(), 0);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrTests, MoveAssignmentOperator) {
    //arrange
    SharedPtr<int> original(new int(10));
    SharedPtr<int> moved;

    //act
    moved = std::move(original);

    //assert
    EXPECT_NE(moved.get(), nullptr);
    EXPECT_EQ(*moved, 10);
    EXPECT_EQ(moved.use_count(), 1);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrTests, MoveAssignmentOperatorWithNullptr) {
    //arrange
    SharedPtr<int> original(nullptr);
    SharedPtr<int> moved;

    //act
    moved = std::move(original);

    //assert
    EXPECT_EQ(moved.get(), nullptr);
    EXPECT_EQ(moved.use_count(), 0);
    EXPECT_EQ(original.get(), nullptr);
    EXPECT_EQ(original.use_count(), 0);
}

TEST(SharedPtrTests, ResetMethodWithObject) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //act
    ptr.reset(new int(20));

    //assert
    EXPECT_NE(ptr.get(), nullptr);
    EXPECT_EQ(*ptr, 20);
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(SharedPtrTests, ResetMethodWithNullptr) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //act
    ptr.reset(nullptr);

    //assert
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(ptr.use_count(), 0);
}

TEST(SharedPtrTests, ResetMethodDecreasesCount) {
    //arrange
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2 = ptr1;

    //act
    ptr1.reset(new int(20));

    //assert
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrTests, SwapMethod) {
    //arrange
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2(new int(20));

    //act
    ptr1.swap(ptr2);

    //assert
    EXPECT_NE(ptr1.get(), nullptr);
    EXPECT_EQ(*ptr1, 20);
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrTests, SwapMethodWithNullptr) {
    //arrange
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2(nullptr);

    //act
    ptr1.swap(ptr2);

    //assert
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrTests, GetMethod) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //act
    int* raw_ptr = ptr.get();

    //assert
    EXPECT_NE(raw_ptr, nullptr);
    EXPECT_EQ(*raw_ptr, 10);
}

TEST(SharedPtrTests, GetMethodWithNullptr) {
    //arrange
    SharedPtr<int> ptr(nullptr);

    //act
    int* raw_ptr = ptr.get();

    //assert
    EXPECT_EQ(raw_ptr, nullptr);
}

TEST(SharedPtrTests, ArrowOperator) {
    //arrange
    SharedPtr<std::vector<int>> ptr(new std::vector<int>{1, 2, 3});

    //act
    int size = ptr->size();

    //assert
    EXPECT_EQ(size, 3);
}

TEST(SharedPtrTests, DereferenceOperator) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //act
    int value = *ptr;

    //assert
    EXPECT_EQ(value, 10);
}

TEST(SharedPtrTests, UniqueMethod) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //act and assert
    EXPECT_TRUE(ptr.unique());

    //arrange
    SharedPtr<int> ptr2 = ptr;

    //act and assert
    EXPECT_FALSE(ptr.unique());
    EXPECT_FALSE(ptr2.unique());
}

TEST(SharedPtrTests, UseCountMethod) {
    //arrange
    SharedPtr<int> ptr(new int(10));

    //act and assert
    EXPECT_EQ(ptr.use_count(), 1);

    //arrange
    SharedPtr<int> ptr2 = ptr;

    //act and assert
    EXPECT_EQ(ptr.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
}

TEST(SharedPtrTests, UniqueMethodWithNullptr) {
    //arrange
    SharedPtr<int> ptr(nullptr);

    //act and assert
    EXPECT_FALSE(ptr.unique());

    //arrange
    SharedPtr<int> ptr2 = ptr;

    //act and assert
    EXPECT_FALSE(ptr.unique());
    EXPECT_FALSE(ptr2.unique());
}

TEST(SharedPtrTests, UseCountMethodWithNullptr) {
    //arrange
    SharedPtr<int> ptr(nullptr);

    //act and assert
    EXPECT_EQ(ptr.use_count(), 0);

    //arrange
    SharedPtr<int> ptr2 = ptr;

    //act and assert
    EXPECT_EQ(ptr.use_count(), 0);
    EXPECT_EQ(ptr2.use_count(), 0);
}

TEST(SharedPtrTests, BoolOperator) {
    //arrange
    SharedPtr<int> ptr(new int(10));
    SharedPtr<int> ptr2(nullptr);

    //act and assert
    EXPECT_TRUE(ptr);
    EXPECT_FALSE(ptr2);    
}

TEST(SharedPtrTests, ComparisonOperators) {
    //arrange
    SharedPtr<std::vector<int>> ptr1(new std::vector<int>{1, 2, 3});
    SharedPtr<std::vector<int>> ptr2 = ptr1;
    SharedPtr<std::vector<int>> ptr3(new std::vector<int>{4, 5, 6});
    std::vector<int>* raw_ptr = ptr1.get();

    //act and assert
    EXPECT_EQ(ptr1, ptr2);
    EXPECT_NE(ptr1, ptr3);
    EXPECT_EQ(ptr1, raw_ptr);
    EXPECT_NE(ptr3, raw_ptr);
    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr3, nullptr);

    //arrange
    ptr1.reset();

    //act and assert
    EXPECT_NE(ptr1, ptr2);
    EXPECT_NE(ptr1, raw_ptr);
    EXPECT_EQ(ptr1, nullptr);
}

TEST(SharedPtrTests, SwapFunction) {
    //arrange
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2(new int(20));

    //act
    swap(ptr1, ptr2);

    //assert
    EXPECT_NE(ptr1.get(), nullptr);
    EXPECT_EQ(*ptr1, 20);
    EXPECT_EQ(ptr1.use_count(), 1);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(SharedPtrTests, SwapFunctionWithNullptr) {
    //arrange
    SharedPtr<int> ptr1(new int(10));
    SharedPtr<int> ptr2(nullptr);

    //act
    swap(ptr1, ptr2);

    //assert
    EXPECT_EQ(ptr1.get(), nullptr);
    EXPECT_EQ(ptr1.use_count(), 0);
    EXPECT_NE(ptr2.get(), nullptr);
    EXPECT_EQ(*ptr2, 10);
    EXPECT_EQ(ptr2.use_count(), 1);
}