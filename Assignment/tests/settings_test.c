/* Unit tests for the settings module. */

#include "settings_test.h"

#include "common.h"
#include "../settings.h"

#include <assert.h>
#include <stdio.h>


#define NONEXISTENT_FILE "test_settings/nonexistent_file.txt"
#define EMPTY_FILE "test_settings/empty.txt"
#define INVALID_FORMAT "test_settings/invalid_format.txt"
#define INVALID_OPTION "test_settings/invalid_option.txt"
#define INVALID_OPTIONS "test_settings/invalid_options.txt"
#define MISSING_OPTION "test_settings/missing_option.txt"
#define MISSING_OPTIONS "test_settings/missing_options.txt"
#define DUPLICATE_OPTION "test_settings/duplicate_option.txt"
#define DUPLICATE_OPTIONS "test_settings/duplicate_options.txt"
#define INVALID_OPTION_AND_MISSING "test_settings/invalid_option_missing.txt"
#define INVALID_FORMAT_AND_MISSING "test_settings/invalid_format_missing.txt"
#define DUPLICATE_INVALID_FORMAT "test_settings/duplicate_invalid_format.txt"
#define LINE_TOO_LONG "test_settings/line_too_long.txt"
#define LAST_LINE_TOO_LONG "test_settings/last_line_too_long.txt"
#define TRAILING_RUBBISH "test_settings/trailing_rubbish.txt"
#define VALID "test_settings/valid.txt"
#define VALID_NO_NEWLINE "test_settings/valid_no_newline.txt"
#define VALID_EXTRA_SPACE "test_settings/valid_extra_space.txt"


/* PRIVATE INTERFACE */


/* Asserts that all members of a Settings instance are zeroed out. */
static void assertSettingsZero(Settings const* settings)
{
    assert(settings->n == 0);
    assert(settings->m == 0);
    assert(settings->k == 0);
}


/* Tests zeroedSettings(). */
static void zeroedSettingsTest(void)
{
    Settings settings = zeroedSettings();
    assertSettingsZero(&settings);
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

    printf("Line too long test:\n");
    error = 0;
    settings = readSettings(LINE_TOO_LONG, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Last line too long test:\n");
    error = 0;
    settings = readSettings(LAST_LINE_TOO_LONG, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Valid but trailing rubbish each line test:\n");
    error = 0;
    settings = readSettings(TRAILING_RUBBISH, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Valid file test:\n");
    error = 0;
    settings = readSettings(VALID, &error);
    assert(!error);
    assert(settings.n == 10);
    assert(settings.m == 45);
    assert(settings.k == 6);
    printf("\n");

    printf("Valid file without final newline test:\n");
    error = 0;
    settings = readSettings(VALID_NO_NEWLINE, &error);
    assert(!error);
    assert(settings.n == 10);
    assert(settings.m == 45);
    assert(settings.k == 6);
    printf("\n");

    printf("Valid file with extra space test:\n");
    error = 0;
    settings = readSettings(VALID_EXTRA_SPACE, &error);
    assert(!error);
    assert(settings.n == 11);
    assert(settings.m == 10);
    assert(settings.k == 7);
    printf("\n");
}


/* Tests validateSettings(). */
static void validateSettingsTest(void)
{
    int result = 0;
    Settings settings = zeroedSettings();

    printf("Invalid N:\n");
    settings.n = 0;
    settings.m = 5;
    settings.k = 5;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Invalid M:\n");
    settings.n = 5;
    settings.m = 0;
    settings.k = 5;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Invalid K:\n");
    settings.n = 5;
    settings.m = 5;
    settings.k = 0;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Invalid M, N and K:\n");
    settings.n = 0;
    settings.m = 0;
    settings.k = 0;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Potentially invalid K:\n");
    settings.n = 2;
    settings.m = 3;
    settings.k = 4;
    result = validateSettings(&settings);
    assert(result);
    printf("\n");

    printf("Invalid M, N, and potentially invalid K:\n");
    settings.n = 0;
    settings.m = 0;
    settings.k = 4;
    result = validateSettings(&settings);
    assert(!result);
    printf("\n");

    printf("Valid:\n");
    settings.n = 50;
    settings.m = 6;
    settings.k = 10;
    result = validateSettings(&settings);
    assert(result);
    printf("\n");
}


/* Tests writeSettings(). */
static void writeSettingsTest(void)
{
    Settings settings = zeroedSettings();
    settings.n = 10;
    settings.m = 1;
    settings.k = 5;
    writeSettings(stdout, &settings);
}



/* PUBLIC INTERFACE */


void settingsTest(void)
{
    moduleTestHeader("settings");

    runUnitTest("zeroedSettings()", zeroedSettingsTest);
    runUnitTest("readSettings()", readSettingsTest);
    runUnitTest("validateSettings()", validateSettingsTest);
    runUnitTest("writeSettings()", writeSettingsTest);
}
