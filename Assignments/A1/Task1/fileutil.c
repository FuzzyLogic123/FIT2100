#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <stdio.h> //remove this for submssion

void printError(char *errorString);
void appendToFile(char *fileName, char buffer[1]);
void printStandard(char *string);

int main(int argc, char *argv[])
{
    int i, infile, outfile, opt;
    int spaceCount = 0;
    char buffer[1];
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
            printf("Option n has arg: %s\n", optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        case ':':
            printf("Missing arg for %c\n", optopt);
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

    append = true;

    if ((infile = open(fileName, O_RDONLY)) < 0)
    {
        printError("The file could not be opened\n");
    }

    while (read(infile, buffer, 1) > 0 && spaceCount < 10)
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