#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


void printError(char *errorString);
void appendToFile(char *fileName, char buffer[1]);
void printStandard(char *string);

int main(int argc, char *argv[])
{
    int i, infile, outfile, opt;
    int spaceCount = 0;
    char buffer[1];
    int numberOfWords = 10;
    bool append = false;

    char *fileName = "sample.txt";
    char *outfileName;

    // https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
    while ((opt = getopt(argc, argv, ":a:n:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            append = true;
            outfileName = (char *)malloc(strlen(optarg) + 1);
            outfileName = optarg;
            break;
        case 'n':
            numberOfWords = atoi(optarg);
            break;
        case '?':
            printError("Unknown option\n");
            break;
        case ':':
            printError("Missing an argument\n");
            exit(1);
            break;
        }
    }

    /* Get all of the non-option arguments */
    if (optind < argc)
    {
        while (optind < argc)
        {
            fileName = (char *)malloc(strlen(argv[optind]) + 1);
            if (fileName == NULL)
            {
                printError("Memory allocation error\n");
            }
            strcpy(fileName, argv[optind]);
            optind++;
        }
    }

    if ((infile = open(fileName, O_RDONLY)) < 0)
    {
        printError("The file could not be opened\n");
    }

    while (read(infile, buffer, 1) > 0 && spaceCount < numberOfWords)
    {
        if (strcmp(buffer, " ") == 0)
        {
            spaceCount++;
        }

        if (append)
        {
            appendToFile(outfileName, buffer);
        }
        else
        {
            write(1, buffer, 1);
        }
    }

    if (append)
    {
        printStandard("Append successful\n");
    }
    else
    {
        printStandard("\n");
    }

    close(infile);

    return 0;
}

void printError(char *errorString)
{
    write(2, errorString, strlen(errorString));
    exit(1);
}

void printStandard(char *string)
{
    write(1, string, strlen(string));
}

void appendToFile(char *fileName, char buffer[1])
{
    int outfile;
    if ((outfile = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0664)) < 0)
    {
        exit(1);
    }
    write(outfile, buffer, 1);
}