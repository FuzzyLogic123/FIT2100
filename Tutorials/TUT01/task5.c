#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define numCount 6

int main(void)
{
    int i;

    int randomNumbers[numCount];
    /* Intializes random number generator */
    srand(time(NULL));

    for (i = 0; i < numCount; i++)
    {
        /* code */
        randomNumbers[i] = rand();
    }

    // prints to output
    for (int i = 0; i < numCount; i++)
    {
        printf("%d ", randomNumbers[i]);
    }
    printf("\n");
    return 0;
}
