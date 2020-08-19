#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipefd[2];
    int pid;
    int ret;
    char* buf = "abcdefgh";
    ret = pipe(pipefd);
    if(ret  < 0)
    {
        perror("pipe error\n");
        return -1;
    }

    pid = fork();
    if(pid < 0)
    {
        perror("fork error\n");
        return -1;
    }
    else if(pid == 0)
    {
        close(pipefd[0]);
        write(pipefd[1], buf, sizeof(buf));
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        char buffer[100] = {0};
        read(pipefd[0], buffer, sizeof(buf));
        close(pipefd[0]);
        printf("buffer = %s\n", buffer);
    }
    return 0;
}
