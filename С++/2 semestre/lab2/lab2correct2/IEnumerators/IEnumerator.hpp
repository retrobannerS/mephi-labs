#ifndef LAB2CORRECT2_IENUMERATOR_HPP
#define LAB2CORRECT2_IENUMERATOR_HPP
#include "../Sequences/Sequence.hpp"


namespace lab2 {
    template <typename T>
    class IEnumerator {
    private:
        Sequence<T>* sequence;
        int index;
    public:
        IEnumerator(Sequence<T> *sequence, int index);

        bool move_next();
        T& current() const;
        void reset();

        IEnumerator <T> & operator ++();
        bool operator !=(const IEnumerator<T> &other) const;
        T& operator *() const;
    };
} // lab2

#include "IEnumerator.cpp"
#endif //LAB2CORRECT2_IENUMERATOR_HPP
