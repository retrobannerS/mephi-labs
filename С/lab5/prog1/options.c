#include "options.h"
#include <stdio.h>
#include <getopt.h>

void help()
{
    printf("\nOPTIONS:\n");
    printf("-h prints this message again.\n");
    printf("-s changes sorting algorithm to Gnome sort (\"gnomes\" argument) "
           "or Shell sort (\"shell\" argument).\nQuick Sort is used as default.\n");
    printf("-p changes sort field to by name (\"name\" argument), by group(\"group\" argument)."
           "\nBy average score is used as default.\n");
    printf("-d changes sorting direction to descending.\nAscending order is used as default.\n\n");
}

void err_usage()
{
    fprintf(stderr, "Programme requires two arguments: input and output files. Use -h to read all options.\n");
}

short int options(int argc, char *argv[], char **sort, char **id,
                  char **in_file, char **out_file, unsigned short int *direction)
{
    int c;
    while ((c = getopt (argc, argv, "hs:p:d")) != -1)
        switch (c)
        {
            case 'h':
                help();
                return 0;
            case 's':
                *sort = optarg;
                break;
            case 'p':
                *id = optarg;
                break;
            case 'd':
                *direction = -1;
                break;
            case '?':
                if (optopt != 's' && optopt != 'p')
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
        *in_file = argv[optind++];
        *out_file = argv[optind++];
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