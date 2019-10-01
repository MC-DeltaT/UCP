/* Miscellaneous unit testing utilities. */

#include "common.h"

#include <stdio.h>


/* PUBLIC INTERFACE */


void moduleTestHeader(char const* moduleName)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s module test\n", moduleName);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
}


void runUnitTest(char const* unitName, void (*testCase)(void))
{
    unitTestHeader(unitName);
    testCase();
    unitTestFooter();
}


void unitTestHeader(char const* unitName)
{
    printf("%s unit test\n", unitName);
    printf("---------------------------\n");
}


void unitTestFooter(void)
{
    printf("---------------------------\n");
    printf("\n");
}
