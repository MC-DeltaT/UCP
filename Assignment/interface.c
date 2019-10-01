/* User interface and associated high-level logic. */

#include "interface.h"

#include "board.h"
#include "common.h"
#include "log.h"
#include "settings.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


/* PRIVATE INTERFACE */


/* Stores data required for main menu options. */
typedef struct
{
    char const* option;             /* Option displayed to user. */
    int (*handler)(Settings*);      /* Handler function. */
} MenuOption;


/* Gets an unsigned integer from the user. */
static unsigned unsignedIntInput(void)
{
    long val = 0;
    int valid = 0;
    static char line[128] = {0};
    char end = '\0';

    do
    {
        fgets(line, sizeof line, stdin);

        /* Whole line was read. */
        if (strchr(line, '\n'))
        {
            /* Can't use strtoul, because that, for some ungodly reason,
               actually accepts negative values, and then wraps them around to
               large positive values. */
            val = strtol(line, &end, 10);

            /* Line is not a valid long int. Either the whole line is invalid,
               or there is a valid long int at the start but the rest is rubbish
               (e.g. "12sdfglkstr"). */
            if (end == line || (*end != '\0' && !isspace(*end)))
            {
                fprintf(stderr, "Error: input must be an integer.\n");
            }
            else if (val < 0)
            {
                fprintf(stderr, "Error: number must be >=0.\n");
            }
            else if (val > UINT_MAX)
            {
                fprintf(stderr, "Error: number too large.\n");
            }
            else
            {
                valid = 1;
            }
        }
        else
        {
            fprintf(stderr, "Error: input too long.\n");
            /* Remove the rest of the line from stdin so it doesn't mess up the
               next input. */
            readUntil(stdin, '\n', 1);
        }
    } while (!valid);

    return val;
}


/* Inputs and executes a player's turn. */
static void playerTurn(GameBoard* board, Player player)
{
    unsigned row = 0;
    unsigned column = 0;
    int validCoordinate = 0;

    printf("Player %c's turn.\n", playerToChar(player));

    do
    {
        printf("Enter coordinate: ");
        coordinateInput(&row, &column);
        if (inBoardBounds(board, row, column))
        {
            validCoordinate = 1;
        }
        else
        {
            fprintf(stderr, "Error: coordinate out of bounds.\n");
        }
    } while(!validCoordinate);

    setCell(board, row, column, playerToCell(player));
}


/* Runs a game using the given settings. */
static int runGame(Settings* settings)
{
    GameBoard board = createGameBoard(settings->boardRows,
            settings->boardColumns, settings->winRequirement);
    int xWon = 0;
    int oWon = 0;
    unsigned long placed = 0;
    unsigned long const cells = board->rows * board->columns;

    newGameLog();

    while (placed < cells && !xWon && !oWon)
    {
        playerTurn(&board, PLAYER_X);
        ++placed;
        printf("\n");
        displayGameBoard(&board);
        xWon = hasXWon(&board);
        if (!xWon)
        {
            playerTurn(&board, PLAYER_O);
            ++placed;
            printf("\n");
            displayGameBoard(&board);
            oWon = hasOWon(&board);
        }
    }

    printf("Game complete.\n");
    printf("Result: ");
    assert(!(xWon && yWon));
    if (xWon)
    {
        printf("player X has won!\n");
    }
    else if (oWon)
    {
        printf("player O has won!\n");
    }
    else
    {
        printf("draw.\n");
    }

    return 0;
}


/* Displays the current settings to the user. */
static int displaySettings(Settings* settings)
{
    printf("\n");
    writeSettings(stdout, settings);
    printf("\n");

    return 0;
}


/* Displays game logs to the user. */
static int displayLogs(Settings* _)
{
    printf("\n");
    writeGameLogs(stdout);

    return 0;
}


/* Saves the game logs to file. */
static int saveLogs(Settings* settings)
{
    /* Theoretically there is no upper limit on the size of the integer types
       and thus the length of string required to represent them, but this is
       plenty for today's systems. */
    char fileName[256] = {0};
    FILE* file = NULL;
    int res = 0;
    time_t epochTime = time(NULL);
    tm const* time = localtime(&epochTime);
    assert(time);

    res = sprintf(fileName, "MNK_%u-%u-%u_%.2i-%.2i_%.2i-%.2i.log",
        settings->boardColumns, settings->boardRows, settings->winRequirement,
        time->tm_hour, time->tm_min, time->tm_day, time->tm_month);
    assert(res > 0);

    printf("Saving logs to file %s ...", fileName);
    file = fopen(fileName, "w");
    if (file)
    {
        writeSettings(file, settings);
        writeGameLogs(file);

        if (ferror(file))
        {
            perror("Error writing to log file");
        }
        else
        {
            printf(" success\n");
        }

        fclose(file);
        file = NULL;
    }
    else
    {
        perror("Error opening log file");
    }

    return 0;
}


/* Lets the user edit the current settings. */
static int editSettings(Settings* settings)
{
    do
    {
        printf("Enter new M value: ");
        settings->boardColumns = unsignedIntInput();

        printf("Enter new N value: ");
        settings->boardRows = unsignedIntInput();

        printf("Enter new K value: ");
        settings->winRequirement = unsignedIntInput();

        printf("\n");
    } while (!validateSettings(settings));

    return 0;
}


static int exitApplication(Settings* _)
{
    /* Non-zero return signals mainMenu() to exit. */
    return 1;
}


static MenuOption const menuOptions[] = {
    {"Start a new game", runGame},
#ifdef EDITOR_MODE
    {"Edit settings", editSettings},
#endif
    {"View current settings", displaySettings},
    {"View game logs", displayLogs},
#ifndef SECRET_MODE
    {"Save game logs to file", saveLogs},
#endif
    {"Exit application", exitApplication},
};


static size_t const MENU_OPTION_COUNT = sizeof menuOptions / sizeof menuOptions[0];



/* PUBLIC INTERFACE */


void mainMenu(Settings* settings)
{
    unsigned choice = 0;
    unsigned i = 0;
    int exit = 0;
    int validOption = 0;

    do
    {
        printf("Main menu:\n");
        for (i = 0; i < MENU_OPTION_COUNT; ++i)
        {
            printf("\t%u) %s\n", i + 1u, menuOptions[i].option);
        }
        printf("\n");

        validOption = 0;
        do
        {
            printf("Enter an option: ");
            choice = unsignedIntInput();
            if (choice > 0 && choice < MENU_OPTION_COUNT)
            {
                validOption = 1;
            }
            else
            {
                fprintf(stderr, "Error: option must be >=1 and <=%u.\n",
                    MENU_OPTION_COUNT - 1u);
            }
        } while (!validOption);
        --choice;

        assert(choice < MENU_OPTION_COUNT);
        exit = menuOptions[choice].handler(settings);
    } while (!exit);
}
