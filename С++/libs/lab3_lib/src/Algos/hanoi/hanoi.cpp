#include "Collections/Stack.hpp"
#include "hanoi.h"
#include <thread>
#include <chrono>

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

    void hanoi2(int n, char from, char to, char aux) {
        if (n == 1) {
            std::cout << "Move disk 1 from rod " << from << " to rod " << to << std::endl;
            return;
        }
        hanoi2(n - 1, from, aux, to);
        std::cout << "Move disk " << n << " from rod " << from << " to rod " << to << std::endl;
        hanoi2(n - 1, aux, to, from);
    }


} //lab3