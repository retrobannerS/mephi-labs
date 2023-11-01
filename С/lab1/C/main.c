#include <stdio.h>

int sum(int);

int main()
{
    int x;
    printf("Write integer:\n");
    if (scanf("%d", &x) == 1)
        printf("%d", sum(x));
    else
        printf("Error. You haven`t write integer\n");
    return 0;
}

int sum (int x)
{
    int res = 0;
    while (x)
    {
        res += x % 10;
        x /= 10;
    }
    return res;
}


