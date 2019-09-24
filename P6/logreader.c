#include <stdio.h>
#include <string.h>


void processEntry(char const month[4], unsigned day, unsigned hour,
    unsigned minute, unsigned second, char const* process, char const* message)
{
    unsigned long sinceMidnight;

    if (strstr(message, "fail"))
    {
        sinceMidnight = second;
        sinceMidnight += minute * 60ul;
        sinceMidnight += hour * 3600ul;
        printf("%lu: %s\n", sinceMidnight, message);
    }
}


int main(int argc, char** argv)
{
    int error = 0;
    FILE* file = NULL;
    int readRes;
    char month[4];
    unsigned day;
    unsigned hour;
    unsigned minute;
    unsigned second;
    char process[128];
    char message[1024];

    if (argc != 2)
    {
        printf("Usage: logreader <log_file_path>\n");
        error = 1;
    }

    if (!error)
    {
        file = fopen(argv[1], "r");
        if (!file)
        {
            perror("Error opening log file");
            error = 1;
        }
    }

    if (!error)
    {
        do
        {
            readRes = fscanf(file, "%3s %u %u:%u:%u %127[^:]: %1023[^\n]\n",
                month, &day, &hour, &minute, &second, process, message);
            /* Successfully parsed all the arguments. */
            if (readRes == 7)
            {
                processEntry(month, day, hour, minute, second, process, message);
            }
            /* Line wasn't formatted correctly. */
            else if (readRes != EOF)
            {
                /* Consume rest of line. */
                do
                {
                    readRes = fgetc(file);
                } while (readRes != '\n' && readRes != EOF);
            }
        } while (readRes != EOF);

        if (ferror(file))
        {
            perror("Error reading from log file");
            error = 1;
        }
    }

    if (file)
    {
        fclose(file);
        file = NULL;
    }

    return 0;
}
