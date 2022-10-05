#include "main.h"

typedef enum
{
    READY,
    RUNNING,
    EXIT
} process_state_t;

typedef struct
{
    char process_name[11];

    int entryTime;
    int serviceTime;
    int remainingTime;
    int deadline;

    process_state_t state;
} pcb_t;

typedef struct
{
    char process_name[11];

    int entryTime;
    int serviceTime;
    int remainingTime;
    int deadline;

    process_state_t state;
} process_information; // to avoid using the same struct as the processes - seems like a sensible restriction to me


int count_lines(FILE *fptr)
{
    int new_line_counter = 0;
    char c;
    while ((c = getc(fptr)) != EOF)
    {
        if (c == '\n')
        {
            new_line_counter++;
        }
    }
    fseek(fptr, 0, SEEK_SET);
    return new_line_counter;
}

void read_from_file(char *filename)
{
    FILE *fptr;
    int read;
    int process_count;
    process_information *process_array;

    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        exit(1);
    }

    process_count = count_lines(fptr) + 1;
    process_array = malloc(process_count * sizeof(process_information));
    int process_iterator = 0;
    process_information process_information;
    while ((read = fscanf(fptr, "%s %i %i %i", process_information.process_name, &process_information.entryTime, &process_information.serviceTime, &process_information.deadline)) != -1)
    {
        process_information.remainingTime = process_information.serviceTime;
        process_array[process_iterator] = process_information;
        process_iterator++;
    }

    fclose(fptr);
}

char *get_file_name(int argc, char *argv[]) {
    if (argc > 1)
    {
        return argv[1];
    }
    else
    {
        return "processes.txt";
    }
}