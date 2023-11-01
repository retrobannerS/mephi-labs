#ifndef PROG_SORTS_H
#define PROG_SORTS_H

#include "met.h"

int sorting(student *array, unsigned len, char *sort, char *id, unsigned short direction);

int cmp_score(const student *p1, const student *p2);
int cmp_group(const student *p1, const student *p2);
int cmp_name(const student *p1, const student *p2);

int cmp_score_des(const student *p1, const student *p2);
int cmp_group_des(const student *p1, const student *p2);
int cmp_name_des(const student *p1, const student *p2);

void gnomes(student *arr, unsigned int len, int (*cmp)(const student *, const student *));
void shell(student *data, unsigned int len, int (*cmp)(const student *, const student *));

#endif //PROG_SORTS_H