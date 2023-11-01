#ifndef LAB2CORRECT2_SEQUENCE_HPP
#define LAB2CORRECT2_SEQUENCE_HPP
#include <stdexcept>
#include <iostream>
#include <utility>
#include "Options.hpp"

namespace lab2 {
    template <typename T>
    class Sequence {
    public:
        virtual ~Sequence();

        T GetFirst() const;
        T GetLast() const;
        Options<T> TryGetFirst() const;
        Options<T> TryGetLast() const;
        [[nodiscard]] virtual T Get(int index) const = 0;
        Options<T> TryGet(int index) const;
        [[nodiscard]] virtual size_t GetSize() const = 0;
        virtual Sequence<T> *GetSubSequence(int start, int end) const = 0;

        virtual void Set(int index, const T &item) = 0;
        void Set(int start, int count, const T &item);
        virtual void PushBack(const T &item);
        virtual void PushFront(const T &item);
        virtual void InsertAt(int index, const T &item) = 0;
        virtual void PopBack();
        virtual void PopFront();
        virtual void PopFrom(int index) = 0;

        virtual Sequence<T> *operator +(const Sequence<T> &another) const;
        virtual T &operator [](int index) = 0;

        [[nodiscard]] virtual Sequence<T> *Concat(const Sequence<T> &another) const = 0;
        virtual Sequence<T> *Map(T (*func)(const T &)) const = 0;
        virtual T Reduce(T (*func)(const T &, const T &)) const;
        size_t Find(const T &item) const;
        Options<T> TryFind(const T &item) const;
        virtual std::pair<Sequence<T>**, int> Split(const T &delim) const = 0;
        void Slice(int start, int count, const Sequence<T> &sq);

        bool Empty();
        void Clear();
    };
    template <typename T>
    Sequence<T>::~Sequence() = default;

    template <typename T>
    T Sequence<T>::GetFirst() const {
        if (this->GetSize() == 0) {
            throw std::out_of_range("Index out of range!");
        } else {
            return Get(0);
        }
    }

    template <typename T>
    T Sequence<T>::GetLast() const {
        if (this->GetSize() == 0) {
            throw std::out_of_range("Index out of range!");
        }
        return this->Get(this->GetSize() - 1);
    }

    template <typename T>
    Options<T> Sequence<T>::TryGetFirst() const {
        return this->TryGet(0);
    }

    template <typename T>
    Options<T> Sequence<T>::TryGetLast() const {
        return this->TryGet(this->GetSize() - 1);
    }

    template <typename T>
    Options<T> Sequence<T>::TryGet(int index) const {
        if (index < 0 || index >= this->GetSize()) {
            return Options<T>();
        }
        return Options<T>(this->Get(index));
    }

    template <typename T>
    void Sequence<T>::Set(int start, int count, const T &item) {
        if (start < 0 || start >= this->GetSize() || count <= 0 || start + count > this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        for (int i = start; i < start + count; i++) {
            this->Set(i, item);
        }
    }

    template <typename T>
    void Sequence<T>::PushBack(const T &item) {
        this->InsertAt(this->GetSize(), item);
    }

    template <typename T>
    void Sequence<T>::PushFront(const T &item) {
        this->InsertAt(0, item);
    }

    template <typename T>
    void Sequence<T>::PopBack() {
        this->PopFrom(this->GetSize() - 1);
    }

    template <typename T>
    void Sequence<T>::PopFront() {
        this->PopFrom(0);
    }

    template <typename T>
    Sequence<T> *Sequence<T>::operator+(const Sequence<T> &another) const {
        return this->Concat(another);
    }

    template <typename T>
    T Sequence<T>::Reduce(T (*func)(const T &, const T &)) const {
        if (this->GetSize() < 2) {
            throw std::invalid_argument("Invalid size!");
        }
        T res = func(this->Get(0), this->Get(1));
        for (int i = 2; i < this->GetSize(); i++) {
            res = func(res, this->Get(i));
        }
        return res;
    }

    template <typename T>
    size_t Sequence<T>::Find(const T &item) const {
        for (int i = 0; i < this->GetSize(); i++) {
            if (this->Get(i) == item) {
                return i;
            }
        }
        throw std::invalid_argument("Item not found!");
    }

    template <typename T>
    Options<T> Sequence<T>::TryFind(const T &item) const {
        for (int i = 0; i < this->GetSize(); i++) {
            if (this->Get(i) == item) {
                return Options<T>(i);
            }
        }
        return Options<T>();
    }

    template <typename T>
    void Sequence<T>::Slice(int start, int count, const Sequence<T> &sq) {
        int true_start = start < 0 ? this->GetSize() + start : start;
        int true_end = start < 0 ? true_start - count : true_start + count; //end is not included
        if (true_start < 0 || true_start >= this->GetSize() || true_end < -1 ||
            true_end > this->GetSize() || count != sq.GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        if (start < 0) {
            for (int i = true_start; i != true_end; --i) {
                this->Set(i, sq.Get(true_start - i));
            }
        } else {
            for (int i = true_start; i != true_end; ++i) {
                this->Set(i, sq.Get(i - true_start));
            }
        }
    }

    template <typename T>
    bool Sequence<T>::Empty() {
        return this->GetSize() == 0;
    }

    template <typename T>
    void Sequence<T>::Clear() {
        while (!this->Empty()) {
            this->PopBack();
        }
    }

}
#endif //LAB2CORRECT2_SEQUENCE_HPP
