#ifndef LAB3_HANOI_H
#define LAB3_HANOI_H
#include "Collections/Stack.hpp"

namespace lab3 {

    void hanoi(int n, Stack<int> &from, Stack<int> &to, Stack<int> &aux);
    void hanoi2(int n, char from, char to, char aux);

} //lab3


#endif //LAB3_HANOI_H
