#include "settings_test.h"

#include "../settings.h"

#include <assert.h>
#include <stdio.h>


char const NONEXISTENT_FILE[] = "settings_data/nonexistent_file.txt";
char const EMPTY_FILE[] = "settings_data/empty.txt";
char const INVALID_FORMAT[] = "settings_data/invalid_format.txt";
char const INVALID_OPTION[] = "settings_data/invalid_option.txt";
char const MISSING_OPTION[] = "settings_data/missing_option.txt";
char const MISSING_OPTIONS[] = "settings_data/missing_options.txt";
char const INVALID_OPTION_AND_MISSING[] = "settings_data/invalid_option_missing.txt";
char const INVALID_FORMAT_AND_MISSING[] = "settings_data/invalid_format_missing.txt";
char const VALID[] = "settings_data/valid.txt";


void settings_test()
{
    int error = 0;
    Settings settings = zeroedSettings();

    printf("Non-existent file test:\n");
    error = 0;
    settings = readSettings(NONEXISTENT_FILE, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Empty file test:\n");
    error = 0;
    settings = readSettings(EMPTY_FILE, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Invalid line format test:\n");
    error = 0;
    settings = readSettings(INVALID_FORMAT, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Invalid option test:\n");
    error = 0;
    settings = readSettings(INVALID_OPTION, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Missing option test:\n");
    error = 0;
    settings = readSettings(MISSING_OPTION, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Missing options test:\n");
    error = 0;
    settings = readSettings(MISSING_OPTIONS, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Invalid option and missing option test:\n");
    error = 0;
    settings = readSettings(INVALID_OPTION_AND_MISSING, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Invalid format and missing option test:\n");
    error = 0;
    settings = readSettings(INVALID_FORMAT_AND_MISSING, &error);
    assert(error);
    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
    printf("\n");

    printf("Valid file test:\n");
    error = 0;
    settings = readSettings(VALID, &error);
    assert(!error);
    assert(settings.boardRows == 10);
    assert(settings.boardColumns == 45);
    assert(settings.winRequirement == 6);
    printf("\n");
}
