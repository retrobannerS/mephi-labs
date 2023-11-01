#ifndef LAB3_PRIORITYQUEUE_HPP
#define LAB3_PRIORITYQUEUE_HPP
#include <utility>
#include <stdexcept>
#include "../BaseContainer.hpp"
#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "Sequence.hpp"
#include "ListSequence.hpp"
#include "Options.hpp"

using namespace std;
using namespace lab2;

namespace lab3 {
    template<typename T>
    class PriorityQueue : public BaseContainer<pair<T, int>> {
    private:
        using BaseContainer<pair<T, int>>::sequence;
        [[nodiscard]] int findMaxPriorityIndex() const;
        [[nodiscard]] int findMinPriorityIndex() const;
    public:
        using BaseContainer<pair<T, int>>::empty;
        using BaseContainer<pair<T, int>>::size;

        PriorityQueue();
        explicit PriorityQueue(int size, int priority);
        PriorityQueue(int size, const T &item, int priority);
        PriorityQueue(int size, const pair<T, int> *items);
        explicit PriorityQueue(const DynamicArray<pair<T, int>> &array);
        explicit PriorityQueue(const LinkedList<pair<T, int>> &list);
        explicit PriorityQueue(const Sequence<pair<T, int>> *sequence);
        PriorityQueue(const PriorityQueue<T> &other);

        //memory deletes in ~IEnumerable;
        ~PriorityQueue();

        void push(const T &item, int priority);
        T pop();
        Options<T> tryPop();
        pair<T, int> top();
        Options<pair<T, int>> tryTop();
        pair<T, int> bottom();
        Options<pair<T, int>> tryBottom();

        PriorityQueue<T> *concat(const PriorityQueue<T> &other) const;
        PriorityQueue<T> *getSubQueue(int start, int end) const;
        PriorityQueue<T> *operator +(const PriorityQueue<T> &other) const;

        PriorityQueue<T> *map(T (*func)(const T &)) const;
        T reduce(T (*func)(const T &, const T &)) const;
        using BaseContainer<pair<T, int>>::reduce;
        pair<PriorityQueue<T> **, int> split(const pair<T, int> &delim) const;
        PriorityQueue<T> *where(bool (*func)(const T &)) const;
        int find(const Sequence<T> &find_sequence) const;
        Options<int> tryFind(const Sequence<T> &find_sequence) const;
    };

    template<typename T>
    int PriorityQueue<T>::findMaxPriorityIndex() const {
        int max_priority = sequence->Get(0).second;
        int max_priority_index = 0;
        for (int i = 1; i < size(); ++i) {
            if (sequence->Get(i).second < max_priority) {
                max_priority = sequence->Get(i).second;
                max_priority_index = i;
            }
        }
        return max_priority_index;
    }

