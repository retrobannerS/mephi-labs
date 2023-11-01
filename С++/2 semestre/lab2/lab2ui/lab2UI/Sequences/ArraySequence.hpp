#ifndef LAB2CORRECT2_ARRAYSEQUENCE_HPP
#define LAB2CORRECT2_ARRAYSEQUENCE_HPP
#include "Sequence.hpp"
#include "../Data_Classes/LinkedList.hpp"
#include "../Data_Classes/DynamicArray.hpp"
#include <stdexcept>
#include <utility>

namespace lab2 {

    template <typename T>
    class ListSequence;

    template <typename T>
    class ArraySequence : public Sequence<T> {
    private:
        DynamicArray<T> *ker = new DynamicArray<T>;
        size_t size = 0;
        void AutoReserve();
        void AutoShrink();
    public:
        static Sequence<Sequence<T>*> *Zip(Sequence<Sequence<T>*> *sqs);
        ArraySequence();
        explicit ArraySequence(int size);
        ArraySequence(int size, const T &item);
        ArraySequence(int size, const T *items);
        explicit ArraySequence(const DynamicArray<T> &arr);
        explicit ArraySequence(const LinkedList<T> &list);
        explicit ArraySequence(const ListSequence<T> &list);
        explicit ArraySequence(const Sequence<T> *other);
        ArraySequence(const ArraySequence<T> &other);
        ~ArraySequence();

        T Get(int index) const override;
        [[nodiscard]] size_t GetSize() const override;
        [[nodiscard]] size_t GetCapacity() const;
        ArraySequence<T> *GetSubSequence(int start, int end) const override;

        void Set(int index, const T &item) override;
        using Sequence<T>::Set;

        void InsertAt(int index, const T &item) override;
        void PopFrom(int index) override;

        T &operator [](int index) override;
        ArraySequence<T> &operator =(const Sequence<T> &other);

        Sequence<T> *Concat(const Sequence<T> &another) const override;
        Sequence<T> *Map(T (*func)(const T &)) const override;
        std::pair<Sequence<T>**, int> Split(const T &delim) const override;
        void Resize(int new_size);
        void Resize(int new_size, const T &item);
        void Reserve(int new_size);
    };

} // lab2

#include "ArraySequence.cpp"
#endif //LAB2CORRECT2_ARRAYSEQUENCE_HPP
