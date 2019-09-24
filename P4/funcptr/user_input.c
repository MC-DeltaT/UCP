#include "user_input.h"

#include <stdio.h>


void readInts(int* int1, int* int2, int* int3, char* c)
{
    printf("Enter an integer: ");
    scanf("%d", int1);
    printf("Enter an integer: ");
    scanf("%d", int2);
    printf("Enter an integer: ");
    scanf("%d", int3);

    printf("Enter a character: ");
    /* Space before %c consumes previous newline. */
    scanf(" %c", c);
}
