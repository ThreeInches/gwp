#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        perror("fork error\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        sleep(20);
        exit(10);
    }
    else
    {
        int st;
        pid_t ret = wait(&st);
        if(ret == pid && (st & 0x7f) == 0)
        {
            printf("child exit = %d\n", (st >> 8) & 0xff);
        }
        else if(ret == pid)
        {
            printf("signal exit = %d\n", st & 0x7f);
        }
    }
    return 0;
}
