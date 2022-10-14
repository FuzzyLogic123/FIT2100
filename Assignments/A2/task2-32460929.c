/**
 * @file RR.c
 * @author Patrick Edwards
 * @brief this file simulates process scheduling this file
 * uses an algorithim where each process in the queue is given
 * two seconds of cpu time. New processes are added to the back of the queue.
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

    FILE *results_file = create_file("results-2.txt");

    pcb_t *processes_arrived;
    processes_arrived = malloc(file_info.process_count * sizeof(pcb_t));
    int arrived_processes_len = 0;
    int processes_completed = 0;
    int current_process = -1;
    int time = 0;
    int time_quantum_tracker = 0;
    int time_quantum = 2;
    pcb_t *active_process;

    while (processes_completed < file_info.process_count) // keep iterating until processes are completed
    {
        for (size_t i = 0; i < file_info.process_count; i++)
        {
            if (file_info.process_array[i].entryTime == time)
            {
                pcb_t process = file_info_to_process(file_info.process_array[i]);
                if (current_process == -1) // insert to first place if the array is empty
                {
                    int tmp = 0;
                    insert_element(processes_arrived, process, &tmp, &arrived_processes_len);
                    current_process = 0;
                }
                else
                {
                    insert_element(processes_arrived, process, &current_process, &arrived_processes_len);
                }

                printf("Time %i: %s has entered the system.\n", time, process.process_name);
                active_process = &processes_arrived[current_process];
            }
        }

        if (time == 0)
        {
            active_process = &processes_arrived[current_process];
            // active_process->waitTime = 0;
            printf("Time %i: %s is in the running state.\n", time, active_process->process_name);
        }

        if (active_process->waitTime == -1)
        {
            active_process->waitTime = time - active_process->entryTime;
        }
        time++;
        time_quantum_tracker++;

        active_process->remainingTime--;
        if (active_process->remainingTime == 0)
        {
            active_process->state = EXIT;
            printf("Time %i: %s has finished excecution.\n", time, active_process->process_name);

            active_process->turnaroundTime = time - active_process->entryTime;
            active_process->deadlineMet = (time - active_process->entryTime) <= active_process->deadline;
            append_process_information(results_file, *active_process);

            remove_element(processes_arrived, current_process, arrived_processes_len);
            arrived_processes_len--;
            processes_completed++;
            if (arrived_processes_len > 0)
            {
                active_process = get_next_process(processes_arrived, &current_process, arrived_processes_len, time);
            }
            time_quantum_tracker = 0;
            continue;
        }

        if (time_quantum_tracker % time_quantum == 0 && arrived_processes_len > 0) // get new process if 2 seconds has passed
        {
            active_process = get_next_process(processes_arrived, &current_process, arrived_processes_len, time);
        }
    }
    return 0;
}
