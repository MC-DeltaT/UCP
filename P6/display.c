#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINE_MAX 1024


void checkArgs(int argc, char** argv, int* error)
{
    if (!*error && argc != 2)
    {
        printf("Usage: display <array_file_path>\n");
        *error = 1;
    }
}


FILE* openFile(char const* path, int* error)
{
    FILE* file = NULL;

    if (!*error)
    {
        file = fopen(path, "r");
        if (!file)
        {
            perror("Error opening array file");
            *error = 1;
        }
    }

    return file;
}


void closeFile(FILE** file)
{
    if (*file)
    {
        fclose(*file);
        *file = NULL;
    }
}


void readDimensions(FILE* file, char lineBuffer[LINE_MAX],
                    unsigned long* rows, unsigned long* columns, int* error)
{
    /* Read line then parse later, because fscanf will treat newlines the
        same as other whitespace, meaning it can't force the number of rows
        and columns to be on the same line (which we want to do). */

    if (!*error)
    {
        if (!fgets(lineBuffer, LINE_MAX, file))
        {
            if (ferror(file))
            {
                perror("Error reading from array file");
            }
            else
            {
                printf("Error: expected array dimensions, but got EOF.\n");
            }
            *error = 1;
        }
    }

    if (!*error)
    {
        if (2 != sscanf(lineBuffer, "%lu %lu", rows, columns))
        {
            printf("Error: array dimensions format invalid.\n");
            *error = 1;
        }
    }
}


void* allocate(size_t size, int* error)
{
    void* ptr = NULL;

    if (!*error)
    {
        ptr = malloc(size);
        if (!ptr)
        {
            printf("Error: failed to allocate memory of size %lu.\n", size);
            *error = 1;
        }
    }

    return ptr;
}


double** createArray(unsigned long rows, unsigned long columns, int* error)
{
    double** array = NULL;
    unsigned long i;

    if (!*error)
    {
        array = (double**)allocate(rows * sizeof(double*), error);
    }

    if (!*error)
    {
        for (i = 0; i < rows; ++i)
        {
            if (!*error)
            {
                array[i] = (double*)allocate(columns * sizeof(double), error);
            }
            else
            {
                array[i] = NULL;
            }
        }
    }

    return array;
}

void freeArray(double** array, unsigned long rows)
{
    unsigned long i;

    if (array)
    {
        for (i = 0; i < rows; ++i)
        {
            free(array[i]);
        }
    }
    free(array);
}


void parseLine(char* line, unsigned long lineNum, double* row,
               unsigned long columns, int* error)
{
    unsigned long column;
    char* token;
    char* end;
    double element;

    if (!*error)
    {
        column = 0;
        /* Include newline as a delimiter so it handles newline
            included by fgets. */
        token = strtok(line, " \n");
        while (token)
        {
            element = strtod(token, &end);
            /* Token is not a valid double. Either the whole token is invalid,
                or there is a valid double at the start but the rest is
                rubbish (e.g. "1.2sdfglkstr"). */
            if (end == token || (*end != '\0' && !isspace(*end)))
            {
                printf("Error on line %lu: element at column %lu is invalid.\n",
                       lineNum, column + 1ul);
                *error = 1;
            }
            /* Token is valid an column is in range. */
            else if (column < columns)
            {
                row[column] = element;
            }

            token = strtok(NULL, " \n");
            ++column;
        }

        if (column != columns)
        {
            printf("Error on line %lu: expected %lu column(s), but got %lu.\n",
                   lineNum, columns, column);
            *error = 1;
        }
    }
}


void readArray(FILE* file, char lineBuffer[LINE_MAX], double** array,
               unsigned long rows, unsigned long columns, int* error)
{
    char* readRes;
    unsigned long row = 0;

    if (!*error)
    {
        do
        {
            /* Read whole line and then parse after, because again, fscanf
                won't work with newlines correctly. */

            readRes = fgets(lineBuffer, LINE_MAX, file);
            if (readRes)
            {
                if (row < rows)
                {
                    parseLine(lineBuffer, row + 2, array[row], columns, error);
                }
                ++row;
            }
        } while (readRes);

        if (ferror(file))
        {
            perror("Error reading from array file");
            *error = 1;
        }
        else if (row != rows)
        {
            printf("Error: %lu row(s) were specified, but got %lu.\n",
                   rows, row);
            *error = 1;
        }
    }
}


int main(int argc, char** argv)
{
    int error = 0;
    FILE* file = NULL;
    char line[LINE_MAX];
    unsigned long rows = 0;
    unsigned long columns = 0;
    double** array = NULL;


    checkArgs(argc, argv, &error);

    file = openFile(argv[1], &error);

    readDimensions(file, line, &rows, &columns, &error);

    array = createArray(rows, columns, &error);

    readArray(file, line, array, rows, columns, &error);

    closeFile(&file);

    if (!error)
    {
        /* Do stuff with array. */
        printf("Processing array.\n");
    }

    freeArray(array, rows);
    
    return 0;
}
