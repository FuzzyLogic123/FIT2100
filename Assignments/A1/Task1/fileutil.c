#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <stdio.h> //remove this for submssion

void printError(char *errorString);

int main(int argc, char *argv[])
{
    int i, infile, opt;
    int spaceCount = 0;
    char buffer[1];
    bool append = false;

    char *fileName = "sample.txt";

    // https://azrael.digipen.edu/~mmead/www/Courses/CS180/getopt.html
    while ((opt = getopt(argc, argv, "an:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            printf("Option a was provided");
            append = true;
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
        printf("Non-option args: ");
        while (optind < argc)
            optind++;
        printf("%s", argv[optind]);
        // fileName = (char *)malloc(strlen(argv[optind]) + 1);
        if (fileName == NULL)
        {
            printError("Memory allocation error\n");
        }
        strcpy(fileName, argv[optind]);
        printf("%s ", fileName);
        printf("\n");
    }


    if ((infile = open(fileName, O_RDONLY)) < 0)
    {
        printError("The file could not be opened\n");
    }

    while (read(infile, buffer, 1) > 0 && spaceCount < 10)
    {
        if (strcmp(buffer, " ") != 0)
        {
            write(1, buffer, 1);
        }
        else
        {
            write(1, "\n", 2 * sizeof(char));
            spaceCount++;
        }
    }
    write(1, "\n", 2 * sizeof(char));

    close(infile);

    return 0;
}

void printError(char *errorString)
{
    write(2, errorString, strlen(errorString));
    exit(1);
}