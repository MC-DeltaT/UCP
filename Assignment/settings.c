/* Program/game settings management. */

#include "settings.h"

#include "common.h"

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>


/* Line length maximum for settings file. Any lines over this length are
   assumed to be invalid format. */
#define LINE_LEN_MAX 1024

#define BOARD_ROWS_OPTION 'n'
#define BOARD_COLUMNS_OPTION 'm'
#define WIN_REQ_OPTION 'k'


/* PRIVATE INTERFACE */


/* Contains data needed for parsing an option from a settings file. */
typedef struct
{
    char option;        /* Character used in file to indicate option. */
    unsigned value;     /* Value of option. */
    int beenRead;       /* Indicates if this option has been read yet. Does NOT
                           mean the option specification had to be valid. */
} OptionData;


static void setOption(OptionData options[], unsigned optionCount,
    char optionChar, long optionVal, unsigned lineNum, int* error)
{
    OptionData* option = NULL;
    unsigned i;

    i = 0;
    while (!option && i < optionCount)
    {
        if (tolower(options[i].option) == tolower(optionChar))
        {
            option = options + i;
        }
        ++i;
    }

    if (option)
    {
        if (option->beenRead)
        {
            fprintf(stderr,
                "Error in settings file, line %u: option %c already specified.\n",
                lineNum, optionChar);
            *error = 1;
        }
        else
        {
            if (optionVal <= 0 || optionVal > UINT_MAX)
            {
                fprintf(stderr,
                    "Error in settings file, line %u: option value must be non-negative.\n",
                    lineNum);
                *error = 1;
            }
            else
            {
                option->value = optionVal;
            }
            option->beenRead = 1;
        }
    }
    else
    {
        fprintf(stderr,
            "Error in settings file, line %u: invalid option '%c'.\n",
            lineNum, optionChar);
        *error = 1;
    }
}


static void readSettingsLine(FILE* file, OptionData options[],
    unsigned optionCount, unsigned* lineCount, int* error)
{
    char line[LINE_LEN_MAX] = {0};
    char optionChar = '\0';
    long optionVal = 0;
    int invalidFormat = 0;

    if(fgets(line, LINE_LEN_MAX, file))
    {
        ++*lineCount;
        /* Whole line was read. */
        if (strchr(line, '\n'))
        {
            /* Note: can't use %u format specifier, because that, for some
               ungodly reason, actually accepts negative values, and then wraps
               them around to large positive values. */
            if (2 == sscanf(line, "%c=%ld", &optionChar, &optionVal))
            {
                setOption(options, optionCount, optionChar, optionVal,
                    *lineCount, error);
            }
            else
            {
                invalidFormat = 1;
            }
        }
        /* Line too long for buffer, we assume it's invalid. */
        else
        {
            invalidFormat = 1;
            /* Read the rest of the line so parsing of the file can continue
               normally. */
            readUntil(file, '\n', 1);
        }

        if (invalidFormat)
        {
            fprintf(stderr,
                "Error in settings file, line %u: invalid option format.\n",
                *lineCount);
            *error = 1;
        }
    }
}



/* PUBLIC INTERFACE */


Settings zeroedSettings(void)
{
    Settings settings;

    settings.boardRows = 0;
    settings.boardColumns = 0;
    settings.winRequirement = 0;

    return settings;
}


Settings readSettings(char const* filePath, int* error)
{
    Settings settings = zeroedSettings();
    FILE* file = NULL;
    unsigned lineCount = 0;
    /* Note: other members automatically init to 0. */
    OptionData options[] = {
        {BOARD_ROWS_OPTION},
        {BOARD_COLUMNS_OPTION},
        {WIN_REQ_OPTION}
    };
    unsigned i = 0;

    file = fopen(filePath, "r");
    if (file)
    {
        /* Want to read entire file even if parse error occurs, to show the
           user all the errors. */
        while (!feof(file) && !ferror(file))
        {
            readSettingsLine(file, options, 3, &lineCount, error);
        }

        if (ferror(file))
        {
            fprintf(stderr, "Error reading settings file \"%s\": ", filePath);
            perror(NULL);
            *error = 1;
        }
        else
        {
            for (i = 0; i < 3; ++i)
            {
                if (!options[i].beenRead)
                {
                    fprintf(stderr,
                        "Error in settings file: required option %c was not specified.\n",
                        options[i].option);
                    *error = 1;
                }
            }
        }

        if (!*error)
        {
            settings.boardRows = options[0].value;
            settings.boardColumns = options[1].value;
            settings.winRequirement = options[2].value;
        }
    }
    else
    {
        fprintf(stderr, "Error opening settings file \"%s\": ", filePath);
        perror(NULL);
        *error = 1;
    }

    return settings;
}


int validateSettings(Settings const* settings)
{
    int result = 1;
    unsigned boardRows = settings->boardRows;
    unsigned boardColumns = settings->boardColumns;
    unsigned winRequirement = settings->winRequirement;

    if (boardRows == 0)
    {
        fprintf(stderr, "Error in settings: %c must be >0.\n",
            BOARD_ROWS_OPTION);
        result = 0;
    }

    if (boardColumns == 0)
    {
        fprintf(stderr, "Error in settings: %c must be >0.\n",
            BOARD_COLUMNS_OPTION);
        result = 0;
    }

    if (winRequirement == 0)
    {
        fprintf(stderr, "Error in settings: %c must be >0.\n", WIN_REQ_OPTION);
        result = 0;
    }

    /* Doesn't make sense to show this if board dimensions are 0. */
    if (result && winRequirement > boardRows && winRequirement > boardColumns)
    {
        printf("Warning: with the set %c, %c and %c values, games can only end in a draw.\n",
            BOARD_ROWS_OPTION, BOARD_COLUMNS_OPTION, WIN_REQ_OPTION);
    }

    return result;
}
