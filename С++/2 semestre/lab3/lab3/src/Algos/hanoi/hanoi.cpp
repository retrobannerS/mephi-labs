#include "Collections/Stack.hpp"
#include "hanoi.h"

namespace lab3 {

    void hanoi(int n, Stack<int> &from, Stack<int> &to, Stack<int> &aux) {
        if (n == 1) {
            to.push(from.pop());
        } else {
            hanoi(n - 1, from, aux, to);
            to.push(from.pop());
            hanoi(n - 1, aux, to, from);
        }
    }

} //lab3