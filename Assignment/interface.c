/* User interface and associated high-level logic. */

#include "interface.h"

#include "board.h"
#include "common.h"
#include "log.h"
#include "settings.h"

#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* PRIVATE INTERFACE */


/* Stores data required for main menu options. */
typedef struct
{
    char const* option;             /* Option displayed to user. */
    int (*handler)(Settings*);      /* Handler function. */
} MenuOption;


/* Gets an integer from the user. */
static long integerInput(char const* prompt)
{
    long val = 0;
    int valid = 0;
    static char line[128] = {0};
    char* end = NULL;

    do
    {
        printf("%s", prompt);
        fgets(line, sizeof line, stdin);

        /* Whole line was read. */
        if (strchr(line, '\n'))
        {
            errno = 0;
            val = strtol(line, &end, 10);

            /* Line is not a valid long int. Either the whole line is invalid,
               or there is a valid long int at the start but the rest is rubbish
               (e.g. "12sdfg"). */
            if (end == line || !isWhitespace(end))
            {
                fprintf(stderr, "Error: input must be an integer.\n");
            }
            else if (errno == ERANGE)
            {
                fprintf(stderr, "Error: value too large.\n");
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


static unsigned unsignedIntInput(char const* prompt)
{
    int valid = 0;
    long val;

    do {
        val = integerInput(prompt);
        if (val < 0)
        {
            fprintf(stderr, "Error: value must be >0.\n");
        }
        else if (val > UINT_MAX)
        {
            fprintf(stderr, "Error: value too large.\n");
        }
        else
        {
            valid = 1;
        }
    } while (!valid);

    return val;
}


static void coordinateInput(char const* prompt, long* row, long* column)
{
    int valid = 0;
    static char line[128] = {0};
    int scanRes = 0;
    int scanned = 0;

    do
    {
        printf("%s", prompt);
        fgets(line, sizeof line, stdin);

        /* Whole line was read. */
        if (strchr(line, '\n'))
        {
            /* Can't use %u format specifier again. */
            scanRes = sscanf(line, "%ld,%ld%n", column, row, &scanned);
            /* No idea what happens if the character read count can't fit in an
               int (%n doesn't seem to work correctly with long int), it doesn't
               seem to be documented. That shouldn't happen in this case,
               however.*/
            if (scanRes == 2 && isWhitespace(line + scanned))
            {
                valid = 1;
            }
            else
            {
                fprintf(stderr, "Error: input must be in format int,int\n");
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
}


/* Inputs and executes a player's turn. */
static void playerTurn(GameBoard* board, Player player)
{
    long row = 0;
    long column = 0;
    int validCoordinate = 0;

    printf("Player %c's turn.\n", playerToChar(player));

    do
    {
        coordinateInput("Enter coordinate: ", &row, &column);
        if (row < 0 || row > UINT_MAX || column < 0 || column > UINT_MAX ||
            !inBoardBounds(board, row, column))
        {
            fprintf(stderr, "Error: coordinate out of bounds.\n");
        }
        else
        {
            validCoordinate = 1;
        }
    } while(!validCoordinate);

    setCell(board, row, column, playerToCell(player));
}


/* Runs a game using the given settings. */
static int runGame(Settings* settings)
{
    GameBoard board = createGameBoard(settings->n, settings->m, settings->k);
    int xWon = 0;
    int oWon = 0;
    unsigned long placed = 0;
    unsigned long const cells = board.rows * board.columns;

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
    assert(!(xWon && oWon));
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


#ifndef SECRET_MODE
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
    struct tm const* time = localtime(&epochTime);
    assert(time);

    res = sprintf(fileName, "MNK_%u-%u-%u_%.2i-%.2i_%.2i-%.2i.log",
        settings->m, settings->n, settings->k, time->tm_hour, time->tm_min,
        time->tm_mday, time->tm_mon);
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
#endif


#ifdef EDITOR_MODE
/* Lets the user edit the current settings. */
static int editSettings(Settings* settings)
{
    do
    {
        settings->m = unsignedIntInput("Enter new M value: ");

        settings->n = unsignedIntInput("Enter new N value: ");

        settings->k = unsignedIntInput("Enter new K value: ");

        printf("\n");
    } while (!validateSettings(settings));

    return 0;
}
#endif


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
            choice = unsignedIntInput("Enter an option: ");
            if (choice < MENU_OPTION_COUNT)
            {
                validOption = 1;
            }
            else
            {
                assert(MENU_OPTION_COUNT - 1ul < ULONG_MAX);
                fprintf(stderr, "Error: option must be >=1 and <=%lu.\n",
                    (unsigned long)(MENU_OPTION_COUNT - 1ul));
            }
        } while (!validOption);
        --choice;

        assert(choice < MENU_OPTION_COUNT);
        exit = menuOptions[choice].handler(settings);
    } while (!exit);
}
