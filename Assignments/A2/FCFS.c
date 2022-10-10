/**
 * @file FCFS.c
 * @author Patrick Edwards
 * @brief this file simulates process scheduling this file
 * uses an algorithim where the next process in the queue is chosen
 * to get cpu time. New processes are added to the back of the queue.
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

int main(int argc, char *argv[])
{
    char *filename = get_file_name(argc, argv);
    file_information file_info = read_from_file(filename);

    pcb_t *processes_arrived;

    FILE *results_file = create_file("results-1.txt");

    processes_arrived = malloc(file_info.process_count * sizeof(pcb_t));
    int i = 0;
    int j = 0;
    int time = 0;
    int processes_completed = 0;


    while (processes_completed < file_info.process_count) // keep iterating until processes are completed
    {
        /* the process has entered the system */
        if (file_info.process_array[i].entryTime == time && i < file_info.process_count)
        {
            pcb_t process;
            process = file_info_to_process(file_info.process_array[i]);
            processes_arrived[i] = process;

            printf("Time %i: %s has entered the system.\n", time, process.process_name);
            if (i == j) // the first process will always start off running
            {
                printf("Time %i: %s is in the running system.\n", time, processes_arrived[j].process_name);
            }
            i++;
        }

        /* check if a process has finished its excecution */
        if (processes_arrived[j].serviceTime == 0)
        {
            printf("Time %i: %s has finished execution.\n", time, processes_arrived[j].process_name);
            processes_arrived[j].state = EXIT;
            processes_arrived[j].turnaroundTime = time - processes_arrived[j].entryTime;
            processes_arrived[j].deadlineMet = processes_arrived[j].deadline >= (time - processes_arrived[j].entryTime);
            append_process_information(results_file, processes_arrived[j]);
            processes_completed++;
            j++;
            if (j < file_info.process_count) // ensure we have not reached the end of the array
            {
                printf("Time %i: %s is in the running state.\n", time, processes_arrived[j].process_name);
                processes_arrived[j].state = RUNNING;
            }
        }

        /* service a process */
        processes_arrived[j].serviceTime--;
        if (processes_arrived[j].waitTime == -1) // if wait time has not already been set, update it
        {
            processes_arrived[j].waitTime = time - processes_arrived[j].entryTime;
        }
        time++;
    }

    return 0;
}
