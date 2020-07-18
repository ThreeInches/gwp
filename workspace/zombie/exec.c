#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, int* argv[])
{
    printf("ni hao a~~~\n");
    //execl("/usr/bin/ls", "ls", "-a", NULL);
    //execl("./test", "test", "-a", NULL);
    char* new_argv[] = {"test", "-a", "-l", NULL};
    char* new_env[] = {"MYVAL = 1000", "TEST = 2000", NULL};
    execve("./test", new_argv, new_env);
    return 0;
}
