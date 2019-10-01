/* Game board and mechanics. */


#ifndef BOARD_H
#define BOARD_H


#include "common.h"


/* Represents a cell in the tic-tac-toe board. */
typedef enum
{
    CELL_EMPTY,         /* Empty cell. */
    CELL_X,             /* Cell occupied by an "X". */
    CELL_O              /* Cell occupied by an "O". */
} CellStatus;


/* Represents the tic-tac-toe board.
   Use createGameBoard to properly create the board,
   and destroyGameBoard to properly destroy it. */
typedef struct
{
    unsigned rows;                  /* Height of the board ("n" value). */
    unsigned columns;               /* Width of the board ("m" value). */
    unsigned winRequirement;        /* Consecutive cells to win ("k" value). */
    /* Cells are stored in row-major format
        (i.e. consecutive cells in a row are consecutive in the array). */
    CellStatus* cells;
} GameBoard;


/* Returns a GameBoard object with all members zeroed out.
   Mainly for debugging purposes so we can initialise GameBoard objects with
   known values rather than have them unspecified.*/
GameBoard zeroedGameBoard(void);

/* Creates a game board from the given parameters.
   rows, columns and winRequirement must all be >0. */
GameBoard createGameBoard(unsigned rows, unsigned columns,
                          unsigned winRequirement);

/* Destroys a game board (deallocates resources, etc.). */
void destroyGameBoard(GameBoard* board);

/* Sets all cells of a board to CELL_EMPTY. */
void clearCells(GameBoard* board);

/* Checks if Xs has won on the given board. */
int hasXWon(GameBoard const* board);

/* Checks if Os has won on the given board. */
int hasOWon(GameBoard const* board);

/* Checks if the given row and column are within the bounds of the board. */
int inBoardBounds(GameBoard const* board, unsigned row, unsigned column);

/* Sets the status of a board cell.
   row and column must be within the bounds of the board. */
void setCell(GameBoard* board, unsigned row, unsigned column,
             CellStatus status);

/* Gets the status of a board cell.
   row and column must be within the bounds of the board. */
CellStatus getCell(GameBoard const* board, unsigned row, unsigned column);

/* Prints a game board to stdout. */
void displayGameBoard(GameBoard const* board);

/* Returns CELL_X for PLAYER_X and CELL_O for PLAYER_O. */
CellStatus playerToCell(Player player);


#endif
