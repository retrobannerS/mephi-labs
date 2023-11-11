TEST(UniquePtrTests, SwapFunction) {
    // arrange
    UniquePtr<int> ptr1(new int(42));
    UniquePtr<int> ptr2(new int(13));

    // act
    swap(ptr1, ptr2);

    // assert
    EXPECT_EQ(*ptr1, 13);
    EXPECT_EQ(*ptr2, 42);
}