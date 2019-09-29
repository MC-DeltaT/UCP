/* Miscellaneous program utilities. */

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* PUBLIC INTERFACE */


char* concatString(char const* str1, char const* str2)
{
    char* result = NULL;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t resLen = len1 + len2 + 1ul;

    result = (char*)malloc(resLen);

    memcpy(result, str1, len1);
    memcpy(result + len1, str2, len2 + 1ul);

    return result;
}


int readUntil(FILE* file, char c, int consume)
{
    int read = '\0';

    do {
        read = fgetc(file);
    } while(read != c && read != EOF);

    if (!consume && read != EOF)
    {
        ungetc(read, file);
    }

    return read != EOF;
}
