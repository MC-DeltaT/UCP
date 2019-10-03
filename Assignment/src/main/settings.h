/* Program/game settings management. */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>


/* Stores the program/game settings. */
typedef struct
{
    unsigned m;         /* Width of the board (number of columns). */
    unsigned n;         /* Height of the board (number of rows). */
    unsigned k;         /* Number of consecutive cells to win. */
} Settings;


/* Returns a Settings object with all members zeroed out.
   Mainly for debugging purposes so we can initialise Settings objects with
   known values rather than have them unspecified.*/
Settings zeroedSettings(void);

/* Reads settings from the given settings file path.
   If an error occurs, prints info to stderr, sets error to 1, and returns a
   zeroed Settings object. */
Settings readSettings(char const* filePath, int* error);

/* Validates the given 'M' settings value.
   If it's invalid, prints an error to stderr and returns 0.
   If it's valid, returns 1. */
int validateMSetting(unsigned m);

/* Validates the given 'N' settings value.
   If it's invalid, prints an error to stderr and returns 0.
   If it's valid, returns 1. */
int validateNSetting(unsigned n);

/* Validates the given 'K' settings value.
   If warnings is non-zero, additional warning messages will be printed to
   stdout for certain values.
   If it's invalid, prints an error to stderr and returns 0.
   If it's valid, returns 1. */
int validateKSetting(unsigned k, int warnings);

/* Validates the given combination of settings.
   The individual settings's values are assumed to be valid.
   If warnings is non-zero, additional warning messages will be printed to
   stdout for certain combinations of settings.
   If the settings are invalid, prints errors to stderr and returns 0.
   If all settings are valid, returns 1. */
int validateSettingsCombo(Settings const* settings, int warnings);

/* Validates the given setting, individually and in combination.
   If warnings is non-zero, additional warning messages will be printed to
   stdout for certain cases.
   If the settings are invalid, prints errors to stderr and returns 0.
   If all settings are valid, returns 1. */
int validateSettings(Settings const* settings, int warnings);

/* Writes the given settings in textual form to the given stream. */
void writeSettings(FILE* stream, Settings const* settings);


#endif
