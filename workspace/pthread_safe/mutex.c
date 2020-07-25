#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int ticket = 100;
pthread_mutex_t mutex;

void* thr_scalpers(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if(ticket > 0)
        {
            usleep(1000);
            printf("I get a ticket %d!\n", ticket);
            ticket--;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

    return NULL;
}

int main()
{
    pthread_t tid[4];
    int i = 0;
    pthread_mutex_init(&mutex, NULL);
    for(; i < 4; i++)
    {
        int ret = pthread_create(&tid[i], NULL, thr_scalpers, NULL);
        if(ret != 0)
        {
            printf("pthread_create failed tid[%d]\n", i);
            return -1;
        }
        else
        {
            printf("pthread_create success!\n");
        }
    }

    for(; i < 4; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
