/* task1.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h> /* change to <sys/fcntl.h> for System V */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i, outfile, odd, even;
    char unitCode[8];
    int unitId;

    i = 0;

    int readOrder[] = {1, 0, 3, 2};

    struct Record
    {
        int unitid;
        char unitcode[8];
    };

    outfile = open("recordfile", O_RDONLY);

    if ((odd = open("odd", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
    {
        exit(1);
    }

    if ((even = open("even", O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
    {
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        lseek(outfile, (long) readOrder[i] * 12 + 4, SEEK_SET);
        read(outfile, unitCode, 8);

        lseek(outfile, (long) readOrder[i] * 12, SEEK_SET);
        read(outfile, &unitId, 4);
        if (unitId % 2 == 0) {
            // write into even
            write(even, &unitCode, 8);
        } else {
            // write into odd
            write(odd, &unitCode, 8);
        }

        write(1, &unitCode, 8);
        write(1, "\n", 2 * sizeof(char));
    }

    close(outfile);
    exit(0);
}