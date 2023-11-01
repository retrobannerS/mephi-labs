#include <stdexcept>
#include <string>
#include "../UnitTest.hpp"
#include "../TestCluster.hpp"
#include "../../Data_Classes/DynamicArray.hpp"

test::TestCluster DynamicArrayTests("DynamicArray");

lab2::DynamicArray<std::string> ArrayForTest() {
    auto *a = new std::string[10];
    for(int i = 0; i != 10; ++i) {
        a[i] = "TEST" + std::to_string(i);
    }
    lab2::DynamicArray<std::string> arr(10, a);
    delete[] a;
    return arr;
}

TEST(DynamicArrayTests, Default_Constructor) {
    lab2::DynamicArray<int> arr;
    ASSERT(arr.GetSize() == 0);

    bool flag = false;
    try {
        arr.Get(0);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr[0];
    } catch(const std::out_of_range &) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Default_Constructor);

TEST(DynamicArrayTests, Constructor_With_Size) {
    lab2::DynamicArray<int> arr(5);
    ASSERT(arr.GetSize() == 5);

    bool flag = false;
    try {
        arr.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr[5];
    } catch(const std::out_of_range &) {
        flag = true;
    }
    ASSERT(flag);

    ASSERT(arr[0] == 0);
    ASSERT(arr.Get(3) == 0);

    flag = false;
    try {
        lab2::DynamicArray<int> arr2(-1);
    } catch(const std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Constructor_With_Size);

TEST(DynamicArrayTests, Constructor_With_Size_And_Item) {
    lab2::DynamicArray<std::string> arr(3, "Hello");
    ASSERT(arr.GetSize() == 3);
    ASSERT(arr[0] == "Hello");
    ASSERT(arr.Get(1) == "Hello");

    bool flag = false;
    try {
        arr.Get(3);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        arr[3];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);

    flag = false;
    try {
        lab2::DynamicArray<std::string> arr2(-1, "Hello");
    } catch(const std::invalid_argument &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Constructor_With_Size_And_Item);

TEST(DynamicArrayTests, Constructor_With_Array) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    ASSERT(arr.GetSize() == 10);
    ASSERT(arr[0] == "TEST0");
    ASSERT(arr.Get(1) == "TEST1");

    bool flag = false;
    try {
        arr.Get(10);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr[10];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Constructor_With_Array);

TEST(DynamicArrayTests, Copy_Constructor) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    lab2::DynamicArray<std::string> arr2(arr);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2[0] == "TEST0");
    ASSERT(arr2.Get(1) == "TEST1");

    bool flag = false;
    try {
        arr2.Get(10);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr2[10];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Copy_Constructor);

TEST(DynamicArrayTests, Destructor) {
    auto *arr = new lab2::DynamicArray<std::string>(3, "TEST");
    delete arr;
}
ADD_TEST(DynamicArrayTests, Destructor);

TEST(DynamicArrayTests, Get) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    ASSERT(arr.Get(0) == "TEST0");
    ASSERT(arr.Get(1) == "TEST1");
    ASSERT(arr.Get(2) == "TEST2");
    ASSERT(arr.Get(3) == "TEST3");
    ASSERT(arr.Get(4) == "TEST4");
    ASSERT(arr.Get(5) == "TEST5");
    ASSERT(arr.Get(6) == "TEST6");
    ASSERT(arr.Get(7) == "TEST7");
    ASSERT(arr.Get(8) == "TEST8");
    ASSERT(arr.Get(9) == "TEST9");

    bool flag = false;
    try {
        arr.Get(10);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr.Get(-1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Get);

TEST(DynamicArrayTests, GetSize) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    ASSERT(arr.GetSize() == 10);
    lab2::DynamicArray<int> a;
    ASSERT(a.GetSize() == 0);
    lab2::DynamicArray<int> b(5);
    ASSERT(b.GetSize() == 5);
    lab2::DynamicArray<int> c(5, 1);
    ASSERT(c.GetSize() >= 0);
}
ADD_TEST(DynamicArrayTests, GetSize);

TEST(DynamicArrayTests, GetSubArray) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    lab2::DynamicArray<std::string> arr2 = arr.GetSubArray(0, 5);
    ASSERT(arr2.GetSize() == 6);
    ASSERT(arr2[0] == "TEST0");
    ASSERT(arr2.Get(1) == "TEST1");
    ASSERT(arr2[4] == "TEST4");
    bool flag = false;
    try {
        arr2.Get(6);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    arr2 = arr.GetSubArray(5, 5);
    ASSERT(arr2.GetSize() == 1);
    ASSERT(arr2[0] == "TEST5");
    try {
        arr2.Get(1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr2.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr2 = arr.GetSubArray(0, 9);
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2[0] == "TEST0");
    ASSERT(arr2.Get(1) == "TEST1");
    ASSERT(arr2[9] == "TEST9");
    flag = false;
    try {
        arr2.Get(10);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr2 = arr.GetSubArray(0, 0);
    ASSERT(arr2.GetSize() == 1);
    flag = false;
    try {
        arr2.Get(1);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr2 = arr.GetSubArray(5, 0);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(arr2.GetSize() == 1);
    flag = false;
    ASSERT(arr2.Get(0) == arr.Get(0));
    try {
        arr.GetSubArray(10, 0);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, GetSubArray);

TEST(DynamicArrayTests, Set1) {
lab2::DynamicArray<std::string> arr = ArrayForTest();
    const char *tmp = "ULALA";
    arr.Set(0, tmp);
    ASSERT(arr.Get(0) == tmp);
    arr.Set(1, tmp);
    ASSERT(arr.Get(1) == tmp);
    arr.Set(2, tmp);
    ASSERT(arr.Get(2) == tmp);
    arr.Set(3, tmp);
    ASSERT(arr.Get(3) == tmp);
    arr.Set(4, tmp);
    ASSERT(arr.Get(4) == tmp);
    arr.Set(5, tmp);
    ASSERT(arr.Get(5) == tmp);
    arr.Set(6, tmp);
    ASSERT(arr.Get(6) == tmp);
    arr.Set(7, tmp);
    ASSERT(arr.Get(7) == tmp);
    arr.Set(8, tmp);
    ASSERT(arr.Get(8) == tmp);
    arr.Set(9, tmp);
    ASSERT(arr.Get(9) == tmp);

    bool flag = false;
    try {
        arr.Set(10, "TEST");
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr.Set(-1, "TEST");
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Set1);\

TEST(DynamicArrayTests, Set2) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    const char *tmp = "ULALA";
    arr.Set(0, 5, tmp);
    ASSERT(arr.Get(0) == tmp);
    arr.Set(1, 5, tmp);
    ASSERT(arr.Get(5) == tmp);
    ASSERT(arr.Get(6) == "TEST6");
    bool flag = false;
    try {
        arr.Set(10, 5, tmp);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr.Set(-1, 5, tmp);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;
    try {
        arr.Set(0, 15, tmp);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Set2);

TEST(DynamicArrayTests, Operator_Square_Brackets) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    ASSERT(arr[0] == "TEST0");
    ASSERT(arr[1] == "TEST1");
    ASSERT(arr[2] == "TEST2");
    ASSERT(arr[3] == "TEST3");
    ASSERT(arr[4] == "TEST4");
    ASSERT(arr[5] == "TEST5");
    ASSERT(arr[6] == "TEST6");
    ASSERT(arr[7] == "TEST7");
    ASSERT(arr[8] == "TEST8");
    ASSERT(arr[9] == "TEST9");
    arr[0] = "ULALA";
    ASSERT(arr[0] == "ULALA");
    arr[9] = "ULALA";
    ASSERT(arr[9] == "ULALA");

    bool flag = false;
    try {
        arr[10];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr[-1];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Operator_Square_Brackets);

TEST(DynamicArrayTests, Operator_Equal) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    lab2::DynamicArray<std::string> arr2 = arr;
    ASSERT(arr2.GetSize() == 10);
    ASSERT(arr2[0] == "TEST0");
    ASSERT(arr2.Get(1) == "TEST1");

    bool flag = false;
    try {
        arr2.Get(10);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr2[10];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Operator_Equal);

TEST(DynamicArrayTests, Operator_Plus) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    lab2::DynamicArray<std::string> arr2 = ArrayForTest();
    lab2::DynamicArray<std::string> arr3 = arr + arr2;
    ASSERT(arr3.GetSize() == 20);
    ASSERT(arr3[0] == "TEST0");
    ASSERT(arr3.Get(1) == "TEST1");
    ASSERT(arr3[10] == "TEST0");
    ASSERT(arr3.Get(11) == "TEST1");

    bool flag = false;
    try {
        arr3.Get(20);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    flag = false;

    try {
        arr3[20];
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    ASSERT(arr3.GetSize() >= 0);
}
ADD_TEST(DynamicArrayTests, Operator_Plus);

TEST(DynamicArrayTests, Realloc) {
    lab2::DynamicArray<std::string> arr = ArrayForTest();
    arr.Realloc(30);
    ASSERT(arr.GetSize() == 30);
    ASSERT(arr[0] == "TEST0");
    ASSERT(arr.Get(1) == "TEST1");
    ASSERT(arr[9] == "TEST9");
    arr.Realloc(5);
    ASSERT(arr.GetSize() == 5);
    ASSERT(arr[0] == "TEST0");
    ASSERT(arr.Get(1) == "TEST1");
    ASSERT(arr[4] == "TEST4");
    bool flag = false;
    try {
        arr.Get(5);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
    arr.Realloc(0);
    ASSERT(arr.GetSize() == 0);
    flag = false;
    try {
        arr.Get(0);
    } catch(const std::out_of_range &e) {
        flag = true;
    }
    ASSERT(flag);
}
ADD_TEST(DynamicArrayTests, Realloc);