#ifndef LAB3_PRIMENUMBERS_H
#define LAB3_PRIMENUMBERS_H
#include "ArraySequence.hpp"
#include <utility>

using namespace lab2;

namespace lab3 {

    ArraySequence<std::pair<int, int>> factorize(int n);
    bool isPrime(int n);
    ArraySequence<bool> sieveOfEratosthenes(int n);

}

#endif //LAB3_PRIMENUMBERS_H
