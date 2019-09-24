#include "util.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void do_main(char** args, size_t num_args);
void do_sum(int const* array, size_t size);
void do_max(int const* array, size_t size);
void do_reverse(int* array, size_t size);


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: main <func> [<int1> [<int2> ...]]\n");
    }
    else
    {
        do_main(argv + 1, argc - 1);
    }

    return 0;
}


void do_main(char** args, size_t num_args)
{
    char const* choice;
    char* choice_upper;
    int num_ints;
    int* ints;

    num_ints = num_args - 1;
    ints = (int*)malloc(num_ints * sizeof(int));
    strings_to_ints(args + 1, ints, num_ints);

    choice = args[0];
    choice_upper = (char*)malloc(strlen(choice) + 1);
    strcpy(choice_upper, choice);
    to_upper(choice_upper);

    if (strcmp(choice_upper, "SUM") == 0)
    {
        do_sum(ints, num_ints);
    }
    else if (strcmp(choice_upper, "MAX") == 0)
    {
        do_max(ints, num_ints);
    }
    else if (strcmp(choice_upper, "REVERSE") == 0)
    {
        do_reverse(ints, num_ints);
    }
    else
    {
        printf("\"%s\" is not a valid option.\n", choice);
    }

    free(choice_upper);
    choice_upper = NULL;

    free(ints);
    ints = NULL;
}


void do_sum(int const* array, size_t size)
{
    int res = sum(array, size);
    printf("Sum: %d\n", res);
}


void do_max(int const* array, size_t size)
{
    int res = max(array, size);
    printf("Index of max: %d\n", res);
}


void do_reverse(int* array, size_t size)
{
    reverse(array, size);
    printf("Reversed: ");
    print(array, size);
    printf("\n");
}
