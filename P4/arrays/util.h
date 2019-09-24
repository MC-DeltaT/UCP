#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>


int sum(int const* array, size_t size);

int max(int const* array, size_t size);

void reverse(int* array, size_t size);

void print(int const* array, size_t size);

void strings_to_ints(char** strings, int* ints, size_t size);

void to_upper(char* string);

#endif
