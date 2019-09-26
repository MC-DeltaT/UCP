#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINE_MAX 1024


typedef struct {
    unsigned day;
    unsigned month;
    unsigned year;
    char* message;
} JournalEntry;



/* Validates the command line parameters. */
void validateArgs(int argc, char** argv, int* error)
{
    if (!*error && argc != 2)
    {
        fprintf(stderr, "Usage: journalreader <entry_index>\n");
        *error = 1;
    }
}


/* Opens the file with the given path in read text mode.
 * If an error occurs or has occurred, returns NULL. */
FILE* openFile(char const* path, int* error)
{
    FILE* file = NULL;

    if (!*error)
    {
        file = fopen(path, "r");
        if (!file)
        {
            perror("Error opening journal file");
            *error = 1;
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


JournalEntry* createEntries(unsigned long count, int* error)
{
    JournalEntry* entries = NULL;
    unsigned long i;

    entries = allocate(count * sizeof(JournalEntry), error);
    if (!*error)
    {
        for (i = 0; i < count; ++i)
        {
            entries[i].day = 0;
            entries[i].month = 0;
            entries[i].year = 0;
            entries[i].message = NULL;
        } 
    }
    return entries;
}


void freeEntries(JournalEntry** entries, unsigned long entryCount)
{
    unsigned long i;

    if (*entries)
    {
        for (i = 0; i < entryCount; ++i)
        {
            free((*entries)[i].message);
            (*entries)[i].message = NULL;
        }
        free(*entries);
        *entries = NULL;
    }
}


/* Reads a line of up to LINE_MAX-1 characters
 * Returns 1 on success, 0 on error or EOF.
 * Increments lineCount if successful. */
int readLine(FILE* file, char line[LINE_MAX], unsigned long* lineCount,
             int* error)
{
    int res = 0;
    char* newline;

    if (!*error)
    {
        if (fgets(line, LINE_MAX, file))
        {
            newline = strchr(line, '\n');
            if (newline)
            {
                *newline = '\0';
                ++*lineCount;
                res = 1;
            }
            else
            {
                fprintf(stderr, "Error on line %lu: line too long.\n",
                        *lineCount + 1ul);
                *error = 1;
            }
        }
        else
        {
            if (ferror(file))
            {
                perror("Error reading journal file");
                *error = 1;
            }
        }
    }

    return res;
}


void parseDate(char const* line, unsigned long lineNum,
               JournalEntry* entry, int* error)
{
    int res;
    int n;

    if (!*error)
    {
        res = sscanf(line, "%u/%u/%u %n", &entry->day, &entry->month,
                        &entry->year, &n);
        if (res != 3 || n != strlen(line))
        {
            fprintf(stderr, "Error on line %lu: date format incorrect.\n",
                    lineNum);
            *error = 1;
        }
    }
}


void parseMessage(char const* line, JournalEntry* entry, int* error)
{
    size_t len;

    if (!*error)
    {
        len = strlen(line);
        entry->message = allocate(len + 1ul, error);
        if (!*error)
        {
            memcpy(entry->message, line, len + 1ul);
        }
    }
}


void readEntries(FILE* file, char lineBuffer[LINE_MAX], JournalEntry* entries,
                 unsigned long entryCount, unsigned long* lineCount, int* error)
{
    unsigned long i = 0;

    if (!*error)
    {
        while (!*error && !feof(file) && i < entryCount)
        {
            if (readLine(file, lineBuffer, lineCount, error))
            {
                parseDate(lineBuffer, *lineCount, entries + i, error);
                if (readLine(file, lineBuffer, lineCount, error))
                {
                    parseMessage(lineBuffer, entries + i, error);
                    ++i;
                }
                else if (feof(file))
                {
                    fprintf(stderr,
                "Error: expected entry message on line %lu, but got EOF.\n",
                            *lineCount + 1);
                    *error = 1;
                }
            }
        }

        if (!*error && i != entryCount)
        {
            fprintf(stderr, "Error: %lu entries specified, but got %lu.\n",
                    entryCount, i);
            *error = 1;
        }
    }
}


unsigned long parseUL(char const* str, int* error)
{
    long res = 0;
    char* end;

    if (!*error)
    {
        res = strtol(str, &end, 10);
        if (end == str || (*end != '\0' && !isspace(*end)) || res < 0)
        {
            *error = 1;
        }
        
    }

    return res;
}


unsigned long readEntryCount(FILE* file, char lineBuffer[LINE_MAX],
                             unsigned long* lineCount, int* error)
{
    unsigned long entries = 0;

    if (!*error)
    {
        if (readLine(file, lineBuffer, lineCount, error))
        {
            entries = parseUL(lineBuffer, error);
            if (*error)
            {
                fprintf(stderr, "Error on line %lu: entry count is invalid.\n",
                        *lineCount);
                *error = 1;
            }
        }
        else if (feof(file))
        {
            fprintf(stderr,
                    "Error on line %lu: expected entry count, but got EOF.\n",
                    *lineCount);
            *error = 1;
        }
    }

    return entries;
}


void printEntry(JournalEntry const* entries, unsigned long entryCount,
                unsigned long idx, int* error)
{
    JournalEntry const* entry;

    if (!*error)
    {
        if (idx < entryCount)
        {
            entry = entries + idx;
            printf("%u-%u-%u: %s\n", entry->year, entry->month, entry->day,
                   entry->message);
        }
        else
        {
            fprintf(stderr, "Error: entry index must be <%lu, but got %lu.\n",
                    entryCount, idx);
            *error = 1;
        }
    }
}


int main(int argc, char** argv)
{
    static char const JOURNAL_PATH[] = "journal.txt";

    int error = 0;
    FILE* file = NULL;
    char line[LINE_MAX] = {0};
    unsigned long lineCount = 0;
    unsigned long entryCount = 0;
    JournalEntry* entries = NULL;
    unsigned long entryIdx = 0;

    validateArgs(argc, argv, &error);

    file = openFile(JOURNAL_PATH, &error);

    entryCount = readEntryCount(file, line, &lineCount, &error);

    entries = createEntries(entryCount, &error);

    readEntries(file, line, entries, entryCount, &lineCount, &error);

    /* If error is set, argv[1] might be out of bounds, so technically can't
        dereference argv+1 even though we won't use it anyway. */
    if (!error)
    {
        entryIdx = parseUL(argv[1], &error);
    }

    printEntry(entries, entryCount, entryIdx, &error);

    closeFile(&file);

    freeEntries(&entries, entryCount);

    return 0;
}
