#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//程序的运行参数可以通过main函数传入
//argc表示有多少个参数
//argv中存储参数信息
//env中存储环境变量信息
int main(int agrc, char* argv[], char* env[])
{
    int i = 0;
    for(i= 0; i < agrc; i++)
    {
        printf("agrv[%d] = [%s]\n",i ,argv[i]);
    }
    for(i= 0; env[i] != NULL; i++)
    {
        printf("env[%d] = [%s]\n",i ,env[i]);
    };
    extern char** environ;//声明一个变量
    for(i= 0; environ[i] != NULL; i++)
    {
        printf("environ[%d] = [%s]\n",i ,environ[i]);
    };
    // char* getenv(char* name);通过环境变量名称获取指定环境变量的数据
    char* ptr = getenv("MYVAL");
    if(ptr != NULL)
    {
        printf("%s\n", ptr);
    }
    else
    {
        printf("There is no variavle!\n");
    }
    return 0;
}
