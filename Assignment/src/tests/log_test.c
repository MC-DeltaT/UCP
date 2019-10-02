/* Unit tests for the log module. */

#include "log_test.h"

#include "common.h"
#include "../main/log.h"

#include <stdio.h>


/* PUBLIC INTERFACE */


void logTest(void)
{
    moduleTestHeader("log");

    printf("Empty logs:\n");
    writeGameLogs(stdout);
    printf("\n");

    printf("1 log:\n");
    newGameLog();
    logTurn(PLAYER_X, 0, 0);
    logTurn(PLAYER_O, 1, 2);
    logTurn(PLAYER_X, 3, 40);
    logTurn(PLAYER_O, 50, 60);
    writeGameLogs(stdout);
    printf("\n");

    printf("Multiple logs:\n");
    newGameLog();
    logTurn(PLAYER_X, 0, 0);
    newGameLog();
    logTurn(PLAYER_X, 7, 34);
    logTurn(PLAYER_O, 2, 6);
    logTurn(PLAYER_X, 21, 40);
    logTurn(PLAYER_O, 86, 40);
    newGameLog();
    logTurn(PLAYER_O, 1, 2);
    logTurn(PLAYER_X, 3, 40);
    logTurn(PLAYER_O, 50, 60);
    logTurn(PLAYER_X, 3, 40);
    writeGameLogs(stdout);
    printf("\n");

    freeGameLogs();
}
