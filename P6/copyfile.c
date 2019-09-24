#include <stdio.h>


int main(int argc, char** argv)
{
    int error = 0;
    FILE* inputFile = NULL;
    FILE* outputFile = NULL;
    int inputChar;
    int writeStatus;

    if (argc != 3)
    {
        printf("Usage: copyfile <input_file_path> <output_file_path>\n");
        error = 1;
    }

    if (!error)
    {
        inputFile = fopen(argv[1], "rb");
        if (!inputFile)
        {
            perror("Error opening input file");
            error = 1;
        }
    }

    if (!error)
    {
        outputFile = fopen(argv[2], "wb");
        if (!outputFile)
        {
            perror("Error opening output file");
            error = 1;
        }
    }

    if (!error)
    {
        do
        {
            inputChar = fgetc(inputFile);
            if (inputChar != EOF)
            {
                writeStatus = fputc(inputChar, outputFile);
            }
        } while (inputChar != EOF && writeStatus != EOF);

        if (ferror(inputFile))
        {
            perror("Error reading input file");
            error = 1;
        }
        if (ferror(outputFile))
        {
            perror("Error writing output file");
            error = 1;
        }
    }

    if (inputFile)
    {
        fclose(inputFile);
        inputFile = NULL;
    }
    if (outputFile)
    {
        fclose(outputFile);
        outputFile = NULL;
    }

    return 0;
}
