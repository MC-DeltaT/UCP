/* Game board and mechanics. */

#include "board.h"

#include "common.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* PRIVATE INTERFACE */


/* Checks if the given status occurs consecutively enough along any row to be a
   win. */
static int hasWonRow(GameBoard const* board, CellStatus status)
{
    int win = 0;
    unsigned consecutive = 0;
    unsigned i = 0;
    unsigned j = 0;

    while (i < board->rows && !win)
    {
        consecutive = 0;
        j = 0;
        while (j < board->columns && consecutive < board->winRequirement)
        {
            if (getBoardCell(board, i, j) == status)
            {
                ++consecutive;
            }
            else
            {
                consecutive = 0;
            }
            ++j;
        }
        ++i;
        win = consecutive >= board->winRequirement;
    }

    return win;
}


/* Checks if the given status occurs consecutively enough along any column to
   be a win. */
static int hasWonColumn(GameBoard const* board, CellStatus status)
{
    int win = 0;
    unsigned consecutive = 0;
    unsigned i = 0;
    unsigned j = 0;

    while (j < board->columns && !win)
    {
        consecutive = 0;
        i = 0;
        while (i < board->rows && consecutive < board->winRequirement)
        {
            if (getBoardCell(board, i, j) == status)
            {
                ++consecutive;
            }
            else
            {
                consecutive = 0;
            }
            ++i;
        }
        ++j;
        win = consecutive >= board->winRequirement;
    }

    return win;
}


/* Checks if the given status occurs consecutively enough along any rising
   diagonal to be a win.
   A falling diagonal is one that goes from the bottom of the board to the top
   and it goes from left to right. */
static int hasWonRisingDiagonal(GameBoard const* board, CellStatus status)
{
    int win = 0;
    unsigned consecutive = 0;
    unsigned long diagonal = 0;
    long i = 0;
    unsigned j = 0;
    unsigned long const numDiagonals = board->rows - 1ul + board->columns;

    while (diagonal < numDiagonals && !win)
    {
        /* Start at bottom left of diagonal, either on first row or last column. */
        if (diagonal < board->rows)
        {
            i = diagonal;
            j = 0;
        }
        else
        {
            i = board->rows - 1u;
            j = diagonal + 1u - board->rows;
        }

        /* Scan up to top right of diagonal. */
        while (i >= 0 && inBoardBounds(board, i, j) && !win)
        {
            if (getBoardCell(board, i, j) == status)
            {
                ++consecutive;
            }
            else
            {
                consecutive = 0;
            }
            --i;
            ++j;
            win = consecutive >= board->winRequirement;
        }
        ++diagonal;
    }

    return win;
}


/* Checks if the given status occurs consecutively enough along any falling
   diagonal to be a win.
   A falling diagonal is one that goes from the top of the board to the bottom
   and it goes from left to right. */
static int hasWonFallingDiagonal(GameBoard const* board, CellStatus status)
{
    int win = 0;
    unsigned consecutive = 0;
    unsigned long diagonal = 0;
    unsigned i = 0;
    unsigned j = 0;
    unsigned long const numDiagonals = board->rows - 1ul + board->columns;

    while (diagonal < numDiagonals && !win)
    {
        /* Start at top left of diagonal, either on first row or first column. */
        if (diagonal < board->columns)
        {
            i = 0;
            j = board->columns - diagonal - 1u;
        }
        else
        {
            i = diagonal + 1u - board->columns;
            j = 0;
        }

        /* Scan down to bottom right of diagonal. */
        while (inBoardBounds(board, i, j) && !win)
        {
            if (getBoardCell(board, i, j) == status)
            {
                ++consecutive;
            }
            else
            {
                consecutive = 0;
            }
            ++i;
            ++j;
            win = consecutive >= board->winRequirement;
        }
        ++diagonal;
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

    clearBoardCells(&board);

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


void clearBoardCells(GameBoard* board)
{
    unsigned i = 0;
    unsigned j = 0;

    for (i = 0; i < board->rows; ++i)
    {
        for (j = 0; j < board->columns; ++j)
        {
            setBoardCell(board, i, j, CELL_EMPTY);
        }
    }
}


int hasPlayerWon(GameBoard const* board, Player player)
{
    int win = 0;
    CellStatus cellStatus = playerToCell(player);

    /* Check for a win along a row. */
    win = win || hasWonRow(board, cellStatus);

    /* Check for a win along a column. */
    win = win || hasWonColumn(board, cellStatus);

    /* Check for a win along a rising diagonal.*/
    win = win || hasWonRisingDiagonal(board, cellStatus);

    /* Check for a win along a falling diagonal. */
    win = win || hasWonFallingDiagonal(board, cellStatus);

    return win;
}


int inBoardBounds(GameBoard const* board, unsigned row, unsigned column)
{
    return row < board->rows && column < board->columns;
}


void setBoardCell(GameBoard* board, unsigned row, unsigned column, CellStatus status)
{
    assert(inBoardBounds(board, row, column));

    board->cells[row * board->columns + column] = status;
}


CellStatus getBoardCell(GameBoard const* board, unsigned row, unsigned column)
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
            switch (getBoardCell(board, i, j))
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
