#include "main.h"

int main(int argc, char *argv[])
{
    char *filename = get_file_name(argc, argv);
    file_information file_info = read_from_file(filename);

    pcb_t *processes_arrived;

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
            process.deadline = file_info.process_array[i].deadline;
            strcpy(process.process_name, file_info.process_array[i].process_name);
            process.entryTime = file_info.process_array[i].entryTime;
            process.serviceTime = file_info.process_array[i].serviceTime;
            process.remainingTime = file_info.process_array[i].remainingTime;
            process.state = READY;
            processes_arrived[i] = process;
            printf("Time %i: %s has entered the system.\n", time, process.process_name);
            if (i == j)
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
