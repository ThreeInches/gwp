#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main()
{
   //kill(getpid(), 15);
    //abort();
    //alarm(2);
    raise(15);
    while(1)
    {
        printf("This is a signal example\n");
        sleep(5);
    }
    return 0;
}
