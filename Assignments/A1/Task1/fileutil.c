#include <sys/file.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

int main(int argc, char const *argv[])
{
    int i, infile;
    int spaceCount = 0;
    char buffer[1];

    char *fileName = "sample.txt";

    if (argc == 2)
    {
        fileName = (char *)malloc(strlen(argv[0]) + 1);

        if (fileName == NULL) {
            char *errorString = "Memory allocation error\n";
            write(2, errorString, strlen(errorString));
        }
        strcpy(fileName, argv[1]);

    }

    if ((infile = open(fileName, O_RDONLY)) < 0)
    {
        printf("%s", fileName);
        // char *errorString = "The file could not be opened\n";
        // write(2, errorString, strlen(errorString));
        // exit(1);
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
