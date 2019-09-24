#include "order.h"
#include "user_input.h"

#include <stdio.h>


int main(void)
{
    int int1;
    int int2;
    int int3;
    char c;

    readInts(&int1, &int2, &int3, &c);

    ascending3(&int1, &int2, &int3);

    printf("%d %d %d\n", int1, int2, int3);

    return 0;
}
