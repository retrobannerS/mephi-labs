#pragma once
#include "ArraySequence.hpp"
#include "containers/SmartSequence.hpp"
#include "data_classes/SmartDynamicArray.hpp"
#include "data_classes/SmartLinkedList.hpp"
#include "smart_pointers/UniquePtr.hpp"
#include <stdexcept>

namespace sem3 {
    template <typename T>
    class SmartListSequence;

    template <typename T>
    class SmartArraySequence : public SmartSequence<T> {
    private:
        UniquePtr<SmartDynamicArray<T>> array;
        int size;
        void autoReserve();
        void autoShrink();

    public:
        SmartArraySequence();
        explicit SmartArraySequence(int size);
        SmartArraySequence(int size, const T &item);
        SmartArraySequence(int size, const T *items);
        explicit SmartArraySequence(const SmartDynamicArray<T> &array);
        explicit SmartArraySequence(const SmartLinkedList<T> &list);
        explicit SmartArraySequence(const ArraySequence<T> &array);
        explicit SmartArraySequence(const Sequence<T> *sequence);
        explicit SmartArraySequence(const SmartSequence<T> *sequence);
        explicit SmartArraySequence(const SharedPtr<SmartSequence<T>> sequence);
        explicit SmartArraySequence(const UniquePtr<SmartSequence<T>> sequence);

        SmartArraySequence(const SmartArraySequence<T> &other);
        SmartArraySequence(SmartArraySequence<T> &&other) noexcept;

        SmartArraySequence<T> &operator=(const SmartArraySequence<T> &other);
        SmartArraySequence<T> &operator=(SmartArraySequence<T> &&other) noexcept;

        T get(int index) const override;
        int getSize() const override;
        int getCapacity() const;
        //SmartArraySequence<T> getSubSequence(int startIndex, int endIndex) const;
        //SharedPtr<SmartSequence<T>> getSubSequencePtr(int startIndex, int endIndex) const override;

        void set(int index, const T &item) override;
        using SmartSequence<T>::set;

        void insertAt(int index, const T &item) override;
        void removeAt(int index) override;

        T &operator[](int index) override;
        SmartArraySequence<T> concat(const SmartArraySequence<T> &other) const;

        void resize(int new_size);
        void resize(int new_size, const T &item);
        void reserve(int new_size);

        void clear();
        bool empty() const;
    };

    template <typename T>
    void SmartArraySequence<T>::autoReserve() {
        if (empty()) {
            array->resize(3);
        } else if (size >= getCapacity()) {
            array->resize(getCapacity() * 2);
        }
    }

