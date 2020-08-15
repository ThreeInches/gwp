#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        perror("fork error\n");
        return -1;
    }
    else if(pid == 0)
    {
        printf("I am child pid %d,pid = %d\n", getpid(), pid);
    }
    else
    {
        printf("I am parent pid %d,pid = %d\n", getpid(), pid);
    }
    sleep(1);
    return 0;
}
