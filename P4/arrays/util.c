#include "util.h"

#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


int sum(int const* array, size_t size)
{
    int res = 0;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        res += array[i];
    }
    return res;
}


int max(int const* array, size_t size)
{
    int max_val = INT_MIN;
    int max_idx = 0;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        if (array[i] > max_val)
        {
            max_idx = i;
            max_val = array[i];
        }
    }
    return max_idx;
}


void reverse(int* array, size_t size)
{
    int tmp;
    size_t i;
    for (i = 0; i < size / 2; ++i)
    {
        tmp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = tmp;
    }
}


void print(int const* array, size_t size)
{
    size_t i;
    printf("{");
    for (i = 0; i < size; ++i)
    {
        printf("%d", array[i]);
        if (i < size - 1)
        {
            printf(", ");
        }
    }
    printf("}");
}


void strings_to_ints(char** strings, int* ints, size_t size)
{
    size_t i;
    for (i = 0; i < size; ++i)
    {
        ints[i] = atoi(strings[i]);
    }
}


void to_upper(char* string)
{
    char* p = string;
    while (*p)
    {
        *p = toupper(*p);
        ++p;
    }
}
