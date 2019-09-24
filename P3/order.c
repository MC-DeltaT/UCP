#include "order.h"


void ascending2(int* a, int* b)
{
    if (*a > *b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}


void ascending3(int* a, int* b, int* c)
{
    /* Bubble sort. */
    ascending2(a, b);
    ascending2(b, c);
    ascending2(a, b);
}


void descending2(int* a, int* b)
{
    if (*a < *b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}


void descending3(int* a, int* b, int* c)
{
    /* Bubble sort. */
    descending2(a, b);
    descending2(b, c);
    descending2(a, b);
}
