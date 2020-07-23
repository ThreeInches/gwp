#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sigcb(int signo)
{
    printf("recerve a signal no : %d \n", signo);
}

int main()
{
    signal(SIGINT, sigcb);
    signal(SIGQUIT, sigcb);
    while(1)
    {
        printf("This is a signal example\n");
        sleep(10);
    }
    return 0;
}
