/* Logging of games and game events. */

#ifndef LOG_H
#define LOG_H

#include <stdio.h>


/* Note on implementation:
    All the game logs are stored internally in this module, i.e. the module is
    stateful. Functions give purposely limited access to them. This is in order
    to simplify the logging process. */


/* Identifies game players. */
typedef enum
{
    PLAYER_X,
    PLAYER_O
} Player;


/* Creates a new, empty game log and sets it as the current game log. */
void newGameLog(void);

/* Removes and frees the internally stored game logs.
   Must be called before the end of the program otherwise there will be a memory
   leak. */
void freeGameLogs(void);

/* Logs a player's turn to the current game log. */
void logTurn(Player player, unsigned row, unsigned column);

/* Writes the games logs in textual form to the given stream. */
void writeGameLogs(FILE* stream);


#endif
