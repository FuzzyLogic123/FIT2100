#include <stdio.h>

int main(int argc, char *argv[])
{
    char *filename;

    FILE *fptr;
    char *line = NULL;
    size_t len = 0;
    int read;
    
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "processes.txt";
    }

    fptr = fopen(filename, "r");
    while ((read = getline(&line, &len, fptr)) != -1) {
        printf("%s", line);
    }
    printf("\n");

    fclose(fptr);

    return 0;
}
