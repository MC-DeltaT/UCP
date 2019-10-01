/* Miscellaneous program utilities. */

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>


/* Identifies game players. */
typedef enum
{
    PLAYER_X,
    PLAYER_O
} Player;


/* Returns 'X' for PLAYER_X, 'O' for PLAYER_O. */
char playerToChar(Player player);


/* Reads characters from a file until a given character is encountered.
   consume controls whether or not that character is consumed from the file.
   On success, returns 1.
   On error or EOF, returns 0. */
int readUntil(FILE* file, char c, int consume);


#endif
