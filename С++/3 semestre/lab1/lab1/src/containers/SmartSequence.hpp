#pragma once
#include "Options.hpp"
#include "smart_pointers/SharedPtr.hpp"
#include <iostream>
#include <stdexcept>

using namespace lab2;

namespace sem3 {
    template <typename T>
    class SmartSequence {
    public:
        virtual ~SmartSequence() = default;

        T getFirst() const;
        T getLast() const;
        virtual T get(int index) const = 0;
        virtual int getSize() const = 0;
        virtual SharedPtr<SmartSequence<T>> getSubSequence(int startIndex, int endIndex) const = 0;

        virtual void set(int index, const T &item) = 0;
        void set(int startIndex, int endIndex, const T &item);

        void append(const T &item);
        void prepend(const T &item);
        virtual void insertAt(int index, const T &item) = 0;

        void removeFirst();
        void removeLast();
        virtual void removeAt(int index) = 0;

        virtual void clear() = 0;
        bool empty() const;

        virtual T &operator[](int index) = 0;
        virtual SharedPtr<SmartSequence<T>> operator+(const SmartSequence<T> &other);

        virtual SharedPtr<SmartSequence<T>> concat(const SmartSequence<T> &other) const = 0;
        int find(const T &item) const;
        virtual SharedPtr<SmartSequence<T>> map(T (*mapper)(const T &)) const = 0;
        virtual SharedPtr<SmartSequence<T>> where(bool (*predicate)(const T &)) const = 0;
        virtual T reduce(T (*reducer)(const T &, const T &), const T &initialValue) const = 0;

        Options<T> tryGetFirst() const;
        Options<T> tryGetLast() const;
        Options<T> tryGet(int index) const;
        Options<int> tryFind(const T &item) const;
    };

    template <typename T>
    T SmartSequence<T>::getFirst() const {
        return get(0);
    }

    template <typename T>
    T SmartSequence<T>::getLast() const {
        return get(getSize() - 1);
    }

    template <typename T>
    void SmartSequence<T>::set(int startIndex, int endIndex, const T &item) {
        if (startIndex < 0 || startIndex >= getSize() || endIndex < 0 || endIndex > getSize()) {
            throw std::out_of_range("Index out of range");
        } else if (startIndex > endIndex) {
            throw std::invalid_argument("Start index must be less than end index");
        }
        for (int i = startIndex; i < endIndex; i++) {
            set(i, item);
        }
    }

    template <typename T>
    void SmartSequence<T>::append(const T &item) {
        insertAt(getSize(), item);
    }

    template <typename T>
    void SmartSequence<T>::prepend(const T &item) {
        insertAt(0, item);
    }

    template <typename T>
    void SmartSequence<T>::removeFirst() {
        removeAt(0);
    }

    template <typename T>
    void SmartSequence<T>::removeLast() {
        removeAt(getSize() - 1);
    }

    template <typename T>
    bool SmartSequence<T>::empty() const {
        return getSize() == 0;
    }

    template <typename T>
    SharedPtr<SmartSequence<T>> SmartSequence<T>::operator+(const SmartSequence<T> &other) {
        return concat(other);
    }

    template <typename T>
    int SmartSequence<T>::find(const T &item) const {
        for (int i = 0; i < getSize(); i++) {
            if (get(i) == item) {
                return i;
            }
        }
        throw std::invalid_argument("Item not found!");
    }

    template <typename T>
    Options<T> SmartSequence<T>::tryGetFirst() const {
        if (empty()) {
            return Options<T>();
        }
        return Options<T>(getFirst());
    }

    template <typename T>
    Options<T> SmartSequence<T>::tryGetLast() const {
        if (empty()) {
            return Options<T>();
        }
        return Options<T>(getLast());
    }

    template <typename T>
    Options<T> SmartSequence<T>::tryGet(int index) const {
        if (index < 0 || index >= getSize()) {
            return Options<T>();
        }
        return Options<T>(get(index));
    }

    template <typename T>
    Options<int> SmartSequence<T>::tryFind(const T &item) const {
        try {
            return Options<int>(find(item));
        } catch (std::invalid_argument &e) {
            return Options<int>();
        }
    }

} // namespace sem3