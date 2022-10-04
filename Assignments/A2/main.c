#include <stdio.h>

typedef enum {
    READY, RUNNING, EXIT
} process_state_t;

typedef struct {
    char process_name[11];

    int entryTime;
    int serviceTime;
    int remainingTime;

    process_state_t state;
} pcb_t;

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
