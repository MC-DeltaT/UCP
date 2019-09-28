/* Program/game settings management. */

#ifndef SETTINGS_H
#define SETTINGS_H


/* Stores the program/game settings. */
typedef struct {
    unsigned boardRows;
    unsigned boardColumns;
    unsigned winRequirement;
} Settings;


Settings readSettings(char const* filePath, int* error);


#endif
