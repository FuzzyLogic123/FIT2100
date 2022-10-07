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

    while (processes_completed < file_info.process_count)
    {
        /* the process has entered the system */
        if (file_info.process_array[i].entryTime == time && i < file_info.process_count)
        {
            pcb_t process;
            process = file_info_to_process(file_info.process_array[i]);
            processes_arrived[i] = process;
            processes_arrived[i].waitTime = time + 1;
            
            printf("Time %i: %s has entered the system.\n", time, process.process_name);
            if (i == j)
            {
                printf("Time %i: %s is in the running system.\n", time, processes_arrived[j].process_name);
                processes_arrived[j].waitTime = 0;
            }
            i++;
        }

        /* check if a process has finished its excecution */
        if (processes_arrived[j].serviceTime == 0)
        {
            printf("Time %i: %s has finished execution.\n", time, processes_arrived[j].process_name);
            processes_arrived[j].state = EXIT;
            processes_arrived[j].turnaroundTime = time - processes_arrived[j].entryTime;
            processes_arrived[j].deadlineMet = time <= processes_arrived[j].deadline;
            append_process_information(results_file, processes_arrived[j]);
            processes_completed++;
            j++;
            if (j < file_info.process_count)
            {
                printf("Time %i: %s is in the running state.\n", time, processes_arrived[j].process_name);
                processes_arrived[j].state = RUNNING;
            }
        }

        /* service a process */
        processes_arrived[j].serviceTime--;
        time++;
    }

    return 0;
}
