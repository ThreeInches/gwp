#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int bowl = 0;
pthread_mutex_t mutex;

pthread_cond_t cond_cook;
pthread_cond_t cond_customer;

void* thr_cook(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(bowl != 0)
        {
            pthread_cond_wait(&cond_cook, &mutex);
        }
        bowl = 1;
        printf("I made a bowl of rice\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_customer);
    }
    return NULL;
}

void* thr_customer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        while(bowl != 1)
        {
            pthread_cond_wait(&cond_customer, &mutex);
        }
        bowl = 0;
        printf("I had a bowl of rice. It was delicious\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond_cook);
    }
    return NULL;
}

int main()
{
    pthread_t tid[4];
    int ret;
    int i = 0;
    pthread_cond_init(&cond_cook, NULL);
    pthread_cond_init(&cond_customer, NULL);
    for(i = 0; i < 4; i++)
    {
        ret = pthread_create(&tid[i], NULL, thr_cook, NULL);
        if(ret != 0)
        {
            perror("pthread_create error\n");
            return -1;
        }
    }

    for(i = 0; i < 4; i++)
    {
        ret = pthread_create(&tid[i], NULL, thr_customer, NULL);
        if(ret != 0)
        {
            perror("pthread_create error\n");
            return -1;
        }
    }
    for(i = 0; i < 4; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_cond_destroy(&cond_cook);
    pthread_cond_destroy(&cond_customer);
    return 0;
}
