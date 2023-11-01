#include "ArraySequence.hpp"
#include <utility>

using namespace lab2;

namespace lab3 {

    ArraySequence<std::pair<int, int>> factorize(int n) {
        ArraySequence<std::pair<int, int>> factors;
        for (int i = 2; i * i <= n; ++i) {
            if (n % i) {
                continue;
            }
            int count = 0;
            while (n % i == 0) {
                n /= i;
                ++count;
            }
            factors.PushBack(std::make_pair(i, count));
        }
        if (n > 1) {
            factors.PushBack(std::make_pair(n, 1));
        }
        return factors;
    }

    bool isPrime(int n) {
        if (n <= 1) {
            return false;
        }
        if (n == 2) {
            return true;
        }
        if (n % 2 == 0) {
            return false;
        }
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    ArraySequence<bool> sieveOfEratosthenes(int n) {
        ArraySequence<bool> sieve(n + 1, true);
        sieve.Set(0, false);
        sieve.Set(1, false);
        for (int p = 2; p * p <= n; p++) {
            if (sieve[p]) {
                for (int i = p * p; i <= n; i += p) {
                    sieve[i] = false;
                }
            }
        }
        return sieve;
    }

} //lab3

