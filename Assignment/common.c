/* Miscellaneous program utilities. */

#include "common.h"

#include <assert.h>
#include <stdio.h>


/* PUBLIC INTERFACE */


char playerToChar(Player player)
{
    char res = '\0';

    switch (player)
    {
        case PLAYER_X: res = 'X'; break;
        case PLAYER_O: res = 'O'; break;
        default: assert(0);
    }

    return res;
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
