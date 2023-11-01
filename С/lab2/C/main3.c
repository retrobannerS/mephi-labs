#include <stdio.h>
#include <math.h>
int main()
{
    long double x;
    scanf("%Lf", &x);
    int m;
    scanf("%d", &m);
    long double q = (-1) * (x*x*x) / 6, sum = x;
    for (int i = 2; i <= m; i++)
    {
        
        sum += q;
        q *= (-1) * (2*i-1) * (x*x) / ((2*i)*(2*i + 1));
    }
    printf("%Lf", sum);
}
