#ifndef LAB3_CHECKING_H
#define LAB3_CHECKING_H

#define N 5                 //Только >= 1 (целые числа)!

#include <stdbool.h>
#include <stdio.h>
#include "iso646.h"
#include <stdlib.h>
#include <string.h>

bool str_check(char*, bool);
bool choosing_arr(long double**, unsigned int*, unsigned int*, long double**, unsigned int*, unsigned int*, long double**, unsigned int*, unsigned int*);
long double input_elem();
unsigned int input_int();
long double *allocating(long double*, const unsigned int*, unsigned int*);

#endif //LAB3_CHECKING_H