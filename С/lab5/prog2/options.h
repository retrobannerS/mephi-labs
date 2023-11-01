#ifndef PROG_OPTIONS_H
#define PROG_OPTIONS_H

void help();
void err_usage();
short int options(int argc, char *argv[], char **sort, unsigned *num1, unsigned *num2);

#endif //PROG_OPTIONS_H