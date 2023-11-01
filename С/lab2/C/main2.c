#include <stdio.h>
#include <iso646.h>
#include <math.h>

long double input_x(long double);
int input_prec(int);
long double teylors_row(long double, int);
long double ten_powl(int);

int main()
{
    long double x = 0.0;
    int prec = 5;

    x = input_x(x);
    prec = input_prec(prec);

    printf("\nCalculated value - %.*Lf\n", prec, teylors_row(x, prec));

    return 0;
}

long double input_x (long double x)
{
    printf("\nWrite number x in the range from -1 to 1 (except -1 and 1):");
    while(scanf("%Lf", &x) != 1 or fabsl(x) >= 1)
    {
        if (fabsl(x) >= 1)
        {
            printf("\nYou haven`t written number in range from -1 to 1"
                          "(except -1 and 1). Try again:");
            x = 0.0;
        }
        else if (getchar() == -1)
            printf("\n\nError or EOF\n");
        else
            printf("\nYou haven`t written number. Try again:");

        while(getchar() != '\n');
    }

    return x;
}

int input_prec(int prec)
{
    char check;

    printf("\nWrite integer precision (number of decimal places):");
    while ((scanf("%d%c", &prec, &check) != 2) or (check != 10))
    {
        if (check == -1)
            printf("\n\nError or EOF.\n");
        else
            printf("\nYou haven`t written integer. Try again:");

        while(getchar() != '\n');
    }

    return prec;
}

long double teylors_row(long double x, int prec)
{
    int i = 2, count = 0;
    long double q = 1.0, num_with_prec = ten_powl(prec), sum = 0.0;

    while (q >= num_with_prec)
    {
        sum += q;
        q *= (x*x)*(i+1)/(i);
        i += 2;
        count += 1;
    }

    printf("\nNumber of row members - %d\n", count);

    return sum;
}

long double ten_powl(int prec) /*Example: pres = 3 -> num_with_pres = 0.0001 to better
 *                              precision*/
{
    long double num_with_prec = 1;
    for (int i = 1; i <= (prec + 1); i++)
        num_with_prec /= 10;

    return num_with_prec;
}