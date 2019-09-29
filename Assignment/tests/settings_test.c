/* Unit tests for the settings module. */

#include "settings_test.h"

#include "common.h"
#include "../settings.h"

#include <assert.h>
#include <stdio.h>


#define NONEXISTENT_FILE "settings_data/nonexistent_file.txt"
#define EMPTY_FILE "settings_data/empty.txt"
#define INVALID_FORMAT "settings_data/invalid_format.txt"
#define INVALID_OPTION "settings_data/invalid_option.txt"
#define INVALID_OPTIONS "settings_data/invalid_options.txt"
#define MISSING_OPTION "settings_data/missing_option.txt"
#define MISSING_OPTIONS "settings_data/missing_options.txt"
#define DUPLICATE_OPTION "settings_data/duplicate_option.txt"
#define DUPLICATE_OPTIONS "settings_data/duplicate_options.txt"
#define INVALID_OPTION_AND_MISSING "settings_data/invalid_option_missing.txt"
#define INVALID_FORMAT_AND_MISSING "settings_data/invalid_format_missing.txt"
#define DUPLICATE_INVALID_FORMAT "settings_data/duplicate_invalid_format.txt"
#define VALID "settings_data/valid.txt"


/* PRIVATE INTERFACE */


/* Asserts that all members of a Settings instance are zeroed out. */
static void assertSettingsZero(Settings const* settings)
{
    assert(settings->boardRows == 0);
    assert(settings->boardColumns == 0);
    assert(settings->winRequirement == 0);
}


static void zeroedSettingsTest(void)
{
    Settings settings = zeroedSettings();

    assert(settings.boardRows == 0);
    assert(settings.boardColumns == 0);
    assert(settings.winRequirement == 0);
}


/* Tests readSettings(). */
static void readSettingsTest(void)
{
    int error = 0;
    Settings settings = zeroedSettings();

    printf("Non-existent file test:\n");
    error = 0;
    settings = readSettings(NONEXISTENT_FILE, &error);
    assert(error);
    assertSettingsZero(&settings);

    printf("\n");

    printf("Empty file test:\n");
    error = 0;
    settings = readSettings(EMPTY_FILE, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid line format test:\n");
    error = 0;
    settings = readSettings(INVALID_FORMAT, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid option test:\n");
    error = 0;
    settings = readSettings(INVALID_OPTION, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid options test:\n");
    error = 0;
    settings = readSettings(INVALID_OPTIONS, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Missing option test:\n");
    error = 0;
    settings = readSettings(MISSING_OPTION, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Missing options test:\n");
    error = 0;
    settings = readSettings(MISSING_OPTIONS, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Duplicate option test:\n");
    error = 0;
    settings = readSettings(DUPLICATE_OPTION, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Duplicate options test:\n");
    error = 0;
    settings = readSettings(DUPLICATE_OPTIONS, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid option and missing option test:\n");
    error = 0;
    settings = readSettings(INVALID_OPTION_AND_MISSING, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid format and missing option test:\n");
    error = 0;
    settings = readSettings(INVALID_FORMAT_AND_MISSING, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Duplicate but invalid option format test:\n");
    error = 0;
    settings = readSettings(DUPLICATE_INVALID_FORMAT, &error);
    assert(error);
    assertSettingsZero(&settings);
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


/* Tests validateSettings(). */
static void validateSettingsTest(void)
{
    int result = 0;
    Settings settings = zeroedSettings();

    printf("Invalid board rows:\n");
    settings.boardRows = 0;
    settings.boardColumns = 5;
    settings.winRequirement = 5;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Invalid board columns:\n");
    settings.boardRows = 5;
    settings.boardColumns = 0;
    settings.winRequirement = 5;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Invalid win requirement:\n");
    settings.boardRows = 5;
    settings.boardColumns = 5;
    settings.winRequirement = 0;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Invalid rows, columns, and win requirement:\n");
    settings.boardRows = 0;
    settings.boardColumns = 0;
    settings.winRequirement = 0;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Potentially invalid win requirement:\n");
    settings.boardRows = 2;
    settings.boardColumns = 3;
    settings.winRequirement = 4;
    result = validateSettings(&settings);
    assert(result);
    printf("\n");

    printf("Invalid rows, columns, and potentially invalid win requirement:\n");
    settings.boardRows = 0;
    settings.boardColumns = 0;
    settings.winRequirement = 4;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Valid:\n");
    settings.boardRows = 50;
    settings.boardColumns = 6;
    settings.winRequirement = 10;
    result = validateSettings(&settings);
    assert(result);
    printf("\n");
}



/* PUBLIC INTERFACE */


void settingsTest(void)
{
    moduleTestHeader("settings");

    runUnitTest("zeroedSettings()", zeroedSettingsTest);
    runUnitTest("readSettings()", readSettingsTest);
    runUnitTest("validateSettings()", validateSettingsTest);
}
