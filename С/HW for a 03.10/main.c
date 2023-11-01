#include <stdio.h>
#include <math.h>

long double radians(long double);
long double computer_sin(long double);
long double teylor_sin(long double, int);

int main()
{
    int n = 0;
    long  double x = 0.0f;

    printf("Write number x (degrees):");
    while (scanf("%Lf", &x) != 1)
    {
        if (getchar() == -1)
            printf("EOF or error");
        else{
            printf("Error. You haven`t written number. Try again:");
            fflush(stdin);
        }
    }
    fflush(stdin);

    printf("Write integer - number of iterations:");
    while (scanf("%d", &n) != 1)
    {
        if(getchar() == -1)
            printf("EOF or error");
        else
        {
            printf("Error. You haven`t written integer. Try again:");
            fflush(stdin);
        }
    }
    x = radians(x);
    n *= -1;
    n = powl(10.0f, n);
    printf("Integrated function have counted sinus\nlike this: %.2Lf\n", computer_sin(x));
    printf("Teylor function have counted sinus\nlike this: %.2Lf\n", teylor_sin(x, n));
    return 0;
}

long double radians(long double x)
{
    return (x/180) * M_PI;
}

long double computer_sin(long double x)
{
    return sinl(x);
}

long double teylor_sin(long double x, int n)
{
    long double q = x, s = 0.0f, prevq = 0.0;
    int i = 1;
    while (fabsl(prevq - q) > n)
    {
        s += q;
        prevq = q;
        q = q * (-1) * x * x / ((2 * i) * ((2 * i) + 1));
        i++;
    }


    return s;
}