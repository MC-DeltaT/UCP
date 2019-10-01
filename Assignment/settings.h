/* Program/game settings management. */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>


/* Stores the program/game settings. */
typedef struct
{
    unsigned boardRows;         /* Height of the board ("n" value). */
    unsigned boardColumns;      /* Width of the board ("m" value). */
    unsigned winRequirement;    /* Consecutive cells to win ("k" value). */
} Settings;


/* Returns a Settings object with all members zeroed out.
   Mainly for debugging purposes so we can initialise Settings objects with
   known values rather than have them unspecified.*/
Settings zeroedSettings(void);

/* Reads settings from the given settings file path.
   If an error occurs, prints info to stderr, sets error to 1, and returns a
   zeroed Settings object. */
Settings readSettings(char const* filePath, int* error);

/* Validates the given settings.
   If a setting is invalid, prints an error to stderr and returns 0.
   If a setting is potentially invalid (i.e technically valid but the user may
   have made a mistake), prints a warning to stdout and returns 1.
   If all settings are not invalid, returns 1.
   */
int validateSettings(Settings const* settings);

/* Writes the given settings in textual form to the given stream. */
void writeSettings(FILE* stream, Settings const* settings);


#endif
