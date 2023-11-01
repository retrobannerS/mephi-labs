#ifndef LAB2CORRECT2_SEQUENCE_HPP
#define LAB2CORRECT2_SEQUENCE_HPP
#include <stdexcept>
#include <iostream>
#include <utility>
#include "../Options/Options.hpp"


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
}
#include "Sequence.cpp"
#endif //LAB2CORRECT2_SEQUENCE_HPP
