/* Miscellaneous program utilities. */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>


/* Concatenates two strings and returns the result as a new string.
   The returned buffer must be freed. */
char* concatString(char const* str1, char const* str2);

/* Reads characters from a file until a given character is encountered.
   Consumes that character from the file stream.
   On success, returns 1.
   On error or EOF, returns 0. */
int readUntil(FILE* file, char c);


#endif
