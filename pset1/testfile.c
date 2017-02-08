#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float num = 3.8;
    printf("%f\n", num);
    printf("%f\n", num);
    num = roundf(num * 100) / 100;
    num = ceilf(num * 100) / 100;
    printf("%f\n", num);
    printf("%.2f", num);
    double d = num;
    d = round(d * 100.0)/100.0;
    printf("%f\n", d);
}