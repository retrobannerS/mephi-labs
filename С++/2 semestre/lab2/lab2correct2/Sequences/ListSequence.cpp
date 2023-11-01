#include "ListSequence.hpp"

namespace lab2 {
    template <typename T>
    Sequence<Sequence<T> *> *ListSequence<T>::Zip(Sequence<Sequence<T> *> *sqs) {
        auto result = new ListSequence<Sequence<T>*>;
        if(sqs->GetSize() == 0)
            return result;
        int min_size = sqs->Get(0)->GetSize();
        for(int i = 1; i != sqs->GetSize(); ++i) {
            if(sqs->Get(i)->GetSize() < min_size)
                min_size = sqs->Get(i)->GetSize();
        }

        for(int i = 0; i != min_size; ++i) {
            auto *tmp = new ArraySequence<T>;
            for(int j = 0; j != sqs->GetSize(); ++j) {
                tmp->PushBack(sqs->Get(j)->Get(i));
            }
            result->PushBack(tmp);
        }

        return result;
    }

    template <typename T>
    ListSequence<T>::ListSequence() = default;

    template <typename T>
    ListSequence<T>::ListSequence(int size) : ListSequence(size, T()) {}

    template <typename T>
    ListSequence<T>::ListSequence(int size, const T &item) : ker(new LinkedList<T>(size, item)) {}

    template <typename T>
    ListSequence<T>::ListSequence(int size, const T *items) : ker(new LinkedList<T>(size, items)) {}

    template <typename T>
    ListSequence<T>::ListSequence(const DynamicArray<T> &arr) : ListSequence(arr.GetSize()) {
        for(int i = 0; i != arr.GetSize(); ++i) {
            this->Set(i, arr.Get(i));
        }
    }

    template <typename T>
    ListSequence<T>::ListSequence(const LinkedList<T> &list) : ker(new LinkedList<T>(list)) {}

    template <typename T>
    ListSequence<T>::ListSequence(const ArraySequence<T> &arr) {
        for(int i = 0; i != arr.GetSize(); ++i) {
            this->PushBack(arr.Get(i));
        }
    }

    template <typename T>
    ListSequence<T>::ListSequence(const Sequence<T> *seq) {
        for(int i = 0; i != seq->GetSize(); ++i) {
            this->PushBack(seq->Get(i));
        }
    }

    template <typename T>
    ListSequence<T>::ListSequence(const ListSequence<T> &other) : ker(new LinkedList<T>(*other.ker)) {}

    template <typename T>
    ListSequence<T>::~ListSequence() {
        delete this->ker;
    }

    template <typename T>
    T ListSequence<T>::Get(int index) const {
        if(index < 0 or index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        return this->ker->Get(index);
    }

    template <typename T>
    ListSequence<T> *ListSequence<T>::GetSubSequence(int start, int end) const {
        if(start < 0 or start >= this->GetSize() or end < 0 or end >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        return new ListSequence<T>(this->ker->GetSubList(start, end));
    }

    template <typename T>
    size_t ListSequence<T>::GetSize() const {
        return this->ker->GetSize();
    }

    template <typename T>
    void ListSequence<T>::Set(int index, const T &item) {
        if(index < 0 or index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        this->ker->Set(index, item);
    }

    template <typename T>
    void ListSequence<T>::InsertAt(int index, const T &item) {
        if(index < 0 or index > this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        this->ker->InsertAt(index, item);
    }

    template <typename T>
    void ListSequence<T>::PopFrom(int index) {
        if(index < 0 or index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        this->ker->PopFrom(index);
    }

    template <typename T>
    T &ListSequence<T>::operator [](int index) {
        if(index < 0 or index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        return this->ker->operator[](index);
    }

    template <typename T>
    ListSequence<T> &ListSequence<T>::operator =(const ListSequence<T> &other) {
        if(this != &other) {
            delete this->ker;
            this->ker = new LinkedList<T>(*other.ker);
        }
        return *this;
    }

    template <typename T>
    Sequence<T> *ListSequence<T>::Concat(const Sequence<T> &another) const {
        Sequence<T> *res = new ListSequence<T>(this);
        for(int i = 0; i != another.GetSize(); ++i) {
            res->PushBack(another.Get(i));
        }
        return res;
    }

    template <typename T>
    Sequence<T> *ListSequence<T>::Map(T (*func)(const T &)) const {
        Sequence<T> *res = new ListSequence<T>(this);
        for(int i = 0; i != res->GetSize(); ++i) {
            res->Set(i, func(this->Get(i)));
        }
        return res;
    }

    template <typename T>
    std::pair<Sequence<T> **, int> ListSequence<T>::Split(const T &delim) const {
        int result_size = 1;
        for(int i = 0; i != this->GetSize(); ++i) {
            if(this->Get(i) == delim) {
                result_size++;
            }
        }
        Sequence<T> **result_ptr = new Sequence<T>*[result_size];

        Sequence<T> *tmp = new ListSequence<T>;
        int tmp_index = 0;
        for(int i = 0; i != this->GetSize(); ++i) {
            if(this->Get(i) == delim) {
                result_ptr[tmp_index++] = tmp;
                tmp = new ListSequence<T>;
            } else {
                tmp->PushBack(this->Get(i));
            }
        }
        result_ptr[tmp_index] = tmp;
        std::pair<Sequence<T> **, int> result = {result_ptr, result_size};
        return result;
    }
} // lab2