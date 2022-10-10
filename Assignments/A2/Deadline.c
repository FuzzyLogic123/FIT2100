// replace get_next_process with a method that takes whichever task has closest deadline
// that shoud be all we need to do

#include "main.h"

int main(int argc, char *argv[])
{
    char *filename = get_file_name(argc, argv);
    file_information file_info = read_from_file(filename);

    FILE *results_file = create_file("results-3.txt");

    pcb_t *processes_arrived;
    processes_arrived = malloc(file_info.process_count * sizeof(pcb_t));
    int time = 0;
    int processes_completed = 0;
    int current_process = -1;
    int arrived_processes_len = 0;


    pcb_t *active_process;

    while (processes_completed < file_info.process_count)
    {
        for (size_t i = 0; i < file_info.process_count; i++)
        {
            if (file_info.process_array[i].entryTime == time)
            {
                pcb_t process = file_info_to_process(file_info.process_array[i]);
                process.waitTime = time + 1;
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
            active_process->waitTime = 0;
            printf("Time %i: %s is in the running state.\n", time, active_process->process_name);
        }

        time++;

        active_process->remainingTime--;
        if (active_process->remainingTime == 0)
        {
            active_process->state = EXIT;
            printf("Time %i: %s has finished excecution.\n", time, active_process->process_name);

            active_process->turnaroundTime = time - active_process->entryTime;
            active_process->deadlineMet = time <= processes_arrived->deadline;
            append_process_information(results_file, *active_process);

            remove_element(processes_arrived, current_process, arrived_processes_len);
            arrived_processes_len--;
            processes_completed++;
            if (arrived_processes_len > 0)
            {
                active_process = get_next_process(processes_arrived, &current_process, arrived_processes_len, time);
            }
            continue;
        }

        if (arrived_processes_len > 0)
        {
            active_process = get_next_process(processes_arrived, &current_process, arrived_processes_len, time);
        }
    }
    return 0;
}
