#include "interface.h"
#include "settings.h"

#include <stdio.h>


void validateArgs(int argc, char* argv[], int* error)
{
    if (!*error && argc != 2)
    {
        fprintf(stderr, "Usage: tictactoe <settings_file_path>\n");
        *error = 1;
    }
}


int main(int argc, char* argv[])
{
    int error = 0;
    Settings settings;

    validateArgs(argc, argv, &error);

    /* If error is set, then maybe argc == 0 and accessing argv[1] is UB.*/
    if (!error)
    {
        settings = readSettings(argv[1], &error);
    }

    if (!error)
    {
        mainMenu(&settings);
    }

    return 0;
}
