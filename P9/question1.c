#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void* randomElement(void** array, size_t size)
{
    return array[rand() % size];
}



int main(void)
{
    int nums[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    void* ptrs[10];
    size_t i;

    for (i = 0; i < 10; ++i)
    {
        ptrs[i] = nums + i;
    }

    srand(time(NULL));

    printf("%d\n", *(int*)randomElement(ptrs, 10));

    return 0;
}
