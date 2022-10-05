#include "main.h"

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

file_information read_from_file(char *filename)
{
    FILE *fptr;
    int read;
    file_information file_info;
    process_information *process_array;

    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        exit(1);
    }

    file_info.process_count = count_lines(fptr) + 1;
    process_array = malloc(file_info.process_count * sizeof(process_information));
    int process_iterator = 0;
    process_information process_information;
    while ((read = fscanf(fptr, "%s %i %i %i", process_information.process_name, &process_information.entryTime, &process_information.serviceTime, &process_information.deadline)) != -1)
    {
        process_information.remainingTime = process_information.serviceTime;
        process_array[process_iterator] = process_information;
        process_iterator++;
    }
    fclose(fptr);
    file_info.process_array = process_array;
    return file_info;
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