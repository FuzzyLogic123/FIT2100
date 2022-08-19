#include <stdio.h>
#include <stdlib.h>

int *find_largest(int the_array[], int num_elements);

int main(void)
{
    int array[] = {1, 4, 2, 4, 5, 6};
    int* largest;
    largest = find_largest(array, 6);
    printf("%p", largest);
    return 0;
}

int *find_largest(int the_array[], int num_elements) {
    int i;
    int *ptr_max;
    ptr_max = &the_array[0];

    for (i = 0; i < num_elements; i++) {
        if (the_array[i] > *ptr_max) {
            ptr_max = &the_array[i];
        }
    }

    return ptr_max;
}