#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipefd[2] = { -1 };
    int ret = pipe(pipefd);
    if(ret < 0)
    {
        perror("pipe error");
        return -1;
    }

    pid_t ps_pid;
    ps_pid = fork();
    if(ps_pid < 0)
    {
        perror("pe_pid error");
        return -1;
    }
    else if(ps_pid == 0)
    {
        dup2(pipefd[1], 1);
        execlp("ps", "ps", "-ef", NULL);
        exit(0);
    }
    
    pid_t grep_pid;
    grep_pid = fork();
    if(grep_pid < 0)
    {
        perror("grep_pid error");
        return -1;
    }
    else if(grep_pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        execlp("grep", "grep", "ssh", NULL);
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(ps_pid, NULL, 0);
    waitpid(grep_pid, NULL, 0);
    return 0;
}
