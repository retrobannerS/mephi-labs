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

        ~SmartDynamicArray() = default;

        SmartDynamicArray<T> &operator=(const SmartDynamicArray &other);
        SmartDynamicArray<T> &operator=(SmartDynamicArray &&other);
        SmartDynamicArray<T> &operator=(const lab2::DynamicArray<T> &other);

        T get(int index) const;
        [[nodiscard]] int getSize() const;
        SmartDynamicArray<T> getSubArray(int startIndex, int endIndex) const;

        void set(int index, const T &item);
        void set(int startIndex, int endIndex, const T &item);

        T &operator[](int index);
        SmartDynamicArray<T> operator+(const SmartDynamicArray<T> &other) const;

        void resize(int newSize);
        void resize(int newSize, const T &item);

        SmartDynamicArray<T> concat(const SmartDynamicArray<T> &other) const;
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
            this->size = size;
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
    SmartDynamicArray<T>::SmartDynamicArray(const SmartDynamicArray &other) {
        size = other.size;
        data = make_shared<T[]>(size);
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray(SmartDynamicArray &&other) {
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
    }

    template <typename T>
    SmartDynamicArray<T>::SmartDynamicArray(const lab2::DynamicArray<T> &other) {
        size = other.GetSize();
        data = make_shared<T[]>(size);
        for (int i = 0; i < size; i++) {
            data[i] = other.Get(i);
        }
    }

    template <typename T>
    SmartDynamicArray<T> &SmartDynamicArray<T>::operator=(const SmartDynamicArray &other) {
        if (this == &other) {
            return *this;
        }
        size = other.size;
        data = make_shared<T[]>(size);
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        return *this;
    }

    template <typename T>
    SmartDynamicArray<T> &SmartDynamicArray<T>::operator=(SmartDynamicArray &&other) {
        if (this == &other) {
            return *this;
        }
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
        return *this;
    }

    template <typename T>
    SmartDynamicArray<T> &SmartDynamicArray<T>::operator=(const lab2::DynamicArray<T> &other) {
        size = other.GetSize();
        data = make_shared<T[]>(size);
        for (int i = 0; i < size; i++) {
            data[i] = other.Get(i);
        }
        return *this;
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
    SmartDynamicArray<T> SmartDynamicArray<T>::getSubArray(int startIndex, int endIndex) const {
        if (startIndex < 0 or startIndex >= size or endIndex < 0 or endIndex > size) {
            throw std::out_of_range("Index out of range");
        } else if (startIndex > endIndex) {
            throw std::invalid_argument("Start index must be less than end index");
        } else {
            int newSize = endIndex - startIndex;
            SmartDynamicArray result(newSize);
            for (int i = 0; i < newSize; i++) {
                result.data[i] = data[startIndex + i];
            }
            return result;
        }
    }

    template <typename T>
    void SmartDynamicArray<T>::set(int index, const T &item) {
        if (index >= size or index < 0) {
            throw std::out_of_range("Index out of range");
        } else {
            data[index] = item;
        }
    }

    template <typename T>
    void SmartDynamicArray<T>::set(int startIndex, int endIndex, const T &item) {
        if (startIndex < 0 or startIndex >= size or endIndex < 0 or endIndex > size) {
            throw std::out_of_range("Index out of range");
        } else if (startIndex > endIndex) {
            throw std::invalid_argument("Start index must be less than end index");
        } else {
            for (int i = startIndex; i < endIndex; i++) {
                data[i] = item;
            }
        }
    }

    template <typename T>
    T &SmartDynamicArray<T>::operator[](int index) {
        if (index >= size or index < 0) {
            throw std::out_of_range("Index out of range");
        } else {
            return data[index];
        }
    }

    template <typename T>
    SmartDynamicArray<T> SmartDynamicArray<T>::operator+(const SmartDynamicArray<T> &other) const {
        return concat(other);
    }

    template <typename T>
    void SmartDynamicArray<T>::resize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("Size must be positive");
        } else {
            auto newData = make_shared<T[]>(newSize);
            for (int i = 0; i < size and i < newSize; i++) {
                newData[i] = data[i];
            }
            data = newData;
            size = newSize;
        }
    }

    template <typename T>
    void SmartDynamicArray<T>::resize(int newSize, const T &item) {
        if (newSize < 0) {
            throw std::invalid_argument("Size must be positive");
        } else {
            auto newData = make_shared<T[]>(newSize);
            for (int i = 0; i < size and i < newSize; i++) {
                newData[i] = data[i];
            }
            for (int i = size; i < newSize; i++) {
                newData[i] = item;
            }
            data = newData;
            size = newSize;
        }
    }

    template <typename T>
    SmartDynamicArray<T> SmartDynamicArray<T>::concat(const SmartDynamicArray<T> &other) const {
        int newSize = size + other.size;
        SmartDynamicArray result(newSize);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i];
        }
        for (int i = 0; i < other.size; i++) {
            result.data[size + i] = other.data[i];
        }
        return result;
    }

} // namespace sem3