    template <typename T>
    void SmartArraySequence<T>::autoShrink() {
        if (empty()) {
            array->resize(3);
        } else if (size <= getCapacity() / 3) {
            array->resize(getCapacity() / 2);
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence() : array(make_unique<SmartDynamicArray<T>>()), size(0) {}

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(int size) : array(make_unique<SmartDynamicArray<T>>(size)), size(size) {}

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(int size, const T &item)
        : array(make_unique<SmartDynamicArray<T>>(2 * size, item)), size(size) {}

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(int size, const T *items)
        : array(make_unique<SmartDynamicArray<T>>(2 * size)), size(size) {
        for (int i = 0; i < size; ++i) {
            set(i, items[i]);
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const SmartDynamicArray<T> &array) {
        size = array.getSize();
        this->array = make_unique<SmartDynamicArray<T>>(2 * size);
        for (int i = 0; i < size; ++i) {
            set(i, array.get(i));
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const SmartLinkedList<T> &list) {
        size = list.getSize();
        array = make_unique<SmartDynamicArray<T>>(2 * size);
        for (int i = 0; i < size; ++i) {
            set(i, list.get(i));
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const ArraySequence<T> &array) {
        size = array.GetSize();
        this->array = make_unique<SmartDynamicArray<T>>(2 * size);
        for (int i = 0; i < size; ++i) {
            set(i, array.Get(i));
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const Sequence<T> *sequence) {
        size = sequence->GetSize();
        array = make_unique<SmartDynamicArray<T>>(2 * size);
        for (int i = 0; i < size; ++i) {
            set(i, sequence->Get(i));
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const SmartSequence<T> *sequence) {
        size = sequence->getSize();
        array = make_unique<SmartDynamicArray<T>>(2 * size);
        for (int i = 0; i < size; ++i) {
            set(i, sequence->get(i));
        }
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const SharedPtr<SmartSequence<T>> sequence)
        : SmartArraySequence(*sequence) {}

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const UniquePtr<SmartSequence<T>> sequence)
        : SmartArraySequence(*sequence) {}

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(const SmartArraySequence<T> &other) {
        size = other.size;
        array = make_unique<SmartDynamicArray<T>>(other.array);
    }

    template <typename T>
    SmartArraySequence<T>::SmartArraySequence(SmartArraySequence<T> &&other) noexcept {
        size = std::move(other.size);
        array = std::move(other.array);
    }

    template <typename T>
    SmartArraySequence<T> &SmartArraySequence<T>::operator=(const SmartArraySequence<T> &other) {
        if (this == &other) {
            return *this;
        }
        size = other.size;
        array = make_unique<SmartDynamicArray<T>>(other.array);
        return *this;
    }

    template <typename T>
    SmartArraySequence<T> &SmartArraySequence<T>::operator=(SmartArraySequence<T> &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        size = std::move(other.size);
        array = std::move(other.array);
        return *this;
    }

    template <typename T>
    T SmartArraySequence<T>::get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array->get(index);
    }

    template <typename T>
    int SmartArraySequence<T>::getSize() const {
        return size;
    }

    template <typename T>
    int SmartArraySequence<T>::getCapacity() const {
        return array->getSize();
    }

    // template <typename T>
    // SmartArraySequence<T> SmartArraySequence<T>::getSubSequence(int startIndex, int endIndex) const {
    //     if (startIndex < 0 || startIndex >= size || endIndex < 0 || endIndex > size) {
    //         throw std::out_of_range("Index out of range");
    //     } else if (startIndex > endIndex) {
    //         throw std::invalid_argument("Start index is greater than end index");
    //     }
    //     SmartDynamicArray<T> subArray = array->getSubArray(startIndex, endIndex);
    //     SmartArraySequence<T> subSequence = SmartArraySequence<T>(subArray);
    //     return subSequence;
    // }

    // template <typename T>
    // SharedPtr<SmartSequence<T>> SmartArraySequence<T>::getSubSequencePtr(int startIndex, int endIndex) const {
    //     return SharedPtr<SmartSequence<T>>(&getSubSequence(startIndex, endIndex));
    // }

    template <typename T>
    void SmartArraySequence<T>::set(int index, const T &item) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        array->set(index, item);
    }

    template <typename T>
    void SmartArraySequence<T>::insertAt(int index, const T &item) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }
        autoReserve();
        for (int i = size; i != index; --i) {
            array->set(i, array->get(i - 1));
        }
        array->set(index, item);
        size++;
    }

    template <typename T>
    void SmartArraySequence<T>::removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i != size - 1; ++i) {
            array->set(i, array->get(i + 1));
        }
        size--;
        autoShrink();
    }

    template <typename T>
    T &SmartArraySequence<T>::operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array->operator[](index);
    }

    template <typename T>
    void SmartArraySequence<T>::resize(int new_size) {
        resize(new_size, T());
    }

    template <typename T>
    void SmartArraySequence<T>::resize(int new_size, const T &item) {
        if (new_size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        if (new_size == 0) {
            clear();
        } else if (new_size < size) {
            size = new_size;
            autoShrink();
        } else if (new_size > size) {
            reserve(2 * new_size);
            for (int i = size; i != new_size; ++i) {
                array->set(i, item);
            }
            size = new_size;
        }
    }

    template <typename T>
    void SmartArraySequence<T>::reserve(int new_size) {
        if (new_size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        if (new_size > getCapacity()) {
            array->resize(new_size);
        }
    }

    template <typename T>
    void SmartArraySequence<T>::clear() {
        size = 0;
        autoShrink();
    }

    template <typename T>
    bool SmartArraySequence<T>::empty() const {
        return size == 0;
    }
} // namespace sem3