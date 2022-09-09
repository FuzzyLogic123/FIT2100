#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{

    int pid = fork();

    if (pid == 0)
    {
        execl("/bin/echo", "echo", argv[1], NULL);
    }
    else if (pid > 0)
    {
        execl("/bin/less", "less", argv[2], NULL);
    }
    else
    {
        perror("The fork failed");
    }

    return 0;
}