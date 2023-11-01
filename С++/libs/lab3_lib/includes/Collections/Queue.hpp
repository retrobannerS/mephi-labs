#ifndef LAB3_QUEUE_HPP
#define LAB3_QUEUE_HPP
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
    class Queue : public BaseContainer<T> {
    private:
        using BaseContainer<T>::sequence;
    public:
        using BaseContainer<T>::empty;
        using BaseContainer<T>::size;

        Queue();
        explicit Queue(int size);
        Queue(int size, const T &item);
        Queue(int size, const T *items);
        explicit Queue(const DynamicArray<T> &array);
        explicit Queue(const LinkedList<T> &list);
        explicit Queue(const Sequence<T> *sequence);
        Queue(const Queue<T> &other);

        //memory deletes in ~IEnumerable;
        ~Queue();

        void push(const T &item);
        T pop();
        Options<T> tryPop();

        T front() const;
        Options<T> tryFront() const;
        T back() const;
        Options<T> tryBack() const;


        Queue<T> *concat(const Queue<T> &other) const;
        Queue<T> *getSubQueue(int start, int end) const;
        Queue<T> *operator+(const Queue<T> &other) const;

        Queue<T> *map(T (*func)(const T &)) const;
        std::pair<Queue<T> **, int> split(const T &delim) const;
        Queue<T> *where(bool (*func)(const T &)) const;
    };

    template<typename T>
    Queue<T>::Queue() {
        sequence = new ListSequence<T>();
    }

    template<typename T>
    Queue<T>::Queue(int size) {
        sequence = new ListSequence<T>(size);
    }

    template<typename T>
    Queue<T>::Queue(int size, const T &item) {
        sequence = new ListSequence<T>(size, item);
    }

    template<typename T>
    Queue<T>::Queue(int size, const T *items) {
        sequence = new ListSequence<T>(size, items);
    }

    template<typename T>
    Queue<T>::Queue(const DynamicArray<T> &array) {
        sequence = new ListSequence<T>(array);
    }

    template<typename T>
    Queue<T>::Queue(const LinkedList<T> &list) {
        sequence = new ListSequence<T>(list);
    }

    template<typename T>
    Queue<T>::Queue(const Sequence<T> *sequence) {
        this->sequence = new ListSequence<T>(sequence);
    }

    template<typename T>
    Queue<T>::Queue(const Queue<T> &other) {
        sequence = new ListSequence<T>(other.sequence);
    }

    template<typename T>
    Queue<T>::~Queue() = default;

    template<typename T>
    void Queue<T>::push(const T &item) {
        sequence->PushBack(item);
    }

    template<typename T>
    T Queue<T>::pop() {
        if(empty())
            throw std::out_of_range("Stack is empty!");
        T result = sequence->GetFirst();
        sequence->PopFront();
        return result;
    }

    template<typename T>
    Options<T> Queue<T>::tryPop() {
        if(empty())
            return Options<T>();
        T result = sequence->GetFirst();
        sequence->PopFront();
        return Options<T>(result);
    }

    template<typename T>
    T Queue<T>::front() const {
        if(empty())
            throw std::out_of_range("Stack is empty!");
        return sequence->GetFirst();
    }

    template<typename T>
    Options<T> Queue<T>::tryFront() const {
        if(empty())
            return Options<T>();
        return Options<T>(sequence->GetFirst());
    }

    template<typename T>
    T Queue<T>::back() const {
        if(empty())
            throw std::out_of_range("Stack is empty!");
        return sequence->GetLast();
    }

    template<typename T>
    Options<T> Queue<T>::tryBack() const {
        if(empty())
            return Options<T>();
        return Options<T>(sequence->GetLast());
    }

    template<typename T>
    Queue<T> *Queue<T>::concat(const Queue<T> &other) const {
        Sequence<T> *concated_sequences = sequence->Concat(*other.sequence);
        auto *result = new Queue<T>(concated_sequences);
        delete concated_sequences;
        return result;
    }

    template<typename T>
    Queue<T> *Queue<T>::getSubQueue(int start, int end) const {
        try {
            Sequence<T> *sub_sequence = sequence->GetSubSequence(start, end);
            auto *result = new Queue<T>(sub_sequence);
            delete sub_sequence;
            return result;
        } catch (std::out_of_range &e) {
            throw std::out_of_range("Index out of range!");
        }
    }

    template<typename T>
    Queue<T> *Queue<T>::operator+(const Queue<T> &other) const {
        return concat(other);
    }

    template<typename T>
    Queue<T> *Queue<T>::map(T (*func)(const T &)) const {
        Sequence<T> *mapped_sequence = sequence->Map(func);
        auto *result = new Queue<T>(mapped_sequence);
        delete mapped_sequence;
        return result;
    }

    template<typename T>
    std::pair<Queue<T> **, int> Queue<T>::split(const T &delim) const {
        std::pair<Sequence<T> **, int> sequences_and_size = sequence->Split(delim);
        auto splitted_sequences = sequences_and_size.first;
        auto splitted_sequences_size = sequences_and_size.second;
        auto **splitted_queues = new Queue<T> *[splitted_sequences_size];
        for (int i = 0; i < splitted_sequences_size; ++i) {
            splitted_queues[i] = new Queue<T>(splitted_sequences[i]);
            delete splitted_sequences[i];
        }
        delete[] splitted_sequences;
        return std::pair<Queue<T> **, int>(splitted_queues, splitted_sequences_size);
    }

    template<typename T>
    Queue<T> *Queue<T>::where(bool (*func)(const T &)) const {
        Sequence<T> *filtered_sequence = new ListSequence<T>();
        for(int i = 0; i != size(); ++i) {
            T item = sequence->Get(i);
            bool flag = func(item);
            if(flag)
                filtered_sequence->PushBack(item);
        }
        auto *result = new Queue<T>(filtered_sequence);
        delete filtered_sequence;
        return result;
    }
}



#endif //LAB3_QUEUE_HPP
