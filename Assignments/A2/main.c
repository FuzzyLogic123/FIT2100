/**
 * @file main.c
 * @author Patrick Edwards 32460929
 * @brief contains all the functions that will be used throughout
 * the process simulation files (FCFS.c, deadline.c, RR.c)
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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

    file_info.process_count = count_lines(fptr) + 1; // there will be one extra process than there is new lines
    process_array = malloc(file_info.process_count * sizeof(process_information));
    int process_iterator = 0; // store where the next location of the process should go
    process_information process_information;
    while ((read = fscanf(fptr, "%s %i %i %i", process_information.process_name, &process_information.entryTime, &process_information.serviceTime, &process_information.deadline)) != -1) // read the information from the file to an object storing process information
    {
        process_information.remainingTime = process_information.serviceTime;
        process_array[process_iterator] = process_information;
        process_iterator++;
    }
    fclose(fptr);
    file_info.process_array = process_array;
    return file_info;
}

char *get_file_name(int argc, char *argv[])
{
    if (argc > 1)
    {
        return argv[1];
    }
    else
    {
        return "processes.txt";
    }
}

pcb_t file_info_to_process(process_information process_info)
{
    pcb_t process;
    process.deadline = process_info.deadline;
    strcpy(process.process_name, process_info.process_name);
    process.entryTime = process_info.entryTime;
    process.serviceTime = process_info.serviceTime;
    process.remainingTime = process_info.remainingTime;
    process.state = READY;
    process.waitTime = -1;
    return process;
}

FILE *create_file(char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        exit(1);
    }
    return fp;
}

void append_process_information(FILE *fp, pcb_t process)
{
    fprintf(fp, "%s %i %i %i\n", process.process_name, process.waitTime, process.turnaroundTime, process.deadlineMet);
}

void remove_element(pcb_t *array, int index, int array_length)
{
    int i;
    for (i = index; i < array_length - 1; i++)
    {
        array[i] = array[i + 1];
    }
}

void insert_element(pcb_t *array, pcb_t element, int *current_process, int *array_size)
{
    int i;
    for (i = *array_size; i > *current_process; i--)
        array[i] = array[i - 1];
    array[*current_process] = element;
    (*array_size)++;
    (*current_process)++; // current process is not incremented to accomidate for the inserted process
}

pcb_t *get_next_process(pcb_t *processes_arrived, int *current_process, int arrived_processes_len, int time)
{
    (*current_process)++;
    if (*current_process > arrived_processes_len - 1)
    {
        *current_process = 0;
    }
    printf("Time %i: %s is in the running state.\n", time, processes_arrived[*current_process].process_name);
    return &processes_arrived[*current_process];
}

pcb_t *get_shortest_deadline(pcb_t *processes_arrived, int *current_process, int arrived_processes_len, int time)
{
    // calculate closest deadline from the current time
    int closest_deadline = 0;
    for (size_t i = 0; i < arrived_processes_len; i++)
    {
        if ((processes_arrived[i].deadline - time < processes_arrived[closest_deadline].deadline - time) && (processes_arrived[i].deadline - time > 0))
        {
            closest_deadline = i;
        }
    }

    *current_process = closest_deadline;
    printf("Time %i: %s is in the running state.\n", time, processes_arrived[*current_process].process_name);
    return &processes_arrived[*current_process];
}