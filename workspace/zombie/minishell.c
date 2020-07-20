#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main()
{
    while(1)
    {   
    //1.等待标准输入
    printf("[gwp@locasthost ~]$ ");
    fflush(stdout);
    char buf[1024] = { 0 };
    fgets(buf, 1023, stdin);
    buf[strlen(buf) - 1] = '\0';
    //2.参数解析
    char* ptr = buf;
    int redirect_flag = 0;
    char* redirect_file = NULL;
    while(*ptr != '\0')
    {
        if(*ptr == '>')
        {
            redirect_flag = 1;
            *ptr = '\0';
            ptr++;
            if(*ptr == '>')
            {
                redirect_flag = 2;
                *ptr = '\0';
                ptr++;
            }
        }
        while(*ptr == ' ' && *ptr != '\0')
        {
            ptr++;
        }
        redirect_file = ptr;
        while(*ptr == ' ' && *ptr != '\0')
        {
            ptr++;
        }
        *ptr = '\0';
    }
    ptr = buf;
    char* new_argv[32] = { NULL };
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
    
    //3.创建一个子进程
    pid_t pid;
    pid = fork();
    int fd = -1;
    if(pid == 0)
    {
    //4.在子进程中进行程序替换
        if(redirect_flag == 1)
        {
            umask(0);
            fd = open(redirect_file, O_WRONLY|O_CREAT|O_TRUNC, 0777);
            if(fd < 0)
            {
                perror("open error");
                return -1;
            }
            dup2(fd, 1);
        }
        else if(redirect_flag == 2)
        {
            umask(0);
            fd = open(redirect_file, O_WRONLY|O_CREAT|O_APPEND, 0777);
            if(fd < 0)
            {
                perror("open error");
                return -1;
            }
            dup2(fd, 1);
        }
        execvp(new_argv[0], new_argv);
        perror("execvp error");
        exit(0);
    }
    //5.进程等待
    wait(NULL);
    }
    
    return 0;
}
