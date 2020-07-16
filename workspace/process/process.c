#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("-----create child process start -----%d\n", getpid());
    pid_t pid;
    pid = fork();//这个函数的返回值对于父子进程是不一样的

    if(pid == 0)
    {
        printf("This is a child process %d -- rpid %d\n", getpid(), pid);
    }else if(pid > 0)
    {
        printf("This is a parent process %d -- rpid %d\n", getpid(), pid);
    }else
    {
        printf("This is a error\n");
    }
    while(1)
    {
        sleep(1);
        printf("-----create child process  end -----%d\n", getpid());
    }
    return 0;
}
