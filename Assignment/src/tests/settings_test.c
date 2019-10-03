/* Unit tests for the settings module. */

#include "settings_test.h"

#include "common.h"
#include "../main/settings.h"

#include <assert.h>
#include <stdio.h>


/* PRIVATE INTERFACE */


#define TEST_FILE_DIR "test_data/settings/"

#define NONEXISTENT_FILE TEST_FILE_DIR "nonexistent_file.txt"
#define EMPTY_FILE TEST_FILE_DIR "empty.txt"
#define INVALID_FORMAT TEST_FILE_DIR "invalid_format.txt"
#define INVALID_OPTION TEST_FILE_DIR "invalid_option.txt"
#define INVALID_OPTIONS TEST_FILE_DIR "invalid_options.txt"
#define MISSING_OPTION TEST_FILE_DIR "missing_option.txt"
#define MISSING_OPTIONS TEST_FILE_DIR "missing_options.txt"
#define DUPLICATE_OPTION TEST_FILE_DIR "duplicate_option.txt"
#define DUPLICATE_OPTIONS TEST_FILE_DIR "duplicate_options.txt"
#define INVALID_OPTION_AND_MISSING TEST_FILE_DIR "invalid_option_missing.txt"
#define INVALID_FORMAT_AND_MISSING TEST_FILE_DIR "invalid_format_missing.txt"
#define DUPLICATE_INVALID_FORMAT TEST_FILE_DIR "duplicate_invalid_format.txt"
#define LINE_TOO_LONG TEST_FILE_DIR "line_too_long.txt"
#define LAST_LINE_TOO_LONG TEST_FILE_DIR "last_line_too_long.txt"
#define TRAILING_RUBBISH TEST_FILE_DIR "trailing_rubbish.txt"
#define VALID TEST_FILE_DIR "valid.txt"
#define VALID_NO_NEWLINE TEST_FILE_DIR "valid_no_newline.txt"
#define VALID_EXTRA_SPACE TEST_FILE_DIR "valid_extra_space.txt"
#define VALID_BLANK_LINES TEST_FILE_DIR "valid_blank_lines.txt"


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

    printf("Non-existent file:\n");
    error = 0;
    settings = readSettings(NONEXISTENT_FILE, &error);
    assert(error);
    assertSettingsZero(&settings);

    printf("\n");

    printf("Empty file:\n");
    error = 0;
    settings = readSettings(EMPTY_FILE, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid line format:\n");
    error = 0;
    settings = readSettings(INVALID_FORMAT, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid option:\n");
    error = 0;
    settings = readSettings(INVALID_OPTION, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid options:\n");
    error = 0;
    settings = readSettings(INVALID_OPTIONS, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Missing option:\n");
    error = 0;
    settings = readSettings(MISSING_OPTION, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Missing options:\n");
    error = 0;
    settings = readSettings(MISSING_OPTIONS, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Duplicate option:\n");
    error = 0;
    settings = readSettings(DUPLICATE_OPTION, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Duplicate options:\n");
    error = 0;
    settings = readSettings(DUPLICATE_OPTIONS, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid option and missing option:\n");
    error = 0;
    settings = readSettings(INVALID_OPTION_AND_MISSING, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Invalid format and missing option:\n");
    error = 0;
    settings = readSettings(INVALID_FORMAT_AND_MISSING, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Duplicate but invalid option format:\n");
    error = 0;
    settings = readSettings(DUPLICATE_INVALID_FORMAT, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Line too long:\n");
    error = 0;
    settings = readSettings(LINE_TOO_LONG, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Last line too long:\n");
    error = 0;
    settings = readSettings(LAST_LINE_TOO_LONG, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Valid but trailing rubbish each line:\n");
    error = 0;
    settings = readSettings(TRAILING_RUBBISH, &error);
    assert(error);
    assertSettingsZero(&settings);
    printf("\n");

    printf("Valid file:\n");
    error = 0;
    settings = readSettings(VALID, &error);
    assert(!error);
    assert(settings.n == 10);
    assert(settings.m == 45);
    assert(settings.k == 6);
    printf("\n");

    printf("Valid file without final newline:\n");
    error = 0;
    settings = readSettings(VALID_NO_NEWLINE, &error);
    assert(!error);
    assert(settings.n == 10);
    assert(settings.m == 45);
    assert(settings.k == 6);
    printf("\n");

    printf("Valid file with extra space:\n");
    error = 0;
    settings = readSettings(VALID_EXTRA_SPACE, &error);
    assert(!error);
    assert(settings.n == 11);
    assert(settings.m == 10);
    assert(settings.k == 7);
    printf("\n");

    printf("Valid file with blank lines:\n");
    error = 0;
    settings = readSettings(VALID_BLANK_LINES, &error);
    assert(!error);
    assert(settings.n == 3);
    assert(settings.m == 10);
    assert(settings.k == 4);
    printf("\n");
}


/* Tests validateMSetting(). */
static void validateMSettingTest(void)
{
    int result = 0;

    printf("Invalid:\n");
    result = validateMSetting(0);
    assert(!result);
    printf("\n");

    printf("Valid:\n");
    result = validateMSetting(1);
    assert(result);
    printf("\n");
}


/* Tests validateNSetting(). */
static void validateNSettingTest(void)
{
    int result = 0;

    printf("Invalid:\n");
    result = validateNSetting(0);
    assert(!result);
    printf("\n");

    printf("Valid:\n");
    result = validateNSetting(1);
    assert(result);
    printf("\n");
}


/* Tests validateKSetting(). */
static void validateKSettingTest(void)
{
    int result = 0;

    printf("Invalid, warnings off:\n");
    result = validateKSetting(0, 0);
    assert(!result);
    printf("\n");

    printf("Invalid, warnings on:\n");
    result = validateKSetting(0, 1);
    assert(!result);
    printf("\n");

    printf("Potentially invalid, warnings off:\n");
    result = validateKSetting(1, 0);
    assert(result);
    printf("\n");

    printf("Potentially invalid, warnings on:\n");
    result = validateKSetting(1, 1);
    assert(result);
    printf("\n");

    printf("Valid, warnings off:\n");
    result = validateKSetting(2, 0);
    assert(result);
    printf("\n");

    printf("Valid, warnings on:\n");
    result = validateKSetting(2, 1);
    assert(result);
    printf("\n");
}


/* Tests validateSettingsCombo(). */
static void validateSettingsComboTest(void)
{
    int result = 0;
    Settings settings = zeroedSettings();

    printf("Potentially invalid K (>M>=N), warnings off:\n");
    settings.n = 5;
    settings.m = 5;
    settings.k = 6;
    result = validateSettingsCombo(&settings, 0);
    assert(result);
    printf("\n");

    printf("Potentially invalid K (>M>=N), warnings on:\n");
    settings.n = 5;
    settings.m = 5;
    settings.k = 6;
    result = validateSettingsCombo(&settings, 1);
    assert(result);
    printf("\n");

    printf("Valid, warnings off:\n");
    settings.n = 5;
    settings.m = 6;
    settings.k = 3;
    result = validateSettingsCombo(&settings, 1);
    assert(result);
    printf("\n");

    printf("Valid, warnings on:\n");
    settings.n = 5;
    settings.m = 6;
    settings.k = 3;
    result = validateSettingsCombo(&settings, 0);
    assert(result);
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
    result = validateSettings(&settings, 1);
    assert(!result);
    printf("\n");

    printf("Invalid M:\n");
    settings.n = 5;
    settings.m = 0;
    settings.k = 5;
    result = validateSettings(&settings, 1);
    assert(!result);
    printf("\n");

    printf("Invalid K (==0):\n");
    settings.n = 5;
    settings.m = 5;
    settings.k = 0;
    result = validateSettings(&settings, 1);
    assert(!result);
    printf("\n");

    printf("Potentially invalid K (==1):\n");
    settings.n = 5;
    settings.m = 5;
    settings.k = 1;
    result = validateSettings(&settings, 1);
    assert(result);
    printf("\n");

    printf("Potentially invalid K (>M>=N):\n");
    settings.n = 5;
    settings.m = 5;
    settings.k = 6;
    result = validateSettings(&settings, 1);
    assert(result);
    printf("\n");

    printf("Invalid M, N and potentially invalid K (==1):\n");
    settings.n = 0;
    settings.m = 0;
    settings.k = 1;
    result = validateSettings(&settings, 1);
    assert(!result);
    printf("\n");

    printf("Invalid M, N and potentially invalid K (>1):\n");
    settings.n = 0;
    settings.m = 0;
    settings.k = 2;
    result = validateSettings(&settings, 1);
    assert(!result);
    printf("\n");

    printf("Invalid M, N and K:\n");
    settings.n = 0;
    settings.m = 0;
    settings.k = 0;
    result = validateSettings(&settings, 1);
    assert(!result);
    printf("\n");

    printf("Valid:\n");
    settings.n = 50;
    settings.m = 6;
    settings.k = 10;
    result = validateSettings(&settings, 1);
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
    runUnitTest("validateMSetting()", validateMSettingTest);
    runUnitTest("validateNSetting()", validateNSettingTest);
    runUnitTest("validateKSetting()", validateKSettingTest);
    runUnitTest("validateSettings()", validateSettingsTest);
    runUnitTest("validateSettingsCombo()", validateSettingsComboTest);
    runUnitTest("writeSettings()", writeSettingsTest);
}
