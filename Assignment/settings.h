/* Program/game settings management. */

#ifndef SETTINGS_H
#define SETTINGS_H


/* Stores the program/game settings. */
typedef struct {
    unsigned boardRows;
    unsigned boardColumns;
    unsigned winRequirement;
} Settings;


/* Returns a Settings object with all members zeroed out.
   Mainly for debugging purposes so we can initialise Settings objects with
   known values rather than garbage.*/
Settings zeroedSettings();

/* Reads settings from the given settings file path.
   If an error occurs, prints info to stderr, sets error to 1, and returns a
   zeroed Settings object. */
Settings readSettings(char const* filePath, int* error);


#endif
