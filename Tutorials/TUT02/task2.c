#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, *iptr;
    int sum = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    iptr = (int *)malloc(n * sizeof(int));

    printf("Enter elements: ");
    for (i = 0; i < n; ++i)
    {
        scanf("%d", iptr + i);
    }

    for (i = 0; i < n; ++i)
    {
        sum += *(iptr + i);
    }

    printf("%d", sum);

    free(iptr);
}
