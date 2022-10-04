#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_char(char *str, char c);
int count_lines(FILE *fptr);


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
    char *line = NULL;
    size_t len = 0;
    int read;
    char c;
    int spaceCounter = 0;
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

    if (fptr = fopen("processes.txt", "r"))
    {
        process_count = count_lines(fptr) + 1;
        process_array = malloc(process_count * sizeof(pcb_t));
        int process_iterator = 0;
        pcb_t process_information;
        process_information.process_name[0] = 0; // set the end of the string to null pointer

        while ((c = getc(fptr)) != EOF)
        {
            if (c != ' ' && c != '\n')
            {
                if (spaceCounter == 0)
                {
                    process_information.process_name[strlen(process_information.process_name) + 1] = 0;
                    process_information.process_name[strlen(process_information.process_name)] = c;
                }
                else if (spaceCounter == 1)
                {
                    int temp = c - '0';
                    process_information.entryTime = temp;
                }
                else if (spaceCounter == 2)
                {
                    int temp = c - '0';
                    process_information.serviceTime = temp;
                }
                else if (spaceCounter == 3)
                {
                    int temp = c - '0';
                    process_information.deadline = temp;
                }
            }
            else
            {
                if (spaceCounter == 3) {
                    process_array[process_iterator] = process_information;
                    process_information.process_name[0] = 0;
                    process_iterator++;
                    spaceCounter = 0;
                } else {
                    spaceCounter++;
                }
            }
        }
        process_array[process_iterator] = process_information;
    }
    else
    {
        exit(1);
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