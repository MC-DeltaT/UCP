#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "randomarray.h"


/* Program structure:
 * Each function takes an `int* error` flag to check and write the error
 * status. Typically a function won't do anything if the error flag is already
 * set (except for, e.g. freeArray() and closeFile()).
 * On error, the functions will print an error message to stderr, and set the
 * error flag. */


void validateArgs(int argc, char** argv, int* error)
{
    if (!*error)
    {
        if (argc != 4)
        {
            fprintf(stderr,
                    "Usage: generate <output_file_path> <rows> <columns>\n");
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


void parseDimensions(char** argv, unsigned long* rows, unsigned long* columns,
                     int* error)
{
    long rowsTmp;
    long columnsTmp;
    char* end;

    if (!*error)
    {
        /* strtoul actually allows negative values, which then wrap around
            to large positive values. We don't want that, so use strtol and
            then manually stop negative values. */
        rowsTmp = strtol(argv[2], &end, 10);
        /* String is not a valid long. Either the whole string is
            invalid, or there is a valid long at the start but the
            rest is rubbish (e.g. "12sdfglkstr"). */
        if (end == argv[2] || (*end != '\0' && !isspace(*end)))
        {
            fprintf(stderr, "Error: row specification is invalid.\n");
            *error = 1;
        }
        else if (rowsTmp <= 0)
        {
            fprintf(stderr, "Error: rows must be >0.\n");
            *error = 1;
        }
        else
        {
            *rows = rowsTmp;
        }

        columnsTmp = strtol(argv[3], &end, 10);
        if (end == argv[3] || (*end != '\0' && !isspace(*end)))
        {
            fprintf(stderr, "Error: column specification is invalid.\n");
            *error = 1;
        }
        else if (columnsTmp <= 0)
        {
            fprintf(stderr, "Error: columns must be >0.\n");
            *error = 1;
        }
        else
        {
            *columns = columnsTmp;
        }
    }
}


/* Opens the file with the given path in write text mode.
 * However, if path is "-", instead returns a handle to stdout.
 * If an error occurs or has occurred, returns NULL. */
FILE* openFile(char const* path, int* error)
{
    FILE* file = NULL;

    if (!*error)
    {
        if (strcmp("-", path))
        {
            file = fopen(path, "w");
            if (!file)
            {
                perror("Error opening output file");
                *error = 1;
            }
        }
        else
        {
            file = stdout;
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


void writeDimensions(FILE* file, unsigned long rows, unsigned long columns,
                     int* error)
{
    if (!*error)
    {
        if (0 > fprintf(file, "%lu %lu\n", rows, columns))
        {
            perror("Error writing to output file");
            *error = 1;
        }
    }
}


void writeArray(FILE* file, double** array, unsigned long rows,
                unsigned long columns, int* error)
{
    /* Format for all columns except last - trailing space. */
    static char const NORMAL_FORMAT[] = "%f ";
    /* Format for last column only - no trailing space. */
    static char const LAST_FORMAT[] = "%f";
    unsigned long i;
    unsigned long j;
    char const* format;

    if (!*error)
    {
        i = 0;
        while (i < rows && !*error)
        {
            j = 0;
            format = NORMAL_FORMAT;
            while (j < columns && !*error)
            {
                if (j + 1 == columns)
                {
                    format = LAST_FORMAT;
                }

                if (0 > fprintf(file, format, array[i][j]))
                {
                    perror("Error writing to output file");
                    *error = 1;
                }

                ++j;
            }
            fprintf(file, "\n");
            ++i;
        }
    }
}


int main(int argc, char** argv)
{
    int error = 0;
    FILE* file = NULL;
    unsigned long rows = 0;
    unsigned long columns = 0;
    double** array = NULL;

    validateArgs(argc, argv, &error);

    parseDimensions(argv, &rows, &columns, &error);

    array = createArray(rows, columns, &error);

    if (!error)
    {
        randomArray(array, rows, columns, 0);
    }

    file = openFile(argv[1], &error);

    writeDimensions(file, rows, columns, &error);

    writeArray(file, array, rows, columns, &error);

    closeFile(&file);

    freeArray(&array, rows);

    return 0;
}