    template<typename T>
    int PriorityQueue<T>::findMinPriorityIndex() const {
    int min_priority = sequence->Get(0).second;
    int min_priority_index = 0;
    for (int i = 1; i < size(); ++i) {
        if (sequence->Get(i).second > min_priority) {
            min_priority = sequence->Get(i).second;
            min_priority_index = i;
        }
    }
    return min_priority_index;
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue() {
        sequence = new ListSequence<pair<T, int>>();
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(int size, int priority) {
        pair<T, int> pair_item = make_pair(T(), priority);
        sequence = new ListSequence<pair<T, int>>(size, pair_item);
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(int size, const T &item, int priority) {
        pair<T, int> pair_item = make_pair(item, priority);
        sequence = new ListSequence<pair<T, int>>(size, pair_item);
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(int size, const pair<T, int> *items) {
        sequence = new ListSequence<pair<T, int>>(size, items);
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(const DynamicArray<pair<T, int>> &array) {
        sequence = new ListSequence<pair<T, int>>(array);
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(const LinkedList<pair<T, int>> &list) {
        sequence = new ListSequence<pair<T, int>>(list);
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(const Sequence<pair<T, int>> *sequence) {
        this->sequence = new ListSequence<pair<T, int>>(sequence);
    }

    template<typename T>
    PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> &other) {
        sequence = new ListSequence<pair<T, int>>(other.sequence);
    }

    template<typename T>
    PriorityQueue<T>::~PriorityQueue() = default;

    template<typename T>
    void PriorityQueue<T>::push(const T &item, int priority) {
        pair<T, int> pair_item = make_pair(item, priority);
        sequence->PushBack(pair_item);
    }

    template<typename T>
    T PriorityQueue<T>::pop() {
        if (empty()) {
            throw out_of_range("PriorityQueue is empty!");
        }
        int max_priority_index = findMaxPriorityIndex();
        pair<T, int> max_priority_item = sequence->Get(max_priority_index);
        sequence->PopFrom(max_priority_index);
        return max_priority_item.first;
    }

    template<typename T>
    Options<T> PriorityQueue<T>::tryPop() {
        if (empty()) {
            return Options<T>();
        }
        int max_priority_index = findMaxPriorityIndex();
        pair<T, int> max_priority_item = sequence->Get(max_priority_index);
        sequence->PopFrom(max_priority_index);
        return Options<T>(max_priority_item.first);
    }

    template<typename T>
    pair<T, int> PriorityQueue<T>::top() {
        if (empty()) {
            throw out_of_range("PriorityQueue is empty!");
        }
        int max_priority_index = findMaxPriorityIndex();
        return sequence->Get(max_priority_index);
    }

    template<typename T>
    Options<pair<T, int>> PriorityQueue<T>::tryTop() {
        if (empty()) {
            return Options<pair<T, int>>();
        }
        int max_priority_index = findMaxPriorityIndex();
        pair<T, int> max_priority_item = sequence->Get(max_priority_index);
        return Options<pair<T, int>>(max_priority_item);
    }

    template<typename T>
    pair<T, int> PriorityQueue<T>::bottom() {
        if (empty()) {
            throw out_of_range("PriorityQueue is empty!");
        }
        int min_priority_index = findMinPriorityIndex();
        return sequence->Get(min_priority_index);
    }

    template<typename T>
    Options<pair<T, int>> PriorityQueue<T>::tryBottom() {
        if (empty()) {
            return Options<pair<T, int>>();
        }
        int min_priority_index = findMinPriorityIndex();
        pair<T, int> min_priority_item = sequence->Get(min_priority_index);
        return Options<pair<T, int>>(min_priority_item);
    }

    template<typename T>
    PriorityQueue<T> *PriorityQueue<T>::concat(const PriorityQueue<T> &other) const {
        Sequence<pair<T, int>> *concated = sequence->Concat(*other.sequence);
        auto *result = new PriorityQueue<T>(concated);
        delete concated;
        return result;
    }

    template<typename T>
    PriorityQueue<T> *PriorityQueue<T>::getSubQueue(int start, int end) const {
        try {
            Sequence<pair<T, int>> *sub_sequence = sequence->GetSubSequence(start, end);
            auto *result = new PriorityQueue<T>(sub_sequence);
            delete sub_sequence;
            return result;
        } catch (out_of_range &e) {
            throw out_of_range("Index out of range!");
        }
    }


    template<typename T>
    PriorityQueue<T> *PriorityQueue<T>::operator+(const PriorityQueue<T> &other) const {
        return concat(other);
    }

    template<typename T>
    PriorityQueue<T> *PriorityQueue<T>::map(T (*func)(const T &)) const {
        Sequence<T> *sequence_for_map = new ListSequence<T>();
        for(int i = 0; i < size(); ++i) {
            sequence_for_map->PushBack(sequence->Get(i).first);
        }
        Sequence<T> *mapped_sequence = sequence_for_map->Map(func);
        delete sequence_for_map;

        Sequence<pair<T, int>> *result_sequence = new ListSequence<pair<T, int>>();
        for(int i = 0; i < mapped_sequence->GetSize(); ++i) {
            result_sequence->PushBack(make_pair(mapped_sequence->Get(i), sequence->Get(i).second));
        }
        delete mapped_sequence;

        auto *result = new PriorityQueue<T>(result_sequence);
        delete result_sequence;

        return result;
    }

    template<typename T>
    pair<PriorityQueue<T> **, int> PriorityQueue<T>::split(const pair<T, int> &delim) const {
        pair<Sequence<pair<T, int>> **, int> splitted_pair = sequence->Split(delim);
        auto **splitted_sequences = splitted_pair.first;
        int splitted_size = splitted_pair.second;
        auto **result = new PriorityQueue<T> *[splitted_size];
        for(int i = 0; i < splitted_size; ++i) {
            result[i] = new PriorityQueue<T>(splitted_sequences[i]);
            delete splitted_sequences[i];
        }
        delete[] splitted_sequences;
        return make_pair(result, splitted_size);
    }

    template<typename T>
    PriorityQueue<T> *PriorityQueue<T>::where(bool (*func)(const T &)) const {
        auto *result = new PriorityQueue<T>(this->sequence);
        for(int i = 0; i < result->size(); ++i) {
            if(!func(result->sequence->Get(i).first)) {
                result->sequence->PopFrom(i);
                --i;
            }
        }
        return result;
    }


    template<typename T>
    T PriorityQueue<T>::reduce(T (*func)(const T &, const T &)) const {
        if(size() < 2) {
            throw invalid_argument("Invalid size!");
        }
        Sequence<T> *sequence_for_reduce = new ListSequence<T>();
        for(int i = 0; i < size(); ++i) {
            sequence_for_reduce->PushBack(sequence->Get(i).first);
        }
        T reduced = sequence_for_reduce->Reduce(func);
        delete sequence_for_reduce;
        return reduced;
    }

}// namespace lab3

#endif //LAB3_PRIORITYQUEUE_HPP
