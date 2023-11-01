#include "DynamicArray.hpp"
#include <stdexcept>

namespace lab2 {
    template <typename T>
    DynamicArray<T>::DynamicArray() = default;

    template <typename T>
    DynamicArray<T>::DynamicArray(int size) : DynamicArray(size, T()) {}

    template <typename T>
    DynamicArray<T>::DynamicArray(int size, const T &item) {
        if(size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        this->arr = new T[size];
        for(int i = 0; i != size; ++i) {
            this->arr[i] = item;
        }
        this->size = size;
    }

    template <typename T>
    DynamicArray<T>::DynamicArray(int size, const T *items) : DynamicArray(size) {
        for(int i = 0; i != size; ++i) {
            this->arr[i] = items[i];
        }
    }

    template <typename T>
    DynamicArray<T>::DynamicArray(const DynamicArray &other) : DynamicArray(other.GetSize()) {
        for(int i = 0; i != this->size; ++i) {
            this->arr[i] = other.arr[i];
        }
    }

    template <typename T>
    DynamicArray<T>::~DynamicArray() {
        delete[] this->arr;
    }

    template <typename T>
    T DynamicArray<T>::Get(int index) const {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        }
        return this->arr[index];
    }

    template <typename T>
    size_t DynamicArray<T>::GetSize() const {
        return this->size;
    }

    template <typename T>
    DynamicArray<T> DynamicArray<T>::GetSubArray(int start, int end) const {
        if(start < 0 || start >= this->size || end < 0 || end >= this->size || start > end) {
            throw std::out_of_range("Index out of range!");
        }
        DynamicArray<T> result(end - start + 1);
        for(int i = start; i <= end; ++i) {
            result.arr[i - start] = this->arr[i];
        }
        return result;
    }

    template <typename T>
    void DynamicArray<T>::Set(int index, const T &value) {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        }
        this->arr[index] = value;
    }

    template <typename T>
    void DynamicArray<T>::Set(int start, int count, const T &value) {
        if(start < 0 || start >= this->size || count < 0 || start + count > this->size) {
            throw std::out_of_range("Index out of range!");
        }
        for(int i = start; i != start + count; ++i) {
            this->arr[i] = value;
        }

    }


    template <typename T>
    T &DynamicArray<T>::operator[](int index) {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        }
        return this->arr[index];
    }

    template <typename T>
    DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other) {
        if(this == &other) {
            return *this;
        } else {
            delete[] this->arr;
            this->size = other.size;
            this->arr = new T[this->size];
            for(int i = 0; i != this->size; ++i) {
                this->arr[i] = other.arr[i];
            }
            return *this;
        }
    }

    template <typename T>
    DynamicArray<T> DynamicArray<T>::operator+(const DynamicArray<T> &another) const {
        return this->Concat(another);
    }


    template <typename T>
    void DynamicArray<T>::Realloc(int new_size) {
        if(new_size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
            size_t minimal_size = this->size < new_size ? this->size : new_size;
            T *new_arr = new T[new_size];
            for(int i = 0; i != minimal_size; ++i) {
                new_arr[i] = this->arr[i];
            }
            delete[] this->arr;
            this->arr = new_arr;
            this->size = new_size;
    }

    template <typename T>
    DynamicArray<T> DynamicArray<T>::Concat(const DynamicArray<T> &another) const {
        DynamicArray<T> result(this->size + another.size);
        for(int i = 0; i != this->size; ++i) {
            result.arr[i] = this->arr[i];
        }
        for(int i = 0; i != another.size; ++i) {
            result.arr[i + this->size] = another.arr[i];
        }
        return result;
    }
} // lab2