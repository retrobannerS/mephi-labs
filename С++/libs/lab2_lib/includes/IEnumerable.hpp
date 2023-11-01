#ifndef LAB2CORRECT2_IENUMERABLE_HPP
#define LAB2CORRECT2_IENUMERABLE_HPP
#include "Sequence.hpp"
#include "ListSequence.hpp"
#include "IEnumerator.hpp"

namespace lab2 {
    template <typename T>
    class IEnumerable {
    protected:
        Sequence<T>* sequence;
        IEnumerable();
    public:
        explicit IEnumerable(Sequence<T> *sequence);
        virtual ~IEnumerable();

        IEnumerator<T> begin() const;
        IEnumerator<T> end() const;
    };

    template<typename T>
    IEnumerable<T>::IEnumerable() = default;

    template <typename T>
    IEnumerable<T>::IEnumerable(Sequence<T> *sequence) : sequence(new ListSequence<T>(sequence)) {}

    template <typename T>
    IEnumerable<T>::~IEnumerable() {
        delete sequence;
    }

    template <typename T>
    IEnumerator<T> IEnumerable<T>::begin() const {
        return IEnumerator<T>(sequence, 0);
    }

    template <typename T>
    IEnumerator<T> IEnumerable<T>::end() const {
        return IEnumerator<T>(sequence, sequence->GetSize());
    }

} // lab2
#endif //LAB2CORRECT2_IENUMERABLE_HPP
