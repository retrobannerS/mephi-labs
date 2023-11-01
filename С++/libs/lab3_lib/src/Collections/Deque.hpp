#ifndef LAB3_DEQUE_HPP
#define LAB3_DEQUE_HPP
#include <utility>
#include <stdexcept>
#include "../BaseContainer.hpp"
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "ListSequence.hpp"
#include "Options.hpp"

using namespace lab2;

namespace lab3 {
    template<typename T>
    class Deque : public BaseContainer<T> {
    private:
        using BaseContainer<T>::sequence;
    public:
        using BaseContainer<T>::empty;
        using BaseContainer<T>::size;

        Deque();
        explicit Deque(int size);
        Deque(int size, const T &item);
        Deque(int size, const T *items);
        explicit Deque(const DynamicArray<T> &array);
        explicit Deque(const LinkedList<T> &list);
        explicit Deque(const Sequence<T> *sequence);
        Deque(const Deque<T> &other);

        //memory deletes in ~IEnumerable;
        ~Deque();

        void pushFront(const T &item);
        void pushBack(const T &item);
        T popFront();
        T popBack();
        Options<T> tryPopFront();
        Options<T> tryPopBack();

        T front() const;
        T back() const;
        Options<T> tryFront() const;
        Options<T> tryBack() const;

        Deque<T> *concat(const Deque<T> &other) const;
        Deque<T> *getSubDeque(int start, int end) const;
        Deque<T> *operator+(const Deque<T> &other) const;

        Deque<T> *map(T (*func)(const T &)) const;
        std::pair<Deque<T> **, int> split(const T &delim) const;
        Deque<T> *where(bool (*func)(const T &)) const;
    };

    template<typename T>
    Deque<T>::Deque() {
        sequence = new ListSequence<T>();
    }

    template<typename T>
    Deque<T>::Deque(int size) {
        sequence = new ListSequence<T>(size);
    }

    template<typename T>
    Deque<T>::Deque(int size, const T &item) {
        sequence = new ListSequence<T>(size, item);
    }

    template<typename T>
    Deque<T>::Deque(int size, const T *items) {
        sequence = new ListSequence<T>(size, items);
    }

    template<typename T>
    Deque<T>::Deque(const DynamicArray<T> &array) {
        sequence = new ListSequence<T>(array);
    }

    template<typename T>
    Deque<T>::Deque(const LinkedList<T> &list) {
        sequence = new ListSequence<T>(list);
    }

    template<typename T>
    Deque<T>::Deque(const Sequence<T> *sequence) {
        this->sequence = new ListSequence<T>(sequence);
    }

    template<typename T>
    Deque<T>::Deque(const Deque<T> &other) {
        sequence = new ListSequence<T>(other.sequence);
    }

    template<typename T>
    Deque<T>::~Deque() = default;

    template<typename T>
    void Deque<T>::pushFront(const T &item) {
        sequence->PushFront(item);
    }

    template<typename T>
    void Deque<T>::pushBack(const T &item) {
        sequence->PushBack(item);
    }

    template<typename T>
    T Deque<T>::popFront() {
        try {
            T item = sequence->GetFirst();
            sequence->PopFront();
            return item;
        } catch (std::out_of_range &e) {
            throw std::out_of_range("Deque is empty!");
        }
    }

    template<typename T>
    T Deque<T>::popBack() {
        try {
            T item = sequence->GetLast();
            sequence->PopBack();
            return item;
        } catch (std::out_of_range &e) {
            throw std::out_of_range("Deque is empty!");
        }
    }

    template<typename T>
    Options<T> Deque<T>::tryPopFront() {
        if (empty()) {
            return Options<T>();
        }
        T item = sequence->GetFirst();
        sequence->PopFront();
        return Options<T>(item);
    }

    template<typename T>
    Options<T> Deque<T>::tryPopBack() {
        if (empty()) {
            return Options<T>();
        }
        T item = sequence->GetLast();
        sequence->PopBack();
        return Options<T>(item);
    }

    template<typename T>
    T Deque<T>::front() const {
        try {
            return sequence->GetFirst();
        } catch (std::out_of_range &e) {
            throw std::out_of_range("Deque is empty!");
        }
    }

    template<typename T>
    T Deque<T>::back() const {
        try {
            return sequence->GetLast();
        } catch (std::out_of_range &e) {
            throw std::out_of_range("Deque is empty!");
        }
    }

    template<typename T>
    Options<T> Deque<T>::tryFront() const {
        if (empty()) {
            return Options<T>();
        }
        return Options<T>(sequence->GetFirst());
    }

    template<typename T>
    Options<T> Deque<T>::tryBack() const {
        if (empty()) {
            return Options<T>();
        }
        return Options<T>(sequence->GetLast());
    }

    template<typename T>
    Deque<T> *Deque<T>::concat(const Deque<T> &other) const {
        Sequence<T> *concated = sequence->Concat(other.sequence);
        auto *deque = new Deque<T>(concated);
        delete concated;
        return deque;
    }

    template<typename T>
    Deque<T> *Deque<T>::getSubDeque(int start, int end) const {
        try {
            Sequence<T> *sub = sequence->GetSubSequence(start, end);
            auto *deque = new Deque<T>(sub);
            delete sub;
            return deque;
        } catch (std::out_of_range &e) {
            throw std::out_of_range("Index out of range!");
        }
    }

    template<typename T>
    Deque<T> *Deque<T>::operator+(const Deque<T> &other) const {
        return concat(other);
    }

    template<typename T>
    Deque<T> *Deque<T>::map(T (*func)(const T &)) const {
        Sequence<T> *mapped = sequence->Map(func);
        auto *deque = new Deque<T>(mapped);
        delete mapped;
        return deque;
    }

    template<typename T>
    std::pair<Deque<T> **, int> Deque<T>::split(const T &delim) const {
        std::pair<Sequence<T> **, int> splitted_pair = sequence->Split(delim);
        Sequence<T> **splitted_sequence = splitted_pair.first;
        int splitted_size = splitted_pair.second;
        auto **deques = new Deque<T> *[splitted_size];
        for (int i = 0; i < splitted_size; i++) {
            deques[i] = new Deque<T>(splitted_sequence[i]);
            delete splitted_sequence[i];
        }
        delete[] splitted_sequence;
        return std::make_pair(deques, splitted_size);
    }

    template<typename T>
    Deque<T> *Deque<T>::where(bool (*func)(const T &)) const {
        Sequence<T> *filtered_sequence = new ListSequence<T>();
        for(int i = 0; i != size(); ++i) {
            T item = sequence->Get(i);
            bool flag = func(item);
            if(flag)
                filtered_sequence->PushBack(item);
        }
        auto *result = new Deque<T>(filtered_sequence);
        delete filtered_sequence;
        return result;
    }
} // namespace lab3


#endif //LAB3_DEQUE_HPP
