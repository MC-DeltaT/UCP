#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plot.h"


#define LINE_MAX 1024


/* Program structure:
 * Each function takes an `int* error` flag to check and write the error
 * status. Typically a function won't do anything if the error flag is already
 * set (except for, e.g. freeArray() and closeFile()).
 * On error, the functions will print an error message to stderr, and set the
 * error flag. */


/* Validates the command line parameters. */
void validateArgs(int argc, char** argv, int* error)
{
    if (!*error && argc != 2)
    {
        fprintf(stderr, "Usage: display <array_file_path>\n");
        *error = 1;
    }
}


/* Opens the file with the given path in read text mode.
 * However, if path is "-", instead returns a handle to stdin.
 * If an error occurs or has occurred, returns NULL. */
FILE* openFile(char const* path, int* error)
{
    FILE* file = NULL;

    if (!*error)
    {
        if (strcmp("-", path))
        {
            file = fopen(path, "r");
            if (!file)
            {
                perror("Error opening array file");
                *error = 1;
            }
        }
        else
        {
            file = stdin;
        }
    }

    return file;
}


/* Closes a file pointer and sets it to NULL. */
void closeFile(FILE** file)
{
    if (*file)
    {
        fclose(*file);
        *file = NULL;
    }
}


/* Reads the dimensions (rows & columns) of the array from the first line of
 * the file.
 * lineBuffer is used as space to store the line from the file. */
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
                fprintf(stderr,
                        "Error: expected array dimensions, but got EOF.\n");
            }
            *error = 1;
        }
    }

    if (!*error)
    {
        if (2 != sscanf(lineBuffer, "%lu %lu", rows, columns))
        {
            fprintf(stderr, "Error: array dimensions format invalid.\n");
            *error = 1;
        }
    }
}


/* Same as malloc.
 * If an error occurs or has occured, returns NULL.*/
void* allocate(size_t size, int* error)
{
    void* ptr = NULL;

    if (!*error)
    {
        ptr = malloc(size);
        if (!ptr)
        {
            fprintf(stderr, "Error: failed to allocate memory of size %lu.\n",
                    size);
            *error = 1;
        }
    }

    return ptr;
}


/* Creates a 2D array with out dimension rows and inner dimension columns.
 * If an error has already occurred, returns NULL.
 * If an error occurs allocating the outer dimension of the array, returns NULL.
 * If an error occurs allocating an inner dimension of the array, sets that
 * and subsequent dimensions to NULL, but does not free any other allocated
 * memory. */
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


/* Frees the 2D array with the given outer dimension and sets it to NULL. */
void freeArray(double*** array, unsigned long rows)
{
    unsigned long i;

    if (*array)
    {
        for (i = 0; i < rows; ++i)
        {
            free((*array)[i]);
        }

        free(*array);
        *array = NULL;
    }
}


/* Parses a line of the file as a row, with the expected number of columns,
 * and stores the result to row.
 * If the line contains more columns than expected, they are discarded. */
void parseRow(char* line, unsigned long lineNum, double* row,
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
                fprintf(stderr,
                    "Error on line %lu: element at column %lu is invalid.\n",
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
            fprintf(stderr,
                "Error on line %lu: expected %lu column(s), but got %lu.\n",
                   lineNum, columns, column);
            *error = 1;
        }
    }
}


/* Reads the 2D array from the file and stores the result in array.
 * rows and columns are the expected dimensions of the array. If the file
 * contains more elements than expected, they aer discarded.
 * lineBuffer is used as space to store lines of the file. */
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
                    parseRow(lineBuffer, row + 2, array[row], columns, error);
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
            fprintf(stderr,
                    "Error: %lu row(s) were specified, but got %lu.\n", rows,
                    row);
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

    validateArgs(argc, argv, &error);

    file = openFile(argv[1], &error);

    readDimensions(file, line, &rows, &columns, &error);

    array = createArray(rows, columns, &error);

    readArray(file, line, array, rows, columns, &error);

    closeFile(&file);

    if (!error)
    {
        plot(array, rows, columns);
    }

    freeArray(&array, rows);
    
    return 0;
}
