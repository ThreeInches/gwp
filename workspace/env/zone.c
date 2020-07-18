#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int gval = 1;

int main()
{
    pid_t pid = 0;
    pid = fork();

    if(pid == 0)
    {
        gval = 100;
        printf("child gval:%d---%p\n", gval, &gval);
    }
    else
    {
        sleep(5);
        printf("parent gval:%d---%p\n", gval, &gval);
    }
}
