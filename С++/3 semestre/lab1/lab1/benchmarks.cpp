#include "smart_pointers/SharedPtr.hpp"
#include "smart_pointers/UniquePtr.hpp"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

using namespace std;
using namespace sem3;

struct TestObject {
    int value;
    TestObject() : value(0) {}
    TestObject(int value) : value(value) {}
};

size_t average(size_t (*test)(size_t), size_t size, size_t iterations);

size_t test_my_array(size_t size);
size_t test_raw_array(size_t size);
size_t test_std_array(size_t size);

SharedPtr<UniquePtr<TestObject>[]> create_my_array(size_t size);
TestObject **create_raw_array(size_t size);
shared_ptr<unique_ptr<TestObject>[]> create_std_array(size_t size);

void shuffle_my_array(SharedPtr<UniquePtr<TestObject>[]> arr, size_t size);
void shuffle_raw_array(TestObject **arr, size_t size);
void shuffle_std_array(shared_ptr<unique_ptr<TestObject>[]> arr, size_t size);

void sort_my_array(SharedPtr<UniquePtr<TestObject>[]> arr, size_t size);
void sort_raw_array(TestObject **arr, size_t size);
void sort_std_array(shared_ptr<unique_ptr<TestObject>[]> arr, size_t size);

int main() {
    srand(time(NULL));
    int max_power = 8;
    size_t iterations = 10;
    for (int i = 1; i <= max_power; ++i) {
        size_t size = pow(10, i);
        cout << "size: 10^" << i << endl;
        cout << "raw pointers:           " << average(test_raw_array, size, iterations) << "μs\n";
        std::cout << "my smart pointers: " << average(test_my_array, size, iterations) << "μs\n";
        cout << "std smart pointers:     " << average(test_std_array, size, iterations) << "μs\n";
    }
    return 0;
}

template <typename F, typename... Ts>
size_t time_it(F &&f, Ts &&...args) {
    auto start = std::chrono::high_resolution_clock::now();
    std::forward<F>(f)(std::forward<Ts>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

size_t average(size_t (*test)(size_t), size_t size, size_t iterations) {
    size_t total = 0;
    for (size_t i = 0; i < iterations; ++i) {
        total += test(size);
    }
    return total / iterations;
}

size_t test_my_array(size_t size) {
    auto arr = create_my_array(size);
    shuffle_my_array(arr, size);
    return time_it([&]() { sort_my_array(arr, size); });
}

size_t test_raw_array(size_t size) {
    auto arr = create_raw_array(size);
    shuffle_raw_array(arr, size);
    return time_it([&]() { sort_raw_array(arr, size); });
}

size_t test_std_array(size_t size) {
    auto arr = create_std_array(size);
    shuffle_std_array(arr, size);
    return time_it([&]() { sort_std_array(arr, size); });
}

SharedPtr<UniquePtr<TestObject>[]> create_my_array(size_t size) {
    auto arr = sem3::make_shared<UniquePtr<TestObject>[]>(size);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = sem3::make_unique<TestObject>(i);
    }
    return arr;
}

TestObject **create_raw_array(size_t size) {
    auto arr = new TestObject *[size];
    for (size_t i = 0; i < size; ++i) {
        arr[i] = new TestObject(i);
    }
    return arr;
}

shared_ptr<unique_ptr<TestObject>[]> create_std_array(size_t size) {
    auto arr = shared_ptr<unique_ptr<TestObject>[]>(new unique_ptr<TestObject>[size]);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = std::make_unique<TestObject>(i);
    }
    return arr;
}

void shuffle_my_array(SharedPtr<UniquePtr<TestObject>[]> arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t j = rand() % size;
        std::swap(arr[i], arr[j]);
    }
}

void shuffle_raw_array(TestObject **arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t j = rand() % size;
        std::swap(arr[i], arr[j]);
    }
}

void shuffle_std_array(shared_ptr<unique_ptr<TestObject>[]> arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        size_t j = rand() % size;
        swap(arr[i], arr[j]);
    }
}

void sort_my_array(SharedPtr<UniquePtr<TestObject>[]> arr, size_t size) {
    std::qsort(arr.get(), size, sizeof(UniquePtr<TestObject>), [](const void *a, const void *b) {
        return (*(UniquePtr<TestObject> *)a)->value - (*(UniquePtr<TestObject> *)b)->value;
    });
}

void sort_raw_array(TestObject **arr, size_t size) {
    std::qsort(arr, size, sizeof(TestObject *),
               [](const void *a, const void *b) { return (*(TestObject **)a)->value - (*(TestObject **)b)->value; });
    for (size_t i = 0; i < size; ++i) {
        delete arr[i];
    }
    delete[] arr;
}

void sort_std_array(shared_ptr<unique_ptr<TestObject>[]> arr, size_t size) {
    std::qsort(arr.get(), size, sizeof(unique_ptr<TestObject>), [](const void *a, const void *b) {
        return (*(unique_ptr<TestObject> *)a)->value - (*(unique_ptr<TestObject> *)b)->value;
    });
}
