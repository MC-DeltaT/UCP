#include <stdio.h>


int nearestEven(int x)
{
    return x & ~1;
}


int nearestOdd(int x)
{
    return x | 1;
}



int main(void)
{
    printf("Nearest even number to %d is %d\n", 10, nearestEven(10));
    printf("Nearest even number to %d is %d\n", 11, nearestEven(11));

    printf("Nearest odd number to %d is %d\n", 10, nearestOdd(10));
    printf("Nearest odd number to %d is %d\n", 11, nearestOdd(11));

    return 0;
}
