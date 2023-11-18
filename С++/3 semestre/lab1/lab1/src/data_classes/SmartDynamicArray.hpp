#pragma once
#include "DynamicArray.hpp"
#include "smart_pointers/SharedPtr.hpp"
#include <stdexcept>

namespace sem3 {
    template <typename T>
    class SmartDynamicArray {
    private:
        SharedPtr<T[]> data;
        int size;

    public:
        SmartDynamicArray();
        explicit SmartDynamicArray(int size);
        SmartDynamicArray(int size, const T &item);
        SmartDynamicArray(int size, const T *items);
        SmartDynamicArray(int size, const SharedPtr<T[]> &items);
        SmartDynamicArray(const SmartDynamicArray &other);
        SmartDynamicArray(SmartDynamicArray &&other);
        SmartDynamicArray(const lab2::DynamicArray<T> &other);
        SmartDynamicArray(lab2::DynamicArray<T> &&other);

        ~SmartDynamicArray() = default;

        SmartDynamicArray<T> &operator=(const SmartDynamicArray &other);
        SmartDynamicArray<T> &operator=(SmartDynamicArray &&other);
        SmartDynamicArray<T> &operator=(const lab2::DynamicArray<T> &other);
        SmartDynamicArray<T> &operator=(lab2::DynamicArray<T> &&other);

        T get(int index) const;
        [[nodiscard]] int getSize() const;
        SmartDynamicArray<T> &getSubArray(int startIndex, int endIndex) const;

        void set(int index, const T &item);
        void set(int startIndex, int endIndex, const T &item);

        T &operator[](int index);
        SmartDynamicArray<T> &operator+(const SmartDynamicArray &other) const;

        void resize(int newSize);
        void resize(int newSize, const T &item);

        SmartDynamicArray<T> &concat(const SmartDynamicArray<T> &other) const;
    };

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray() : data(SharedPtr<T[]>()), size(0) {}

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray(int size) {
        if (size < 0) {
            throw std::invalid_argument("Size must be positive");
        } else {
            this->size = size;
            data = make_shared<T[]>(size);
        }
    }

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray(int size, const T &item) {
        if (size < 0) {
            throw std::invalid_argument("Size must be positive");
        } else {
            size = size;
            data = make_shared<T[]>(size);
            for (int i = 0; i < size; i++) {
                data[i] = item;
            }
        }
    }

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray(int size, const T *items) {
        if (size < 0) {
            throw std::invalid_argument("Size must be positive");
        } else {
            this->size = size;
            data = make_shared<T[]>(size);
            for (int i = 0; i < size; i++) {
                data[i] = items[i];
            }
        }
    }

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray(int size, const SharedPtr<T[]> &items) {
        if (size < 0) {
            throw std::invalid_argument("Size must be positive");
        } else {
            this->size = size;
            data = items;
        }
    }

    template <typename T>
    T SmartDynamicArray<T>::get(int index) const {
        if (index >= size or index < 0) {
            throw std::out_of_range("Index out of range");
        } else {
            return data[index];
        }
    }

    template <typename T>
    int SmartDynamicArray<T>::getSize() const {
        return size;
    }

    template <typename T>
    T &SmartDynamicArray<T>::operator[](int index) {
        if (index >= size or index < 0) {
            throw std::out_of_range("Index out of range");
        } else {
            return data[index];
        }
    }

} // namespace sem3
