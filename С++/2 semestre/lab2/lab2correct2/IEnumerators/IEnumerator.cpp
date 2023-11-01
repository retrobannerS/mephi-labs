#include "../Sequences/Sequence.hpp"
#include "IEnumerator.hpp"

namespace lab2 {

    template <typename T>
    IEnumerator<T>::IEnumerator(Sequence<T> *sequence, int index) : sequence(sequence), index(index) {
        if(index < 0 or index > sequence->GetSize())
            throw std::out_of_range("Index out of range!");
    }

    template <typename T>
    bool IEnumerator<T>::move_next() {
        if(this->index < this->sequence->GetSize())
            this->index++;
        return this->index < this->sequence->GetSize();
    }

    template <typename T>
    T &IEnumerator<T>::current() const {
        return this->sequence->operator [](index);
    }

    template <typename T>
    void IEnumerator<T>::reset() {
        this->index = 0;
    }

    template <typename T>
    IEnumerator<T> &IEnumerator<T>::operator ++() {
        this->move_next();
        return *this;
    }

    template <typename T>
    bool IEnumerator<T>::operator !=(const IEnumerator<T> &other) const {
        return !(this->index == other.index and this->sequence == other.sequence);
    }

    template <typename T>
    T &IEnumerator<T>::operator *() const {
        return this->current();
    }

} // lab2