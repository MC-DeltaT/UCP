/* Unit tests for the common module. */

#include "common_test.h"

#include "common.h"
#include "../main/common.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


/* PRIVATE INTERFACE */


#define TEST_FILE_DIR "test_data/readUntil/"

#define CONSECUTIVE_DELIM TEST_FILE_DIR "consecutive_delim.txt"
#define DELIM_AT_END TEST_FILE_DIR "delim_at_end.txt"
#define DELIM_AT_START TEST_FILE_DIR "delim_at_start.txt"
#define DELIM_IN_MIDDLE TEST_FILE_DIR "delim_in_middle.txt"
#define EMPTY TEST_FILE_DIR "empty.txt"
#define MULTIPLE_DELIM TEST_FILE_DIR "multiple_delim.txt"
#define NO_DELIM TEST_FILE_DIR "no_delim.txt"


/* Tests playerToChar(). */
static void playerToCharTest(void)
{
    char xChar = playerToChar(PLAYER_X);
    char oChar = playerToChar(PLAYER_O);

    assert(isprint(xChar) && !isspace(xChar));
    assert(isprint(oChar) && !isspace(oChar));
    assert(xChar != oChar);
}


/* Tests isWhitespace(). */
static void isWhitespaceTest(void)
{
    assert(isWhitespace(""));

    assert(isWhitespace(" "));
    assert(isWhitespace("\t"));
    assert(isWhitespace("\n"));
    assert(isWhitespace("\r"));

    assert(isWhitespace("  "));
    assert(isWhitespace(" \t\n"));
    assert(isWhitespace("\n \r"));
    assert(isWhitespace("\r\n\t "));
    assert(isWhitespace("           \t \n     \n\n\n\n \r"));

    assert(!isWhitespace("a"));
    assert(!isWhitespace("0"));
    assert(!isWhitespace("_"));
    assert(!isWhitespace("~"));

    assert(!isWhitespace("hello"));
    assert(!isWhitespace("12345"));
    assert(!isWhitespace("____*^#"));
    assert(!isWhitespace("~!@$^%@"));

    assert(!isWhitespace(" a"));
    assert(!isWhitespace(" 0"));
    assert(!isWhitespace(" _"));
    assert(!isWhitespace(" ~"));

    assert(!isWhitespace(" a "));
    assert(!isWhitespace(" 0 "));
    assert(!isWhitespace(" _ "));
    assert(!isWhitespace(" ~ "));

    assert(!isWhitespace("hello world "));
    assert(!isWhitespace("12345  6789 \n"));
    assert(!isWhitespace("\t_  _ _  \n  ~* ^# \r^%*()"));
}


/* Reads up to bufSize - 1 characters from file into buf, and sets null
   terminator. Returns the number of characters read. */
static size_t readTextFile(char* buf, size_t bufSize, FILE* file)
{
    size_t read = fread(buf, 1, bufSize - 1, file);
    buf[read] = '\0';
    return read;
}


/* Tests readUntil(). */
static void readUntilTest(void)
{
    FILE* file = NULL;
#define BUSIZE 1024ul
    char buf[1024ul] = {0};

    file = fopen(CONSECUTIVE_DELIM, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(readTextFile(buf, sizeof buf, file));
    assert(feof(file));
    assert(strcmp("\n\nworld", buf) == 0);
    fclose(file);
    file = NULL;

    file = fopen(DELIM_AT_END, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(readTextFile(buf, sizeof buf, file));
    assert(feof(file));
    assert(strcmp("\n", buf) == 0);
    fclose(file);
    file = NULL;

    file = fopen(DELIM_AT_END, "r");
    assert(file);
    readUntil(file, '\n', 1);
    assert(fgetc(file) == EOF);
    fclose(file);
    file = NULL;

    file = fopen(DELIM_AT_START, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(readTextFile(buf, sizeof buf, file));
    assert(feof(file));
    assert(strcmp("\nhello world", buf) == 0);
    fclose(file);
    file = NULL;

    file = fopen(DELIM_AT_START, "r");
    assert(file);
    readUntil(file, '\n', 1);
    assert(readTextFile(buf, sizeof buf, file));
    assert(feof(file));
    assert(strcmp("hello world", buf) == 0);
    fclose(file);
    file = NULL;

    file = fopen(DELIM_IN_MIDDLE, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(readTextFile(buf, sizeof buf, file));
    assert(feof(file));
    assert(strcmp("\nworld", buf) == 0);
    fclose(file);
    file = NULL;

    file = fopen(DELIM_IN_MIDDLE, "r");
    assert(file);
    readUntil(file, '\n', 1);
    assert(readTextFile(buf, sizeof buf, file));
    assert(feof(file));
    assert(strcmp("world", buf) == 0);
    fclose(file);
    file = NULL;

    file = fopen(EMPTY, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(feof(file));
    fclose(file);
    file = NULL;

    file = fopen(EMPTY, "r");
    assert(file);
    readUntil(file, '\n', 1);
    assert(feof(file));
    fclose(file);
    file = NULL;

    file = fopen(MULTIPLE_DELIM, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(readTextFile(buf, sizeof buf, file));
    assert(strcmp("\nworld\nfoo\nbar\n", buf) == 0);
    assert(feof(file));
    fclose(file);
    file = NULL;

    file = fopen(MULTIPLE_DELIM, "r");
    assert(file);
    readUntil(file, '\n', 1);
    assert(readTextFile(buf, sizeof buf, file));
    assert(strcmp("world\nfoo\nbar\n", buf) == 0);
    assert(feof(file));
    fclose(file);
    file = NULL;

    file = fopen(NO_DELIM, "r");
    assert(file);
    readUntil(file, '\n', 0);
    assert(feof(file));
    fclose(file);
    file = NULL;

    file = fopen(NO_DELIM, "r");
    assert(file);
    readUntil(file, '\n', 1);
    assert(feof(file));
    fclose(file);
    file = NULL;
}



/* PUBLIC INTERFACE */


void commonTest(void)
{
    moduleTestHeader("common");

    runUnitTest("playerToChar()", playerToCharTest);
    runUnitTest("isWhitespace()", isWhitespaceTest);
    runUnitTest("readUntil()", readUntilTest);
}
