/* Game board and mechanics. */

#include "board.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* PRIVATE INTERFACE */


/* Checks if the given status occurs consecutively enough across the given row
   to be a win. */
static int hasWonRow(GameBoard const* board, unsigned row,
                     CellStatus status)
{
    unsigned consecutive = 0;
    unsigned j = 0;

    while(j < board->columns && consecutive < board->winRequirement)
    {
        if (getCell(board, row, j) == status)
        {
            ++consecutive;
        }
        else
        {
            consecutive = 0;
        }

        ++j;
    }

    return consecutive >= board->winRequirement;
}


/* Checks if the given status occurs consecutively enough across the given
   column to be a win. */
static int hasWonColumn(GameBoard const* board, unsigned column,
                        CellStatus status)
{
    unsigned consecutive = 0;
    unsigned i = 0;

    while(i < board->rows && consecutive < board->winRequirement)
    {
        if (getCell(board, i, column) == status)
        {
            ++consecutive;
        }
        else
        {
            consecutive = 0;
        }

        ++i;
    }

    return consecutive >= board->winRequirement;
}


/* Checks if the given status occurs consecutively enough across the given
   rising diagonal to be a win.
   Diagramatic explanation:
     Grid:          Path checked:
       a b c        a: diagonal = 0
       b c d        b: diagonal = 1
       c d e        c: diagonal = 2
       d e f        d: diagonal = 3
                    e: diagonal = 4
                    f: diagonal = 5 */
static int hasWonRisingDiagonal(GameBoard const* board, unsigned diagonal,
                                CellStatus status)
{
    /* TODO */
    return 0;
}


/* Checks if the given status occurs consecutively enough across the given
   falling diagonal to be a win.
   Diagramatic explanation:
     Grid:          Path checked:
       c b a        a: diagonal = 0
       d c b        b: diagonal = 1
       e d c        c: diagonal = 2
       f e d        d: diagonal = 3
                    e: diagonal = 4
                    f: diagonal = 5 */
static int hasWonFallingDiagonal(GameBoard const* board, unsigned diagonal,
                                CellStatus status)
{
    /*unsigned consecutive = 0;
    unsigned i;
    unsigned j;

    assert(diagonal + 1u < board->rows + board->columns);
    i = board->rows - diagonal - 1u;

    return consecutive >= board->winRequirement;*/

    /* TODO */

    return 0;
}


/* Checks if X or O has won on the given board.
   status should be either CELL_X or CELL_O
   (but technically you could check if CELL_EMPTY has won :p ). */
static int hasWon(GameBoard const* board, CellStatus status)
{
    unsigned i = 0;
    int win = 0;


    /* Check for a win across a row. */
    i = 0;
    while (i < board->rows && !win)
    {
        win = hasWonRow(board, i, status);
        ++i;
    }

    /* Check for a win across a column. */
    i = 0;
    while (i < board->columns && !win)
    {
        win = hasWonColumn(board, i, status);
        ++i;
    }

    /* Check for a win across a rising diagonal.*/
    i = 0;
    while (i < board->columns + board->rows - 1u && !win)
    {
        win = hasWonRisingDiagonal(board, i, status);
    }

    /* Check for a win across a falling diagonal. */
    i = 0;
    while (i < board->columns + board->rows - 1u && !win)
    {
        win = hasWonFallingDiagonal(board, i, status);
    }

    return win;
}



/* PUBLIC INTERFACE */


GameBoard zeroedGameBoard(void)
{
    GameBoard board;

    board.rows = 0;
    board.columns = 0;
    board.winRequirement = 0;

    return board;
}


GameBoard createGameBoard(unsigned rows, unsigned columns,
                          unsigned winRequirement)
{
    GameBoard board;

    assert(rows > 0);
    assert(columns > 0);
    assert(winRequirement > 0);

    board.cells = malloc(rows * columns * sizeof(CellStatus));
    board.rows = rows;
    board.columns = columns;
    board.winRequirement = winRequirement;

    clearCells(&board);

    return board;
}


void destroyGameBoard(GameBoard* board)
{
    board->rows = 0;
    board->columns = 0;
    board->winRequirement = 0;
    free(board->cells);
    board->cells = NULL;
}


void clearCells(GameBoard* board)
{
    unsigned i = 0;
    unsigned j = 0;

    for (i = 0; i < board->rows; ++i)
    {
        for (j = 0; j < board->columns; ++j)
        {
            setCell(board, i, j, CELL_EMPTY);
        }
    }
}


int hasXWon(GameBoard const* board)
{
    return hasWon(board, CELL_X);
}


int hasOWon(GameBoard const* board)
{
    return hasWon(board, CELL_O);
}


int inBoardBounds(GameBoard const* board, unsigned row, unsigned column)
{
    return row < board->rows && column < board->columns;
}


void setCell(GameBoard* board, unsigned row, unsigned column, CellStatus status)
{
    assert(inBoardBounds(board, row, column));

    board->cells[row * board->columns + column] = status;
}


CellStatus getCell(GameBoard const* board, unsigned row, unsigned column)
{
    assert(inBoardBounds(board, row, column));

    return board->cells[row * board->columns + column];
}


void displayGameBoard(GameBoard const* board)
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


CellStatus playerToCell(Player player)
{
    CellStatus status;

    switch(player)
    {
        case PLAYER_X: status = CELL_X; break;
        case PLAYER_O: status = CELL_O; break;
        default: assert(0);
    }

    return status;
}
