#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int g_val = 100;

int main()
{
    printf("before pid = %d\n", getpid());
    int ret = fork();
    if(ret < 0)
    {
        perror("fork error\n");
        return -1;
    }
    else if(ret == 0)
    {
        g_val = 200;
        printf("child pid = %d ret = %d\n",getpid(), ret);
        printf("g_val = %d\n", g_val);
    }
    else
    {
        printf("parent pid = %d ret = %d\n",getpid(), ret);
        printf("g_val = %d\n", g_val);
    }
    sleep(1);
    return 0;
}
