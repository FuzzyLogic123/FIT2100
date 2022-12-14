/**
 * @file fileutil.c
 * @author Patrick Edwards (ID: 32460929)
 * @brief Creates a file utility to assist reading files
 * @version 0.1
 * @date 2022-08-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include "fileutil.h"

int main(int argc, char *argv[])
{
    int i, infile, outfile, opt;
    int spaceCount = 0;
    char buffer;
    char previousBuffer = ' '; // record the previous charcter that has been read
    int numberOfWords = 10;
    bool append = false; // import boolean library to use true or false

    char *fileName = "sample.txt"; // set the default file name
    char *outfileName;

    while ((opt = getopt(argc, argv, ":a:n:")) != -1) // use build in get opt to read flags from input (see linux man page)
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
        case '?': // flag is unknown
            printError("Unknown option\n");
            break;
        case ':': // argument is required and not provided
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

    while (read(infile, &buffer, 1) > 0 && spaceCount < numberOfWords)
    {
        if (isDelimiter(buffer) && !isDelimiter(previousBuffer)) // check if there is two delimiters in a row
        {
            spaceCount++;
        }

        if (append)
        {
            appendToFile(outfileName, &buffer);
        }
        else
        {
            write(1, &buffer, 1);
        }
        previousBuffer = buffer;
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

void appendToFile(char *fileName, char *buffer)
{
    int outfile;
    if ((outfile = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0664)) < 0)
    {
        exit(1);
    }
    write(outfile, buffer, 1);
    close(outfile);
}

bool isDelimiter(char character)
{
    char delimiters[] = {' ', '\n', '\t'};
    for (int i = 0; i < 3; i++)
    {
        if (character == delimiters[i])
        {
            return true;
        }
    }
    return false;
}