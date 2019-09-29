/* Game board and mechanics. */


#ifndef BOARD_H
#define BOARD_H


/* Represents a cell in the tic-tac-toe board. */
enum CellStatus {
    CELL_EMPTY,         /* empty cell. */
    CELL_X,             /* cell occupied by an "X". */
    CELL_O              /* cell occupied by an "O". */
};


/* Represents the tic-tac-toe board.
   Use createGameBoard to properly create the board,
   and destroyGameBoard to properly destroy it. */
typedef struct {
    unsigned rows;
    unsigned columns;
    unsigned winRequirement;
    /* Cells are stored in row-major format
        (i.e. consecutive cells in a row are consecutive in the array). */
    CellStatus* cells;
} GameBoard;


/* Returns a GameBoard object with all members zeroed out.
   Mainly for debugging purposes so we can initialise GameBoard objects with
   known values rather than garbage.*/
GameBoard zeroedGameBoard();

/* Creates a game board from the given parameters. */
GameBoard createGameBoard(unsigned rows, unsigned columns,
                          unsigned winRequirement);

/* Destroys a game board (deallocates resources, etc.). */
void destroyGameBoard(GameBoard* board);

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


#endif
