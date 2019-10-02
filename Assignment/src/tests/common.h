/* Miscellaneous unit testing utilities. */

#ifndef TESTS_COMMON_H
#define TESTS_COMMON_H


void moduleTestHeader(char const* moduleName);

void runUnitTest(char const* unitName, void (*testCase)(void));

void unitTestHeader(char const* unitName);

void unitTestFooter(void);


#endif
