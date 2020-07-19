#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    while(1)
    {   
    //1.等待标准输入
    char buf[1024] = { 0 };
    fgets(buf, 1023, stdin);
    buf[strlen(buf) - 1] = '\0';
    printf("buf[%s]\n", buf);
    //2.参数解析
    char* ptr = buf;
    char* new_argv[32] = { 0};
    int new_argc = 0;
    while(*ptr != '\0')
    {
        if(*ptr != ' ')
        {
            new_argv[new_argc] = ptr;
            new_argc++;
            while(*ptr != ' ')
            {
                ptr++;
            }
            *ptr = '\0';
        }
        ptr++;
    }
    int i = 0;
    for(; i < new_argc; i++)
    {
        printf("new_argv[%d] = %s\n", i, new_argv[i]);
    }
    //3.创建一个子进程
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
    //4.在子进程中进行程序替换
        execvp(new_argv[0], new_argv);
        perror("execvp error");//打印上一次系统调用接口使用的错误原因
        exit(0);
    }
    //5.进程等待
    wait(NULL);
    }

    return 0;
    }
