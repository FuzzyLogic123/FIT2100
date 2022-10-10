#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    int deadlineMet;
    int turnaroundTime;
    int waitTime;

    process_state_t state;
} pcb_t;

typedef struct
{
    char process_name[11];

    int entryTime;
    int serviceTime;
    int remainingTime;
    int deadline;

} process_information; // to avoid using the same struct as the processes - seems like a sensible restriction to me

typedef struct
{
    int process_count;
    process_information *process_array;

} file_information;

int count_lines(FILE *fptr);
file_information read_from_file(char *filename);
char *get_file_name(int argc, char *argv[]);
pcb_t file_info_to_process(process_information process_info);
void append_process_information(FILE *fp, pcb_t process);
FILE *create_file(char* filename);
void remove_element(pcb_t *array, int index, int array_length);
void insert_element(pcb_t *array, pcb_t element, int *current_process, int *array_size);
pcb_t *get_next_process(pcb_t *processes_arrived, int *current_process, int arrived_processes_len, int time);