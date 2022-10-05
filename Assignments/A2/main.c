#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_char(char *str, char c);
int count_lines(FILE *fptr);
int convert_to_int(char c);

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

int main(int argc, char *argv[])
{
    char *filename;

    FILE *fptr;
    size_t len = 0;
    int read;
    int process_count;
    pcb_t *process_array;

    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        filename = "processes.txt";
    }

    fptr = fopen("processes.txt", "r");
    if (fptr == NULL)
    {
        exit(1);
    }

    process_count = count_lines(fptr) + 1;
    process_array = malloc(process_count * sizeof(pcb_t));
    int process_iterator = 0;
    pcb_t process_information;
    while ((read = fscanf(fptr, "%s %i %i %i", process_information.process_name, &process_information.entryTime, &process_information.serviceTime, &process_information.deadline)) != -1)
    {
        process_information.remainingTime = process_information.serviceTime;
        process_array[process_iterator] = process_information;
        process_iterator++;
    }

    printf("\n");

    fclose(fptr);

    return 0;
}

// char *concatenate_char(char *str, char c)
// {
//     size_t len = strlen(str);
//     /* one for extra char, one for trailing zero */
//     char *str2 = malloc(len + 1 + 1);

//     strcpy(str2, str);
//     str2[len] = c;
//     str2[len + 1] = '\0';
//     return str2;
//     // free(str2);
// }

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

int convert_to_int(char c)
{
    return c - '0';
}