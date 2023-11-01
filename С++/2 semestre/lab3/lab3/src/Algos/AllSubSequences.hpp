#ifndef LAB3_ALLSUBSEQUENCES_HPP
#define LAB3_ALLSUBSEQUENCES_HPP
#include "Sequence.hpp"
#include "ArraySequence.hpp"

using namespace lab2;

namespace lab3 {

    template<typename T>
    Sequence<Sequence<T> *> *AllSubSequences(const Sequence<T> *seq) {
        {
            Sequence<Sequence<T> *> *result = new ArraySequence<Sequence<T> *>;
            for (int i = 0; i != seq->GetSize(); ++i) {
                for (int j = i; j != seq->GetSize(); ++j) {
                    Sequence<T> *subSeq = new ArraySequence<T>;
                    for (int k = i; k <= j; ++k) {
                        subSeq->PushBack(seq->Get(k));
                    }
                    result->PushBack(subSeq);
                }
            }
            return result;
        }
    }

} //lab3

#endif //LAB3_ALLSUBSEQUENCES_HPP
