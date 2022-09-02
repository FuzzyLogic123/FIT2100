/* execl-ls.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void count(int start, char ch);

int main(int argc, char *argv[])
{
  int pid;
  int start = 0;

  pid = fork(); /* fork a child process */

  if (pid > 0) { /* parent continues here  */
    count(start, 'P');
    
    /* wait for the child process to terminate. */
    /* if the child has already terminated, the zombie process it became is cleaned up */
    wait(NULL);
  }
  else if (pid == 0) { /* child got here */
    /* when the child process terminates, the child process becomes a zombie process */
    execl("/bin/ls", "ls", "-l", NULL); /* execute ls command */
  }
  else { /* there is a problem with fork */
    perror("Failed to fork a process\n");
    exit(1);
  }
}

void count(int start, char ch)
{
  int i, j;
  
  for (i = start; i < 10; i++)
  {
    for (j = 0; j < 100000000; j++); /*delay*/
    printf("Message from %c process at the %dth iteration \n", ch, i);
  }
}
