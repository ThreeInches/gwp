#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int a = 100;

void* thr_start(void* arg)
{
    strcpy((char*)arg, "i changed your data");
    while(1)
    {
        a = 200;
        printf("I am a thread %s ======= %d\n", (char*)arg, a);
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t tid;
    char ptr[] = "pthread";
    //pthread_creatr(获取线程id， 线程属性， 线程入口函数， 参数)
    int res = pthread_create(&tid, NULL, thr_start, (void*)ptr);
    if(res != 0)
    {
        printf("thread error\n");
        return -1;
    }
    printf("create thread success\n");
    while(1)
    {
        printf("This is a main thread\n");
        sleep(1);
    }
    return 0;
}
