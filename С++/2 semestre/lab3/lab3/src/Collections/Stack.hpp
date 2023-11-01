#ifndef LAB3_STACK_HPP
#define LAB3_STACK_HPP
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
    template <typename T>
    class Stack : public BaseContainer<T>{
    private:
        using BaseContainer<T>::sequence;
    public:
        using BaseContainer<T>::empty;
        using BaseContainer<T>::size;

        Stack();
        explicit Stack(int size);
        Stack(int size, const T &item);
        Stack(int size, const T *items);
        explicit Stack(const DynamicArray<T> &array);
        explicit Stack(const LinkedList<T> &list);
        explicit Stack(const Sequence<T> *sequence);
        Stack(const Stack<T> &other);
        //memory deletes in ~IEnumerable;
        ~Stack();

        void push(const T &item);
        T pop();
        Options<T> tryPop();
        T peek();
        Options<T> tryPeek();

        Stack<T> *concat(const Stack<T> &other) const;
        Stack<T> *getSubStack(int start, int end) const;

        Stack<T> *operator +(const Stack<T> &other) const;

        Stack<T> *map(T (*func)(const T &)) const;
        std::pair<Stack<T> **, int> split(const T &delim) const;
        Stack<T> *where(bool (*func)(const T &)) const;
    };

    template <typename T>
    Stack<T>::Stack() {
        sequence = new ListSequence<T>();
    }

    template<typename T>
    Stack<T>::~Stack() = default;

    template<typename T>
    Stack<T>::Stack(int size) {
        sequence = new ListSequence<T>(size);
    }

    template<typename T>
    Stack<T>::Stack(int size, const T &item) {
        sequence = new ListSequence<T>(size, item);
    }

    template<typename T>
    Stack<T>::Stack(int size, const T *items) {
        sequence = new ListSequence<T>(size, items);
    }

    template<typename T>
    Stack<T>::Stack(const DynamicArray<T> &array) {
        sequence = new ListSequence<T>(array);
    }

    template<typename T>
    Stack<T>::Stack(const LinkedList<T> &list) {
        sequence = new ListSequence<T>(list);
    }

    template<typename T>
    Stack<T>::Stack(const Sequence<T> *sequence) {
        this->sequence = new ListSequence<T>(sequence);
    }

    template<typename T>
    Stack<T>::Stack(const Stack<T> &other) {
        sequence = new ListSequence<T>(other.sequence);
    }

    template<typename T>
    void Stack<T>::push(const T &item) {
        sequence->PushBack(item);
    }

    template<typename T>
    T Stack<T>::pop() {
        if(empty())
            throw std::out_of_range("Stack is empty!");
        T result = sequence->GetLast();
        sequence->PopBack();
        return result;
    }

    template<typename T>
    Options<T> Stack<T>::tryPop() {
        if(empty())
            return Options<T>();
        T result = sequence->GetLast();
        sequence->PopBack();
        return Options<T>(result);
    }

    template<typename T>
    T Stack<T>::peek() {
        if(empty())
            throw std::out_of_range("Stack is empty!");
        return sequence->GetLast();
    }

    template<typename T>
    Options<T> Stack<T>::tryPeek() {
        if(empty())
            return Options<T>();
        return Options<T>(sequence->GetLast());
    }

    template<typename T>
    Stack<T> *Stack<T>::concat(const Stack<T> &other) const {
        Sequence<T> *concatenated = sequence->Concat(*other.sequence);
        auto *result = new Stack<T>(concatenated);
        delete concatenated;
        return result;
    }

    template<typename T>
    Stack<T> *Stack<T>::getSubStack(int start, int end) const {
        Sequence<T> *subsequence = sequence->GetSubSequence(start, end);
        auto *result = new Stack<T>(subsequence);
        delete subsequence;
        return result;
    }

    template<typename T>
    Stack<T> *Stack<T>::operator+(const Stack<T> &other) const {
        return concat(other);
    }

    template<typename T>
    Stack<T> *Stack<T>::map(T (*func)(const T &)) const {
        Sequence<T> *mapped = sequence->Map(func);
        auto *result = new Stack<T>(mapped);
        delete mapped;
        return result;
    }

    template<typename T>
    std::pair<Stack<T> **, int> Stack<T>::split(const T &delim) const {
        std::pair<Sequence<T> **, int> splited_sequences = sequence->Split(delim);
        Sequence<T> **sequences = splited_sequences.first;
        int result_stacks_count = splited_sequences.second;
        auto **result_stacks = new Stack<T> *[result_stacks_count];
        for(int i = 0; i < result_stacks_count; i++) {
            result_stacks[i] = new Stack<T>(sequences[i]);
            delete sequences[i];
        }
        delete[] sequences;
        return std::make_pair(result_stacks, result_stacks_count);
    }

    template<typename T>
    Stack<T> *Stack<T>::where(bool (*func)(const T &)) const {
        Sequence<T> *filtered_sequence = new ListSequence<T>();
        for(int i = 0; i != size(); ++i) {
            T item = sequence->Get(i);
            bool flag = func(item);
            if(flag)
                filtered_sequence->PushBack(item);
        }
        auto *result = new Stack<T>(filtered_sequence);
        delete filtered_sequence;
        return result;
    }

} // lab3

#endif //LAB3_STACK_HPP
