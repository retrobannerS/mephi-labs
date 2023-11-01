#ifndef LAB2CORRECT2_IENUMERABLE_HPP
#define LAB2CORRECT2_IENUMERABLE_HPP
#include "../Sequences/Sequence.hpp"
#include "IEnumerator.hpp"

namespace lab2 {
    template <typename T>
    class IEnumerable {
    private:
        Sequence<T>* sequence;
    public:
        explicit IEnumerable(Sequence<T> *sequence);
        ~IEnumerable();

        IEnumerator<T> begin() const;
        IEnumerator<T> end() const;
    };

} // lab2

#include "IEnumerable.cpp"
#endif //LAB2CORRECT2_IENUMERABLE_HPP
