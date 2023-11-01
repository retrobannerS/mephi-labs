#ifndef PROG_OPTIONS_H
#define PROG_OPTIONS_H

void help();
void err_usage();
short int options(int argc, char *argv[], char **sort, char **id,
                  char **in_file, char **out_file, unsigned short int *direction);

#endif //PROG_OPTIONS_H