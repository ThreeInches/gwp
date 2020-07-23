#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int a= 1, b = 1;

int test()
{
    a++;
    sleep(5);
    b++;
    return a + b;
}

void sigcb(int signo)
{
    printf("signal sum = %d\n", test());
}

int main()
{
    signal(SIGINT, sigcb);
    sleep(3);
    printf("main sum = %d\n");
    return 0;
}
