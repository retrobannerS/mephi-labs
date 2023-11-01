#ifndef LAB2CORRECT2_DYNAMICARRAY_HPP
#define LAB2CORRECT2_DYNAMICARRAY_HPP

namespace lab2 {

    template <typename T>
    class DynamicArray {
    private:
        T *arr = nullptr;
        size_t size = 0;
    public:
        DynamicArray();
        explicit DynamicArray(int size);
        DynamicArray(int size, const T &item);
        DynamicArray(int size, const T *items);
        DynamicArray(const DynamicArray &other);

        ~DynamicArray();

        T Get(int index) const;
        [[nodiscard]] size_t GetSize() const;
        DynamicArray<T> GetSubArray(int start, int end) const;

        void Set(int index, const T &value);
        void Set(int start, int count, const T &value);

        T &operator[](int index);
        DynamicArray<T> &operator =(const DynamicArray<T> &other);
        DynamicArray<T> operator +(const DynamicArray<T> &another) const;

        void Realloc(int new_size);
        DynamicArray<T> Concat(const DynamicArray <T> &another) const;
    };

} // lab2


#include "DynamicArray.cpp"
#endif //LAB2CORRECT2_DYNAMICARRAY_HPP
