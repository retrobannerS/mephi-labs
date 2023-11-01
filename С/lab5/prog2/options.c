#include "options.h"
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void help()
{
    printf("\nOPTIONS:\n");
    printf("-h prints this message again.\n");
    printf("-s changes sorting algorithm to Gnome sort (\"gnomes\" argument) "
           "or Shell sort (\"shell\" argument).\nQuick Sort is used as default.\n");
}

void err_usage()
{
    fprintf(stderr, "Programme requires two arguments: number of arrays and of elements.\nUse -h to read all options.\n");
}

short int options(int argc, char *argv[], char **sort, unsigned *num1, unsigned *num2)
{
    int c;
    while ((c = getopt (argc, argv, "hs:")) != -1)
        switch (c)
        {
            case 'h':
                help();
                return 0;
            case 's':
                *sort = optarg;
                break;
            case '?':
                if (optopt != 's')
                {
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                    return 1;
                }
            default:
                fprintf(stderr ,"Unknown error\n");
                return 1;
        }
    if (optind <= argc - 2)
    {
        *num1 = atoi(argv[optind++]);
        *num2 = atoi(argv[optind++]);
        if (*num1 == 0 || *num2 == 0)
        {
            printf("Invalid required parametrs\n");
            return 1;
        }
    }
    else
    {
        err_usage();
        return 1;
    }

    while (optind < argc)
        printf ("Excess argument %s\n", argv[optind++]);

    return 0;
}