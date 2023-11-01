#include <stdio.h>
#include <iso646.h>
#include <math.h>

long double input_x(long double);
int input_number_of_row_members(int);
long double teylors_row(long double, int);

int main()
{
    long double x = 0.0;
    int number_of_row_members = 10;

    x = input_x(x);
    number_of_row_members = input_number_of_row_members(number_of_row_members);

    printf("\nCalculated value - %.25Lf\n", teylors_row(x, number_of_row_members));

    return 0;
}

long double input_x (long double x)
{
    printf("\nWrite number x in the range from -1 to 1 (except -1 and 1):");
    while(scanf("%Lf", &x) != 1 or fabsl(x) >= 1)
    {
        if (fabsl(x) >= 1)
        {
            printf("\nYou haven`t written number in the range from -1 to 1"
                          " (except -1 and 1).Try again:");
            x = 0.0;
        }
        else                        //as for "if (scanf("%Lf", &x) != 1)"
            if (getchar() == -1)
                 printf("\nError or EOF\n");
            else
                printf("\nYou haven`t written number.Try again:");

        while(getchar() != '\n');
    }

    return x;
}

int input_number_of_row_members(int number_of_row_members)
{
    char check;

    printf("\nWrite integer required number of row members:");
    while ((scanf("%d%c", &number_of_row_members, &check) != 2) or (check != 10))
    {
        if (getchar() == -1)
            printf("\nError or EOF.\n");
        else
            printf("\nYou haven`t written integer. Try again:");

        while (getchar() != '\n');
    }

    return number_of_row_members;
}

long double teylors_row(long double x, int number_of_members)
{
    long double q = 1.0, sum = 0.0;

    for(int i = 2; i/2 <= number_of_members; i += 2)
    {
        sum += q;
        q *= (x*x)*(i+1)/(i);
    }

    return sum;
}
