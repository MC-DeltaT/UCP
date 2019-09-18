#include "board.h"

#include <assert.h>
#include <stddef.h>


gameBoard createGameBoard(unsigned rows, unsigned columns, unsigned winRequirement)
{
	gameBoard board;
	board.cells = malloc(rows * columns * sizeof(cellStatus));
	board.rows = rows;
	board.columns = columns;
	board.winRequirement = winRequirement;
	return board;
}


void destroyGameBoard(gameBoard* board)
{
	board.rows = 0;
	board.columns = 0;
	free(board.cells);
	board.cells = NULL;
}


bool hasXWon(gameBoard const* board);


bool hasYWon(gameBoard const* board);


bool inBoardBounds(gameBoard const* board, unsigned row, unsigned column)
{
	return row < board->rows && column < board->columns;
}


void setCell(gameBoard* board, unsigned row, unsigned column, cellStatus status)
{
	assert(inBoardBounds(board, row, column));
	
	board->cells[row * board->columns + column] = status;
}


cellStatus getCell(gameBoard const* board, unsigned row, unsigned column)
{
	assert(inBoardBounds(board, row, column));
	
	return board->cells[row * board->columns + column];
}
