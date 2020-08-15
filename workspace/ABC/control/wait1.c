#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
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
        int ret = waitpid(-1, &st, 0);
        if(WIFEXITED(st) && ret == pid)
        {
            printf("wait child exit.exit ID = %d\n", WEXITSTATUS(st));
        }
        else
        {
            printf("wait child failed\n");
        }
    }
    return 0;
}
