/* Logging of games and game events. */

#include "log.h"

#include "linked_list.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* PRIVATE INTERFACE */


/* Represents a player's turn in the game. */
typedef struct
{
    unsigned long turnNum;      /* Turn number in the game, starts at 1. */
    Player player;              /* Player whose turn it was. */
    unsigned row;               /* Row the player placed a tile on. */
    unsigned column;            /* Column the player placed a tile on. */
} PlayerTurn;


/* Contains the log data for a single game. */
typedef struct
{
    unsigned long gameNum;   /* Game number since program start, starts at 1. */
    LinkedList turns;        /* List of PlayerTurn instances. */
} GameLog;


/* Creates a PlayerTurn instance from the given data.
   The returned object is dynamically allocated and must be freed. */
static PlayerTurn* createPlayerTurn(Player player, unsigned turnNum,
    unsigned row, unsigned column)
{
    PlayerTurn* turn = (PlayerTurn*)malloc(sizeof(PlayerTurn));

    turn->player = player;
    turn->turnNum = turnNum;
    turn->row = row;
    turn->column = column;

    return turn;
}


/* Creates a new, empty game log.
   The returned object is dynamically allocated and must be freed. */
static GameLog* createGameLog(unsigned long gameNum)
{
    GameLog* gameLog = (GameLog*)malloc(sizeof(GameLog));

    gameLog->gameNum = gameNum;
    gameLog->turns = createLinkedList();

    return gameLog;
}


/* Destroys/frees a GameLog and sets the pointer to it to NULL. */
static void destroyGameLog(GameLog** gameLog)
{
    listFreeAndRemoveAll(&(*gameLog)->turns);
    *gameLog = NULL;
}


/* Logs a player's turn to the given game log. */
static void logTurnTo(GameLog* gameLog, Player player, unsigned row,
    unsigned column)
{
    unsigned long turnNum = gameLog->turns.size + 1ul;
    PlayerTurn* turn = createPlayerTurn(player, turnNum, row, column);
    listInsertLast(&gameLog->turns, turn);
}


/* Returns 'X' for PLAYER_X, 'O' for PLAYER_O. */
static char playerToChar(Player player)
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


/* Returns a pointer to the LinkedList of GameLog instances used to store the
   game logs.*/
static LinkedList* getGameLogs(void)
{
    static LinkedList gameLogs = EMPTY_LINKED_LIST;
    return &gameLogs;
}


/* List iteration callback for freeGameLogs() to destroy a game log. */
static void freeGameLogCallback(void** data, void* callbackData)
{
    GameLog* gameLog = *data;
    *data = NULL;
    destroyGameLog(&gameLog);
}


/* List iteration callback for writeGameLogCallback() to write a PlayerTurn to a
   stream. */
static void writePlayerTurnCallback(void** data, void* stream)
{
    PlayerTurn const* turn = *data;

    fprintf(stream, "  Turn %lu:\n", turn->turnNum);
    fprintf(stream, "    Player: %c\n", playerToChar(turn->player));
    fprintf(stream, "    Location: %u, %u\n", turn->column, turn->row);
    fprintf(stream, "\n");
}


/* List iteration callback for writeGameLogs() to write a GameLog to a stream.
   */
static void writeGameLogCallback(void** data, void* stream)
{
    GameLog const* gameLog = *data;

    fprintf(stream, "GAME %lu:\n", gameLog->gameNum);
    listIterateForward(&gameLog->turns, writePlayerTurnCallback, stream);
    fprintf(stream, "\n");
}



/* PUBLIC INTERFACE */


void newGameLog(void)
{
    unsigned long gameNum = getGameLogs()->size + 1ul;
    GameLog* gameLog = createGameLog(gameNum);
    listInsertLast(getGameLogs(), gameLog);
}


void freeGameLogs(void)
{
    listIterateReverse(getGameLogs(), freeGameLogCallback, NULL);
    listRemoveAll(getGameLogs());
}


void logTurn(Player player, unsigned row, unsigned column)
{
    GameLog* currentLog = getGameLogs()->tail->data;
    assert(currentLog);
    logTurnTo(currentLog, player, row, column);
}


void writeGameLogs(FILE* stream)
{
    listIterateForward(getGameLogs(), writeGameLogCallback, stream);
}
