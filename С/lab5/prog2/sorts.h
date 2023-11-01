#ifndef PROG_SORTS_H
#define PROG_SORTS_H

#include "gen.h"

int sorting(int *array, unsigned len, char *sort);

int cmp_(const int *p1, const int *p2);

void gnomes(int *arr, unsigned int len, int (*cmp)(const int *, const int *));
void shell(int *data, unsigned int len, int (*cmp)(const int *, const int *));

#endif //PROG_SORTS_H