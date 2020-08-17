#include "math.h"

int main()
{
    int a = 100;
    int b = 20;
    printf("%d + %d = %d\n",a, b, Add(a, b));
    printf("%d + %d = %d\n",a, b, Sub(a, b));
    printf("%d + %d = %d\n",a, b, Mul(a, b));
    printf("%d + %d = %d\n",a, b, Dev(a, b));
    return 0;
}

