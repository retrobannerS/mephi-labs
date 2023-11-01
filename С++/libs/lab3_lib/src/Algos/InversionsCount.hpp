#ifndef LAB3_INVERSIONSCOUNT_HPP
#define LAB3_INVERSIONSCOUNT_HPP
#include "Sequence.hpp"

using namespace lab2;


namespace lab3 {

    template<typename T>
    int InversionsCount(const lab2::Sequence<T> *seq) {
        int count = 0;
        for (int i = 0; i != seq->GetSize(); ++i) {
            for (int j = i + 1; j != seq->GetSize(); ++j) {
                if (seq->Get(i) > seq->Get(j)) {
                    ++count;
                }
            }
        }
        return count;
    }

} //lab3

#endif //LAB3_INVERSIONSCOUNT_HPP
