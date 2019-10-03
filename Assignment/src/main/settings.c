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
                "Error in settings file, line %u: option '%c' already specified.\n",
                lineNum, optionChar);
            *error = 1;
        }
        else
        {
            if (optionVal < 0)
            {
                fprintf(stderr,
                    "Error in settings file, line %u: option value must be non-negative.\n",
                    lineNum);
                *error = 1;
            }
            else if (optionVal > UINT_MAX)
            {
                fprintf(stderr,
                    "Error in settings file, line %u: option value too large.\n",
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
    int scanRes = 0;
    int scanned = 0;
    char optionChar = '\0';
    long optionVal = 0;

    if(fgets(line, LINE_LEN_MAX, file))
    {
        ++*lineCount;
        /* Whole line was read. */
        if (feof(file) || strchr(line, '\n'))
        {
            /* Ignore blank lines. */
            if (!isWhitespace(line))
            {
                /* Can't use %u format specifier, because that, for some ungodly
                   reason, actually accepts negative values, and then wraps them
                   around to large positive values. */
                scanRes = sscanf(line, " %c =%ld%n", &optionChar, &optionVal,
                    &scanned);
                /* No idea what happens if the character read count can't fit in
                   an int (%n doesn't seem to work correctly with long int), it
                   doesn't seem to be documented. That shouldn't happen in this
                   case, however.*/
                if (scanRes == 2 && isWhitespace(line + scanned))
                {
                    setOption(options, optionCount, optionChar, optionVal,
                        *lineCount, error);
                }
                else
                {
                    fprintf(stderr,
                        "Error in settings file, line %u: invalid option format.\n",
                        *lineCount);
                    *error = 1;
                }
            }
        }
        /* Line too long for buffer. */
        else
        {
            fprintf(stderr,
                "Error in settings file, line %u: line too long.\n",
                *lineCount);
            *error = 1;
            /* Read the rest of the line so parsing of the file can continue
               normally. */
            readUntil(file, '\n', 1);
        }
    }
}



/* PUBLIC INTERFACE */


Settings zeroedSettings(void)
{
    Settings settings;

    settings.n = 0;
    settings.m = 0;
    settings.k = 0;

    return settings;
}


Settings readSettings(char const* filePath, int* error)
{
    Settings settings = zeroedSettings();
    FILE* file = NULL;
    unsigned lineCount = 0;
    OptionData options[] = {
        /* Note: other members automatically init to 0. */
        {'M'},
        {'N'},
        {'K'}
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
                        "Error in settings file: required option '%c' was not specified.\n",
                        options[i].option);
                    *error = 1;
                }
            }
        }

        fclose(file);
        file = NULL;

        if (!*error)
        {
            settings.m = options[0].value;
            settings.n = options[1].value;
            settings.k = options[2].value;
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


int validateMSetting(unsigned m)
{
    int result = 1;

    if (m == 0)
    {
        fprintf(stderr, "Invalid setting: M must be >0.\n");
        result = 0;
    }

    return result;
}


int validateNSetting(unsigned n)
{
    int result = 1;

    if (n == 0)
    {
        fprintf(stderr, "Invalid setting: N must be >0.\n");
        result = 0;
    }

    return result;
}


int validateKSetting(unsigned k, int warnings)
{
    int result = 1;

    if (k == 0)
    {
        fprintf(stderr, "Invalid setting: K must be >0.\n");
        result = 0;
    }

    if (warnings && result && k == 1)
    {
        printf("Warning: K=1 will cause the first player to win instantly.\n");
    }

    return result;
}


int validateSettingsCombo(Settings const* settings, int warnings)
{
    int result = 1;
    unsigned m = settings->m;
    unsigned n = settings->n;
    unsigned k = settings->k;

    if (warnings && result && k > n && k > m)
    {
        printf(
            "Warning: with the set M, N and K values, no player can win a game.\n"
        );
    }

    return result;
}


int validateSettings(Settings const* settings, int warnings)
{
    /* unsigned type, bitwise operations on signed is asking for trouble. */
    unsigned result = 1;
    unsigned m = settings->m;
    unsigned n = settings->n;
    unsigned k = settings->k;

    result &= validateMSetting(m);
    result &= validateNSetting(n);
    /* Don't show warnings if settings are already invalid. */
    result &= validateKSetting(k, result);
    result &= validateSettingsCombo(settings, result);

    return result;
}


void writeSettings(FILE* stream, Settings const* settings)
{
    fprintf(stream, "SETTINGS:\n");
    fprintf(stream, "   M: %u\n", settings->m);
    fprintf(stream, "   N: %u\n", settings->n);
    fprintf(stream, "   K: %u\n", settings->k);
}
