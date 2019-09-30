/* Unit tests for the board module. */

#include "board_test.h"

#include "../board.h"
#include "common.h"

#include <assert.h>
#include <stdlib.h>


/* Controls the maximum dimensions of the game board when testing. */
#define TEST_SIZE 50u


/* PRIVATE INTERFACE */


/* Tests zeroedGameBoard(). */
static void zeroedGameBoardTest(void)
{
    GameBoard board = zeroedGameBoard();
    assert(board.rows == 0);
    assert(board.columns == 0);
    assert(board.winRequirement == 0);
}


/* Tests createGameBoard() and destroyGameBoard(). */
static void createDestroyGameBoardTest(void)
{
    GameBoard board = zeroedGameBoard();
    unsigned rows = 0;
    unsigned columns = 0;
    unsigned winRequirement = 0;
    unsigned i = 0;
    unsigned j = 0;

    for (rows = 1u; rows < TEST_SIZE; ++rows)
    {
        for (columns = 1u; columns < TEST_SIZE; ++columns)
        {
            for (winRequirement = 1u; winRequirement < TEST_SIZE; ++winRequirement)
            {
                board = createGameBoard(rows, columns, winRequirement);
                assert(board.rows == rows);
                assert(board.columns == columns);
                assert(board.winRequirement == winRequirement);
                assert(board.cells != NULL);

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        assert(getCell(&board, i, j) == CELL_EMPTY);
                    }
                }

                destroyGameBoard(&board);
                assert(board.rows == 0);
                assert(board.columns == 0);
                assert(board.winRequirement == 0);
                assert(board.cells == NULL);
            }
        }
    }
}


/* Tests inBoardBounds(). */
static void inBoardBoundsTest(void)
{
    GameBoard board = zeroedGameBoard();
    unsigned rows = 0;
    unsigned columns = 0;
    unsigned winRequirement = 0;
    unsigned i = 0;
    unsigned j = 0;

    for (rows = 1u; rows < TEST_SIZE; ++rows)
    {
        for (columns = 1u; columns < TEST_SIZE; ++columns)
        {
            for (winRequirement = 1u; winRequirement < TEST_SIZE; ++winRequirement)
            {
                board = createGameBoard(rows, columns, winRequirement);

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        assert(inBoardBounds(&board, i, j));
                    }
                }

                for (i = rows; i < rows * 2u; ++i)
                {
                    for (j = columns; j < columns * 2u; ++j)
                    {
                        assert(!inBoardBounds(&board, i, j));
                    }
                }

                destroyGameBoard(&board);
            }
        }
    }
}


/* Tests setCell() and getCell(). */
static void setGetCellTest(void)
{
    GameBoard board = zeroedGameBoard();
    unsigned rows = 0;
    unsigned columns = 0;
    unsigned winRequirement = 0;
    unsigned i = 0;
    unsigned j = 0;
    unsigned s = 0;
    CellStatus status;

    for (rows = 1u; rows < TEST_SIZE; ++rows)
    {
        for (columns = 1u; columns < TEST_SIZE; ++columns)
        {
            for (winRequirement = 1u; winRequirement < TEST_SIZE; ++winRequirement)
            {
                board = createGameBoard(rows, columns, winRequirement);

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        s = (i + j) % 3u;
                        switch (s)
                        {
                            case 0: status = CELL_EMPTY; break;
                            case 1: status = CELL_X; break;
                            case 2: status = CELL_O; break;
                            default: assert(0);
                        }

                        setCell(&board, i, j, status);
                        assert(getCell(&board, i, j) == status);
                    }
                }

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        s = (i + j) % 3u;
                        switch (s)
                        {
                            case 0: status = CELL_EMPTY; break;
                            case 1: status = CELL_X; break;
                            case 2: status = CELL_O; break;
                            default: assert(0);
                        }

                        assert(getCell(&board, i, j) == status);
                    }
                }

                destroyGameBoard(&board);
            }
        }
    }
}


/* Tests clearCells(). */
static void clearCellsTest(void)
{
    GameBoard board = zeroedGameBoard();
    unsigned rows = 0;
    unsigned columns = 0;
    unsigned winRequirement = 0;
    unsigned i = 0;
    unsigned j = 0;
    unsigned s;
    CellStatus status;

    for (rows = 1u; rows < TEST_SIZE; ++rows)
    {
        for (columns = 1u; columns < TEST_SIZE; ++columns)
        {
            for (winRequirement = 1u; winRequirement < TEST_SIZE; ++winRequirement)
            {
                board = createGameBoard(rows, columns, winRequirement);

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        s = rand() % 3u;
                        switch (s)
                        {
                            case 0: status = CELL_EMPTY; break;
                            case 1: status = CELL_X; break;
                            case 2: status = CELL_O; break;
                            default: assert(0);
                        }

                        setCell(&board, i, j, status);
                    }
                }

                clearCells(&board);

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        assert(getCell(&board, i, j) == CELL_EMPTY);
                    }
                }

                destroyGameBoard(&board);
            }
        }
    }
}



/* PUBLIC INTERFACE */


void boardTest(void)
{
    moduleTestHeader("board");

    runUnitTest("zeroedGameBoard()", zeroedGameBoardTest);
    runUnitTest("createGameBoard() and destroyGameBoard()",
        createDestroyGameBoardTest);
    runUnitTest("inBoard bounds()", inBoardBoundsTest);
    runUnitTest("setCell() and getCell()", setGetCellTest);
    runUnitTest("clearCells()", clearCellsTest);
}
