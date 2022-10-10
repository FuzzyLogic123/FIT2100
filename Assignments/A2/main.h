/**
 * @file main.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief process state
 * 
 */
typedef enum
{
    READY,
    RUNNING,
    EXIT
} process_state_t;

/**
 * @brief contains information about an active process
 * 
 */
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


/**
 * @brief holds information about processes (not necessarily active)
 * 
 */
typedef struct
{
    char process_name[11];

    int entryTime;
    int serviceTime;
    int remainingTime;
    int deadline;

} process_information; // to avoid using the same struct as the processes - seems like a sensible restriction to me

/**
 * @brief information about the file containing the processes
 * 
 */
typedef struct
{
    int process_count;
    process_information *process_array;

} file_information;

/**
 * @brief counts the number of lines in a text file
 * 
 * @param fptr 
 * @return int 
 */
int count_lines(FILE *fptr);

/**
 * @brief gathers file information from a text file
 * 
 * @param filename 
 * @return file_information 
 */
file_information read_from_file(char *filename);

/**
 * @brief Get the file name object from command line
 * 
 * @param argc 
 * @param argv 
 * @return char* 
 */
char *get_file_name(int argc, char *argv[]);

/**
 * @brief converts file information into an active process
 * 
 * @param process_info 
 * @return pcb_t 
 */
pcb_t file_info_to_process(process_information process_info);

/**
 * @brief appends process information to given file
 * 
 * @param fp 
 * @param process 
 */
void append_process_information(FILE *fp, pcb_t process);

/**
 * @brief Create a file object given string
 * 
 * @param filename 
 * @return FILE* 
 */
FILE *create_file(char *filename);

/**
 * @brief removed an element from an array
 * 
 * @param array 
 * @param index 
 * @param array_length 
 */
void remove_element(pcb_t *array, int index, int array_length);

/**
 * @brief inserts an element into an array
 * 
 * @param array 
 * @param element 
 * @param current_process 
 * @param array_size 
 */
void insert_element(pcb_t *array, pcb_t element, int *current_process, int *array_size);

/**
 * @brief Get the next process object
 * 
 * @param processes_arrived 
 * @param current_process 
 * @param arrived_processes_len 
 * @param time 
 * @return pcb_t* 
 */
pcb_t *get_next_process(pcb_t *processes_arrived, int *current_process, int arrived_processes_len, int time);

/**
 * @brief Get the shortest process based on which process has the closest deadline
 * 
 * @param processes_arrived 
 * @param current_process 
 * @param arrived_processes_len 
 * @param time 
 * @return pcb_t* 
 */
pcb_t *get_shortest_deadline(pcb_t *processes_arrived, int *current_process, int arrived_processes_len, int time);