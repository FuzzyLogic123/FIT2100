#include <stdio.h>

int main(void)
{
    int n1;
    int n2;
    int max;

    printf("Enter two integers\n");
    scanf("%d %d", &n1, &n2);
    max = (n1 > n2) ? n1 : n2;

    
    while (1) {
        if (max % n1 == 0 && max % n2 == 0) {
            printf("the lowest common multiple is %d", max);
            break;
        }
        max++;
    }
    return 0;
}
