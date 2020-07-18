#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        sleep(5);
        exit(0);//子进程5秒后退出，父进程什么都不做就会成为僵尸进程
    }
    //wait(NULL);
    int ret, status;
    while((ret =waitpid(pid, &status, WNOHANG)) == 0)
    {
        printf("子进程退出\n");
        sleep(1);
    }
    if((status & 0x7f) == 0)
    {
        printf("status = %d\n", (status >> 8) & 0xff);
    }
    if(WIFEXITED(status))
    {
        printf("status = %d\n", WEXITSTATUS(status));
    }
    while(1)
    {
        printf("=======\n");
        sleep(1);
    }
    return 0;
}
