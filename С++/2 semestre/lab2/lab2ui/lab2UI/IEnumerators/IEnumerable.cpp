#include "IEnumerable.hpp"

namespace lab2 {
    template <typename T>
    IEnumerable<T>::IEnumerable(Sequence<T> *sequence) {
        this->sequence = new ArraySequence<T>(sequence);
    }

    template <typename T>
    IEnumerable<T>::~IEnumerable() {
        delete this->sequence;
    }

    template <typename T>
    IEnumerator<T> IEnumerable<T>::begin() const {
        return IEnumerator<T>(this->sequence, 0);
    }

    template <typename T>
    IEnumerator<T> IEnumerable<T>::end() const {
        return IEnumerator<T>(this->sequence, this->sequence->GetSize());
    }
}
