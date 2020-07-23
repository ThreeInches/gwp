#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

volatile long long a = 1;

void sigcb(int signo)
{
    a = 0;
    printf("a = %d\n", a);
}

int main()
{
    signal(SIGINT, sigcb);
    while(a)
    {

    }
    printf("exited a = %d\n", a);
    return 0;
}
