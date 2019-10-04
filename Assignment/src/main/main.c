/* Program entry point. */

#include "interface.h"
#include "log.h"
#include "settings.h"

#include <stdio.h>


int validateArgs(int argc, char* argv[])
{
    int res = 1;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: tictactoe <settings_file_path>\n");
        res = 0;
    }

    return res;
}


int main(int argc, char* argv[])
{
    int error = 0;
    Settings settings = zeroedSettings();

    error = !validateArgs(argc, argv);

    if (!error)
    {
        settings = readSettings(argv[1], &error);
    }

    if (!error)
    {
        error = !validateSettings(&settings, 1);
    }

    if (!error)
    {
        mainMenu(&settings);
    }

    freeGameLogs();

    return 0;
}
