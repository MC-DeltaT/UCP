/* Program/game settings management. */

#include "settings.h"

#include "common.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>


/* Line length maximum for settings file. Any lines over this length are
   assumed to be invalid format. */
#define LINE_LEN_MAX 1024


/* PRIVATE INTERFACE */


/* Contains data needed while parsing an option from a settings file. */
typedef struct {
    char option;
    unsigned value;
    int beenRead;
} OptionData;


void setOption(OptionData options[], unsigned optionCount, char optionChar,
               long optionVal, unsigned lineNum, int* error)
{
    OptionData* option = NULL;
    unsigned i;

    i = 0;
    while (!option && i < optionCount)
    {
        if (options[i].option == optionChar)
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
                "Error in settings file, line %u: option %c already specified.",
                lineNum, optionChar);
            *error = 1;
        }
        else
        {
            if (optionVal <= 0 || optionVal > UINT_MAX)
            {
                fprintf(stderr,
                    "Error in settings file, line %u: option value out of range.\n",
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


void readSettingsLine(FILE* file, OptionData options[], unsigned optionCount,
                      unsigned* lineCount, int* error)
{
    char line[LINE_LEN_MAX] = {0};
    char optionChar = '\0';
    long optionVal = 0;
    int invalidFormat = 0;

    if (!*error)
    {
        if(fgets(line, LINE_LEN_MAX, file))
        {
            ++*lineCount;
            /* Whole line was read. */
            if (strchr(line, '\n'))
            {
                /* Note: can't use %u format specifier, because that, for some
                   ungodly reason, actually accepts negative values, and then
                   wraps them around to large positive values. */
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
            }
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


Settings zeroedSettings()
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
    OptionData options[] = {{'m'}, {'n'}, {'k'}};
    unsigned i;

    file = fopen(filePath, "r");
    if (file)
    {
        i = 0;
        while (!*error && !feof(file))
        {
            readSettingsLine(file, options, 3, &lineCount, error);
            ++i;
        }

        if (!*error)
        {
            settings.boardRows = options[1].value;
            settings.boardColumns = options[0].value;
            settings.winRequirement = options[2].value;
        }
    }
    else
    {
        fprintf(stderr, "Error opening settings file \"%s\": ", filePath);
        perror(NULL);
        *error = 1;
    }

    if (*error)
    {
        settings = zeroedSettings();
    }

    return settings;
}
