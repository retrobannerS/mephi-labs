#ifndef PROG_MET_H
#define PROG_MET_H

typedef struct
{
    char *FIO;
    char group[8];
    double score;
} student;

int data_reading(char *in_file, student **data, unsigned *len);
int data_writing(char *out_file, student *data, unsigned len);

#endif //PROG_MET_H