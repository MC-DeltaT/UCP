#include <stdio.h>


unsigned long powersOf2(void);


int main()
{
    unsigned i = 0;
    for (i = 0; i < 16; ++i)
    {
        printf("%ld\n", powersOf2());
    }

    return 0;
}


unsigned long powersOf2(void)
{
    static unsigned long n = 1;
    n *= 2;
    return n;
}
