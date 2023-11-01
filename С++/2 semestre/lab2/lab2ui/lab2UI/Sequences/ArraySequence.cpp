#include "ArraySequence.hpp"

namespace lab2 {
    template <typename T>
    Sequence<Sequence<T> *> *ArraySequence<T>::Zip(Sequence<Sequence<T>*> *sqs) {
        auto result = new ArraySequence<Sequence<T>*>;
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
    void ArraySequence<T>::AutoReserve() {
        if(this->Empty()) {
            this->ker->Realloc(3);
        } else if (this->size >= this->GetCapacity()){
            this->ker->Realloc(2 * this->GetCapacity());
        }
    }

    template <typename T>
    void ArraySequence<T>::AutoShrink() {
        if(this->Empty()) {
            this->ker->Realloc(3);
        } else if (this->size <= this->GetCapacity()/3){
            this->ker->Realloc(this->GetCapacity()/2);
        }
    }

    template <typename T>
    ArraySequence<T>::ArraySequence() = default;

    template <typename T>
    ArraySequence<T>::ArraySequence(int size) : ArraySequence(size, T()) {}

    template <typename T>
    ArraySequence<T>::ArraySequence(int size, const T &item) : ker(new DynamicArray<T>(2 * size, item)), size(size) {}

    template <typename T>
    ArraySequence<T>::ArraySequence(int size, const T *items) : ArraySequence(size) {
        for(int i = 0; i != size; ++i) {
            this->Set(i, items[i]);
        }
    }

    template <typename T>
    ArraySequence<T>::ArraySequence(const DynamicArray<T> &arr) : //arr + zero_array for ker->size = 2 * arr.size
    ker(new DynamicArray<T>(arr.Concat(DynamicArray<T>(arr.GetSize())))), size(arr.GetSize()) {}

    template <typename T>
    ArraySequence<T>::ArraySequence(const LinkedList<T> &list) {
        this->size = list.GetSize();
        this->ker = new DynamicArray<T>(2 * this->size);
        for(size_t i = 0; i != this->size; ++i) {
            this->ker->Set(i, list.Get(i));
        }
    }

    template <typename T>
    ArraySequence<T>::ArraySequence(const ListSequence<T> &list) {
        this->size = list.GetSize();
        this->ker = new DynamicArray<T>(2 * this->size);
        for(size_t i = 0; i != this->size; ++i) {
            this->ker->Set(i, list.Get(i));
        }
    }

    template <typename T>
    ArraySequence<T>::ArraySequence(const ArraySequence<T> &other) {
        this->size = other.size;
        this->ker = new DynamicArray<T>(2 * this->size);
        for(size_t i = 0; i != this->size; ++i) {
            this->ker->Set(i, other.ker->Get(i));
        }
    }

    template <typename T>
    ArraySequence<T>::ArraySequence(const Sequence<T> *other) {
        this->size = other->GetSize();
        this->ker = new DynamicArray<T>(2 * this->size);
        for(size_t i = 0; i != this->size; ++i) {
            this->Set(i, other->Get(i));
        }
    }

    template <typename T>
    ArraySequence<T>::~ArraySequence() {
        delete this->ker;
    }

    template<typename T>
    size_t ArraySequence<T>::GetSize() const {
        return this->size;
    }

    template <typename T>
    size_t ArraySequence<T>::GetCapacity() const {
        return this->ker->GetSize();
    }

    template <typename T>
    T ArraySequence<T>::Get(int index) const {
        if(index < 0 or index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        return this->ker->Get(index);
    }

    template <typename T>
    ArraySequence<T> *ArraySequence<T>::GetSubSequence(int start, int end) const {
        if(start < 0 or start >= this->GetSize() or end < 0 or end >= this->GetSize() or start > end) {
            throw std::out_of_range("Index out of range!");
        }
        auto *sub = new ArraySequence<T>(end - start + 1);
        for(int i = start; i <= end; i++) {
            sub->Set(i - start, this->Get(i));
        }
        return sub;
    }

    template<typename T>
    void ArraySequence<T>::Set(int index, const T &item) {
        if(index < 0 or index >= this->GetSize()) {
            throw std::out_of_range("Index out of range!");
        }
        this->ker->Set(index, item);
    }

    template <typename T>
    void ArraySequence<T>::InsertAt(int index, const T &item) {
        if(index < 0 or index > this->size) {
            throw std::out_of_range("Index out of range!");
        }
        AutoReserve();
        for(int i = this->size; i != index; --i) {
            this->ker->Set(i, this->ker->Get(i - 1));
        }
        this->ker->Set(index, item);
        this->size++;
    }

    template <typename T>
    void ArraySequence<T>::PopFrom(int index) {
        if(index < 0 || index >= this->size) {
            throw std::out_of_range("Index out of range!");
        }
        for(int i = index; i + 1 < size; ++i) {
            this->Set(i, this->Get(i + 1));
        }
        this->size--;
        AutoShrink();
    }

    template <typename T>
    T &ArraySequence<T>::operator [](int index) {
        return this->ker->operator [](index);
    }

    template <typename T>
    ArraySequence<T> &ArraySequence<T>::operator =(const Sequence<T> &other) {
        if(this != &other) {
            delete this->ker;
            this->size = other.GetSize();
            this->ker = new DynamicArray<T>(2 * this->size);
            for(size_t i = 0; i != this->size; ++i) {
                this->ker->Set(i, other.ker->Get(i));
            }
        }
        return *this;
    }

    template <typename T>
    Sequence<T> *ArraySequence<T>::Concat(const Sequence<T> &another) const {
        Sequence<T> *concat = new ArraySequence<T>(this->size + another.GetSize());
        for(int i = 0; i != this->size; ++i) {
            concat->Set(i, this->Get(i));
        }
        for(int i = 0; i != another.GetSize(); ++i) {
            concat->Set(i + this->size, another.Get(i));
        }
        return concat;
    }

    template <typename T>
    Sequence<T> *ArraySequence<T>::Map(T (*func)(const T &)) const {
        if(this->GetSize() == 0) {
            throw std::invalid_argument("Invalid size!");
        }
        auto *mapped = new ArraySequence<T>(this->size);
        for(int i = 0; i != this->size; ++i) {
            mapped->Set(i, func(this->Get(i)));
        }
        return mapped;
    }

    template <typename T>
    std::pair<Sequence<T>**, int> ArraySequence<T>::Split(const T &delim) const {
        int result_size = 1;
        for(int i = 0; i != this->GetSize(); ++i) {
            if(this->Get(i) == delim) {
                result_size++;
            }
        }
        Sequence<T> **result_ptr = new Sequence<T>*[result_size];

        Sequence<T> *tmp = new ArraySequence<T>;
        int tmp_index = 0;
        for(int i = 0; i != this->GetSize(); ++i) {
            if(this->Get(i) == delim) {
                result_ptr[tmp_index++] = tmp;
                tmp = new ArraySequence<T>;
            } else {
                tmp->PushBack(this->Get(i));
            }
        }
        result_ptr[tmp_index] = tmp;
        std::pair<Sequence<T> **, int> result = {result_ptr, result_size};
        return result;
    }

    template <typename T>
    void ArraySequence<T>::Resize(int new_size){
        this->Resize(new_size, T());
    }

    template <typename T>
    void ArraySequence<T>::Resize(int new_size, const T &item) {
        if(new_size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        if(new_size == 0) {
            this->Clear();
        } else if(new_size < this->size) {
            this->size = new_size;
            AutoShrink();
        } else if(new_size > this->size) {
            this->Reserve(2 * new_size);
            for(int i = this->size; i != new_size; ++i) {
                this->ker->Set(i, item);
            }
            this->size = new_size;
        }
    }

    template <typename T>
    void ArraySequence<T>::Reserve(int new_size) {
        if(new_size < 0) {
            throw std::invalid_argument("Invalid size!");
        }
        if(new_size > this->GetCapacity()) {
            this->ker->Realloc(new_size);
        }
    }
} // lab2