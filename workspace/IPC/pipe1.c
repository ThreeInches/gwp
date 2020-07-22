#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        return -1;
    }
    else if(pid == 0)
    {
        close(pipefd[1]);
        sleep(3);
        char buf[1024] = { 0 };
        read(pipefd[0], buf, 1023);
        printf("read:%s\n", buf);
    }
    else
    {
        close(pipefd[1]);
        sleep(1000);
        char* ptr = "This is a pipe1 demo";
        write(pipefd[1], ptr, strlen(ptr));
    }
    
    return 0;
}
