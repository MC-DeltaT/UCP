/* Unit tests for the board module. */

#include "board_test.h"

#include "common.h"
#include "../main/board.h"
#include "../main/common.h"

#include <assert.h>
#include <stdio.h>
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
                        assert(getBoardCell(&board, i, j) == CELL_EMPTY);
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


/* Tests setBoardCell() and getBoardCell(). */
static void setGetBoardCellTest(void)
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

                        setBoardCell(&board, i, j, status);
                        assert(getBoardCell(&board, i, j) == status);
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

                        assert(getBoardCell(&board, i, j) == status);
                    }
                }

                destroyGameBoard(&board);
            }
        }
    }
}


/* Tests clearBoardCells(). */
static void clearBoardCellsTest(void)
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

                        setBoardCell(&board, i, j, status);
                    }
                }

                clearBoardCells(&board);

                for (i = 0; i < rows; ++i)
                {
                    for (j = 0; j < columns; ++j)
                    {
                        assert(getBoardCell(&board, i, j) == CELL_EMPTY);
                    }
                }

                destroyGameBoard(&board);
            }
        }
    }
}


/* Tests hasPlayerWon(). */
static void hasPlayerWonTest(void)
{
    GameBoard board = zeroedGameBoard();

    printf("Rows < columns (diff>1):\n");
    board = createGameBoard(8, 10, 3);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Rows < columns (diff=1):\n");
    board = createGameBoard(9, 10, 3);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Rows = columns:\n");
    board = createGameBoard(10, 10, 3);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Rows > columns (diff=1):\n");
    board = createGameBoard(10, 9, 3);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Rows > columns (diff>1):\n");
    board = createGameBoard(10, 8, 3);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Horizontal win (edge):\n");
    board = createGameBoard(10, 7, 4);
    setBoardCell(&board, 0, 0, CELL_X);
    setBoardCell(&board, 0, 1, CELL_X);
    setBoardCell(&board, 0, 2, CELL_X);
    setBoardCell(&board, 0, 3, CELL_X);
    assert(hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Horizontal win (non-edge):\n");
    board = createGameBoard(4, 7, 4);
    setBoardCell(&board, 2, 2, CELL_O);
    setBoardCell(&board, 2, 3, CELL_O);
    setBoardCell(&board, 2, 4, CELL_O);
    setBoardCell(&board, 2, 5, CELL_O);
    assert(hasPlayerWon(&board, PLAYER_O));
    assert(!hasPlayerWon(&board, PLAYER_X));
    destroyGameBoard(&board);
    printf("\n");

    printf("Vertical win (edge):\n");
    board = createGameBoard(10, 7, 4);
    setBoardCell(&board, 0, 0, CELL_O);
    setBoardCell(&board, 1, 0, CELL_O);
    setBoardCell(&board, 2, 0, CELL_O);
    setBoardCell(&board, 3, 0, CELL_O);
    assert(hasPlayerWon(&board, PLAYER_O));
    assert(!hasPlayerWon(&board, PLAYER_X));
    destroyGameBoard(&board);
    printf("\n");

    printf("Vertical win (non-edge):\n");
    board = createGameBoard(9, 7, 4);
    setBoardCell(&board, 4, 3, CELL_X);
    setBoardCell(&board, 5, 3, CELL_X);
    setBoardCell(&board, 6, 3, CELL_X);
    setBoardCell(&board, 7, 3, CELL_X);
    assert(hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Rising diagonal win (from corner):\n");
    board = createGameBoard(10, 5, 4);
    setBoardCell(&board, 9, 0, CELL_O);
    setBoardCell(&board, 8, 1, CELL_O);
    setBoardCell(&board, 7, 2, CELL_O);
    setBoardCell(&board, 6, 3, CELL_O);
    assert(hasPlayerWon(&board, PLAYER_O));
    assert(!hasPlayerWon(&board, PLAYER_X));
    destroyGameBoard(&board);
    printf("\n");

    printf("Rising diagonal win (not from corner):\n");
    board = createGameBoard(7, 7, 4);
    setBoardCell(&board, 5, 2, CELL_X);
    setBoardCell(&board, 4, 3, CELL_X);
    setBoardCell(&board, 3, 4, CELL_X);
    setBoardCell(&board, 2, 5, CELL_X);
    assert(hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Falling diagonal win (from corner):\n");
    board = createGameBoard(8, 10, 4);
    setBoardCell(&board, 0, 0, CELL_X);
    setBoardCell(&board, 1, 1, CELL_X);
    setBoardCell(&board, 2, 2, CELL_X);
    setBoardCell(&board, 3, 3, CELL_X);
    assert(hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("Falling diagonal win (not from corner):\n");
    board = createGameBoard(7, 7, 4);
    setBoardCell(&board, 2, 3, CELL_O);
    setBoardCell(&board, 3, 4, CELL_O);
    setBoardCell(&board, 4, 5, CELL_O);
    setBoardCell(&board, 5, 6, CELL_O);
    assert(hasPlayerWon(&board, PLAYER_O));
    assert(!hasPlayerWon(&board, PLAYER_X));
    destroyGameBoard(&board);
    printf("\n");

    printf("Almost win:\n");
    board = createGameBoard(6, 8, 3);
    setBoardCell(&board, 1, 1, CELL_X);
    setBoardCell(&board, 2, 2, CELL_X);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");

    printf("K=1:\n");
    board = createGameBoard(4, 3, 1);
    setBoardCell(&board, 1, 1, CELL_O);
    assert(hasPlayerWon(&board, PLAYER_O));
    assert(!hasPlayerWon(&board, PLAYER_X));
    destroyGameBoard(&board);
    printf("\n");

    printf("K>M>=N:\n");
    board = createGameBoard(4, 3, 5);
    setBoardCell(&board, 0, 1, CELL_O);
    setBoardCell(&board, 1, 1, CELL_O);
    setBoardCell(&board, 2, 1, CELL_O);
    setBoardCell(&board, 3, 1, CELL_O);
    assert(!hasPlayerWon(&board, PLAYER_X));
    assert(!hasPlayerWon(&board, PLAYER_O));
    destroyGameBoard(&board);
    printf("\n");
}


/* Tests displayGameBoard(). */
static void displayGameBoardTest(void)
{
    GameBoard board = zeroedGameBoard();

    printf("1x1 board:\n");
    board = createGameBoard(1, 1, 1);
    setBoardCell(&board, 0, 0, CELL_X);
    displayGameBoard(&board);
    destroyGameBoard(&board);
    printf("\n");

    printf("1x2 board:\n");
    board = createGameBoard(1, 2, 2);
    setBoardCell(&board, 0, 1, CELL_O);
    displayGameBoard(&board);
    destroyGameBoard(&board);
    printf("\n");

    printf("2x1 board:\n");
    board = createGameBoard(2, 1, 2);
    setBoardCell(&board, 1, 0, CELL_O);
    setBoardCell(&board, 0, 0, CELL_X);
    displayGameBoard(&board);
    destroyGameBoard(&board);
    printf("\n");

    printf("2x2 board:\n");
    board = createGameBoard(2, 2, 2);
    setBoardCell(&board, 0, 0, CELL_O);
    setBoardCell(&board, 1, 0, CELL_X);
    displayGameBoard(&board);
    destroyGameBoard(&board);
    printf("\n");

    printf("Large board:\n");
    board = createGameBoard(5, 7, 3);
    setBoardCell(&board, 0, 0, CELL_O);
    setBoardCell(&board, 1, 0, CELL_X);
    setBoardCell(&board, 1, 1, CELL_X);
    setBoardCell(&board, 3, 6, CELL_X);
    setBoardCell(&board, 4, 6, CELL_O);
    displayGameBoard(&board);
    destroyGameBoard(&board);
    printf("\n");
}


/* Tests playerToCell(). */
static void playerToCellTest(void)
{
    assert(playerToCell(PLAYER_X) == CELL_X);
    assert(playerToCell(PLAYER_O) == CELL_O);
}



/* PUBLIC INTERFACE */


void boardTest(void)
{
    moduleTestHeader("board");

    runUnitTest("zeroedGameBoard()", zeroedGameBoardTest);
    runUnitTest("createGameBoard() and destroyGameBoard()",
        createDestroyGameBoardTest);
    runUnitTest("inBoard bounds()", inBoardBoundsTest);
    runUnitTest("setBoardCell() and getBoardCell()", setGetBoardCellTest);
    runUnitTest("clearBoardCells()", clearBoardCellsTest);
    runUnitTest("hasPlayerWon()", hasPlayerWonTest);
    runUnitTest("displayGameBoard()", displayGameBoardTest);
    runUnitTest("playerToCell()", playerToCellTest);
}
