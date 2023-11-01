#ifndef LAB2CORRECT2_LISTSEQUENCE_HPP
#define LAB2CORRECT2_LISTSEQUENCE_HPP
#include "Sequence.hpp"
#include "../Data_Classes/LinkedList.hpp"
#include "../Data_Classes/DynamicArray.hpp"
#include <stdexcept>

namespace lab2 {
    template <typename T>
    class ArraySequence;

    template <typename T>
    class ListSequence : public Sequence<T> {
    private:
        LinkedList<T> *ker = new LinkedList<T>;
    public:
        static Sequence<Sequence<T>*> *Zip(Sequence<Sequence<T>*> *sqs);
        ListSequence();
        explicit ListSequence(int size);
        ListSequence(int size, const T &item);
        ListSequence(int size, const T *items);
        explicit ListSequence(const DynamicArray<T> &arr);
        explicit ListSequence(const LinkedList<T> &list);
        explicit ListSequence(const Sequence<T> *seq);
        explicit ListSequence(const ArraySequence<T> &arr);
        ListSequence(const ListSequence<T> &other);
        ~ListSequence();

        T Get(int index) const override;
        [[nodiscard]] size_t GetSize() const override;
        ListSequence<T> *GetSubSequence(int start, int end) const override;

        void Set(int index, const T &item) override;
        using Sequence<T>::Set;

        void InsertAt(int index, const T &item) override;
        void PopFrom(int index) override;

        T &operator [](int index) override;
        ListSequence<T> &operator =(const ListSequence<T> &other);

        Sequence<T> *Concat(const Sequence<T> &another) const override;
        Sequence<T> *Map(T (*func)(const T &)) const override;
        std::pair<Sequence<T>**, int> Split(const T &delim) const override;
    };

} // lab2
#include "ListSequence.cpp"
#endif //LAB2CORRECT2_LISTSEQUENCE_HPP
