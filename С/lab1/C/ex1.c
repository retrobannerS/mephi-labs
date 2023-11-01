#include <stdio.h>
#include <math.h>

int multiplication(int x);

int main()
{
    int x;
    printf("Write integer(except 0):\n");

    if (scanf("%d", &x) == 1)
        {
        if (x == 0)
            printf("Error. You`ve written 0");
        else
            printf("%d", multiplication(x));
        }
    else
        printf("Error. You haven`t write integer\n");

    return 0;
}

int multiplication(int x)
{
    int res = 1, k;
    while(x != 0)
    {
        k = (x % 10 == 0)? 1:abs(x % 10);
        res *= k;
        x /= 10;
    }
    return res;
}