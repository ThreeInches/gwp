#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void function()
{
    char* ptr = "This is a pthread_wait";
    pthread_exit((void*)ptr);
}

void* pth_start(void* arg)
{ 
    pthread_detach(pthread_self());
    while(1)
    {
        printf("I am a pthread\n");
        sleep(1);
        function();
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int res = pthread_create(&tid, NULL, pth_start, NULL);
    if(res != 0)
    {
        printf("create pthread failed\n");
    }
    printf("create pthread success\n");
    //pthread_cancel(tid);
    //char* ptr;
    //pthread_join(tid, (void**)&ptr);
    //printf("reavl = %s\n", ptr);
    while(1)
    {
        printf("I am a main thread\n");
        sleep(1);
    }

    return 0;
}
