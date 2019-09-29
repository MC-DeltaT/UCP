/* User interface and associated high-level logic. */

#include "interface.h"

#include "board.h"
#include "settings.h"

#include <assert.h>
#include <stdio.h>


/* PRIVATE INTERFACE */


/* Prints a game board to stdout. */
void displayBoard(GameBoard const* board)
{
    static char const X_CHAR = 'X';
    static char const O_CHAR = 'O';
    static char const EMPTY_CHAR = ' ';

    unsigned const horizontalDividerWidth = board->columns * 4 + 1;
    unsigned i = 0;
    unsigned j = 0;
    char cell;

    /* Top border. */
    for (i = 0; i < horizontalDividerWidth; ++i)
    {
        printf("-");
    }
    printf("\n");

    /* Board body. */
    for (i = 0; i < board->rows; ++i)
    {
        printf("|");
        for (j = 0; j < board->columns; ++j)
        {
            switch (getCell(board, i, j))
            {
                case CELL_X:
                    cell = X_CHAR;
                    break;
                case CELL_O:
                    cell = O_CHAR;
                    break;
                case CELL_EMPTY:
                    cell = EMPTY_CHAR;
                    break;
                default:
                    assert(0);
            }
            printf(" %c |", cell);
        }
        printf("\n");

        for (j = 0; j < horizontalDividerWidth; ++j)
        {
            printf("-");
        }
        printf("\n");
    }
}


void runGame(Settings const* settings)
{
    GameBoard board = createGameBoard(settings->boardRows,
            settings->boardColumns, settings->winRequirement);
    int xWon = 0;
    int oWon = 0;
    unsigned long placed = 0;
    unsigned long const cells = board->rows * board->columns;

    while (placed < cells && !xWon && !oWon)
    {
        playerTurnX(&board);
        ++placed;
        displayBoard();
        xWon = hasXWon(&board);
        if (!xWon)
        {
            playerTurnO(&board);
            ++placed;
            displayBoard();
            oWon = hasOWon(&board);
        }
    }

    printf("Game complete.\n");
    if (xWon)
    {
        printf("Player X has won!\n");
    }
    else if (oWon)
    {
        printf("Player O has won!\n");
    }
    else
    {
        printf("Draw.\n");
    }
}


void displaySettings(Settings const* settings)
{
    printf("Board rows: %u\n", settings->boardRows);
    printf("Board columns: %u\n", settings->boardColumns);
    printf("Consecutive tokens to win: %u\n", settings->winRequirement);
}


/* Displays the given log to the user. */
void displayLog(GameLog const* log);


/* Saves the given log to a user-provided location. */
void saveLog(GameLog const* log);



/* PUBLIC INTERFACE */


void mainMenu();
