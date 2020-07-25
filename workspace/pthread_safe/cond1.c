#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int bowl = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* thr_cook(void* arg)
{
   while(1)
   {
        pthread_mutex_lock(&mutex);
        if (bowl != 0)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        bowl = 1;
        printf("I made a bowl of rice\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
   }
    return NULL;
}

void* thr_customer(void* arg)
{
   while(1)
   {
        pthread_mutex_lock(&mutex);
        if (bowl != 1)
        {
            pthread_cond_wait(&cond, &mutex);
        }
        bowl = 0;
        printf("I had a bowl of rice. It was delicious\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
   }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret;
    pthread_cond_init(&cond, NULL);
    ret = pthread_create(&tid, NULL, thr_cook, NULL);
    if(ret != 0)
    {
        perror("pthread_create error\n");
        return -1;
    }

    ret = pthread_create(&tid, NULL, thr_customer, NULL);
    if(ret != 0)
    {
        perror("pthread_create error\n");
        return -1;
    }

    pthread_join(tid, NULL);
    pthread_cond_destroy(&cond);
    return 0;
}
