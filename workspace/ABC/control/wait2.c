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
        printf("I am a child process! pid = %d\n", getpid());
        sleep(5);
        exit(257);
    }
    else
    {
        int st;
        int ret;
        do
        {
            ret = waitpid(-1, &st, WNOHANG);
            if(ret == 0)
            {
                printf("child is running\n");
            }
            sleep(1);
        }while(ret == 0);
        if(WIFEXITED(st) && ret == pid)
        {
            printf("child exit waitpid = %d\n", WEXITSTATUS(st));
        }
        else
        {
            printf("child exit failed!\n");
        }
    }
    return 0;
}
