#ifndef PROG2_MYSTRING_H
#define PROG2_MYSTRING_H

#include <stddef.h>

size_t mystrlen(const char*);
char *mystrcat(char*, const char*);
char *mystrdup(const char*);
char *mystrtok(char*, const char*);
size_t mystrcspn (const char *str, const char *srch);

#endif //PROG2_MYSTRING_H
