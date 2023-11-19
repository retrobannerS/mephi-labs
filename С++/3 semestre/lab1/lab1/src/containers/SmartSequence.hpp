#pragma once
#include <stdexcept>
#include <iostream>
#include "Options.hpp"
#include "smart_pointers/SharedPtr.hpp"

using namespace lab2;

namespace sem3 {
    template <typename T>
    class SmartSequence {
    public:
        ~SmartSequence() = default;

        T getFirst() const;
        T getLast() const;
        virtual T get(int index) const = 0;
        virtual int getSize() const = 0;
        //virtual SharedPtr<SmartSequence<T>> getSubSequencePtr(int startIndex, int endIndex) const = 0;

        virtual void set(int index, const T &item) = 0;
        void set(int startIndex, int endIndex, const T &item);

        void append(const T &item);
        void prepend(const T &item);
        virtual void insertAt(int index, const T &item) = 0;

        void removeFirst();
        void removeLast();
        virtual void removeAt(int index) = 0;

        virtual T &operator[](int index) = 0;
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
        for (int i = startIndex; i < endIndex; i++) {
            Set(i, item);
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
} // namespace sem3