#ifndef BOARD_H
#define BOARD_H


/* Represents a cell in the tic-tac-toe board. */
enum cellStatus { CELL_EMPTY, CELL_X, CELL_O };


/* Represents the tic-tac-toe board.
	Use createGameBoard to properly create the board,
	and destroyGameBoard to properly destroy it. */
typedef struct {
	unsigned rows;
	unsigned columns;
	unsigned winRequirement;
	/* Cells are stored in row-major format
		(i.e. consecutive cells in a row are consecutive in the array). */
	cellStatus* cells;
} gameBoard;



/* Creates a game board from the given parameters. */
gameBoard createGameBoard(unsigned rows, unsigned columns, unsigned winRequirement);

/* Destroys a game board (deallocates resources, etc.). */
void destroyGameBoard(gameBoard* board);

/* Checks if Xs has won on the given board. */
bool hasXWon(gameBoard const* board);

/* Checks if Os has won on the given board. */
bool hasYWon(gameBoard const* board);

/* Checks if the given row and column are within the bounds of the board. */
bool inBoardBounds(gameBoard const* board, unsigned row, unsigned column);

/* Sets the status of a board cell.
	row and column must be within the bounds of the board. */
void setCell(gameBoard* board, unsigned row, unsigned column, cellStatus status);

/* Gets the status of a board cell.
	row and column must be within the bounds of the board. */
cellStatus getCell(gameBoard const* board, unsigned row, unsigned column);


#endif
