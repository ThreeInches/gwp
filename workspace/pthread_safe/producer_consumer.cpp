#include <iostream>
#include <queue>
#include <pthread.h>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define MAX_CAPACITY 5 

template<class T>
class BlockQueue
{
public:
    BlockQueue(int capacity = MAX_CAPACITY)
        :m_capacity(capacity)
    {
        pthread_mutex_init(&m_mutex, NULL);
        pthread_cond_init(&m_producer_cond, NULL);
        pthread_cond_init(&m_consumer_cond, NULL);
    }

    ~BlockQueue()
    {

        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_producer_cond);
        pthread_cond_destroy(&m_consumer_cond);
    }

    bool Push(const T& data)
    {
        pthread_mutex_lock(&m_mutex);
        while(m_queue.size() == m_capacity)
        {
            pthread_cond_wait(&m_producer_cond, &m_mutex);
        }
        m_queue.push(data);
        pthread_mutex_unlock(&m_mutex);
        pthread_cond_signal(&m_consumer_cond);
        return true;
    }
    
    bool Pop(T& data)
    {
        pthread_mutex_lock(&m_mutex);
        while(m_queue.empty())
        {
            pthread_cond_wait(&m_consumer_cond, &m_mutex);
        }
        data = m_queue.front();
        m_queue.pop();
        pthread_mutex_unlock(&m_mutex);
        pthread_cond_signal(&m_producer_cond);
        return true;
    }
private:
    queue<T> m_queue;
    int m_capacity;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_producer_cond;
    pthread_cond_t m_consumer_cond;
};

void* thr_producer(void* qu)
{
    BlockQueue<int>* queue = (BlockQueue<int>*)qu;
    while(1)
    {
        int data = rand() % 1024;
        queue->Push(data);
        printf("+++I product a data %d\n", data);
        sleep(1);
    }
    return NULL;
}


void* thr_consumer(void* qu)
{
    BlockQueue<int>* queue = (BlockQueue<int>*)qu;
    while(1)
    {
        int data;
        queue->Pop(data);
        printf("---I consum a data %d\n", data);
        sleep(1);
    }
    return NULL;
}

int main()
{
    int ret;
    int i = 0;
    pthread_t producer_tid[MAX_CAPACITY], consumer_tid[MAX_CAPACITY];
    BlockQueue<int> qu;
    for(i = 0; i < MAX_CAPACITY; i++)
    {
        ret = pthread_create(&producer_tid[i], NULL, thr_producer, (void*)&qu);
        if(ret != 0)
        {
            perror("pthread_create error");
        }

        ret = pthread_create(&consumer_tid[i], NULL, thr_consumer, (void*)&qu);
        if(ret != 0)
        {
            perror("pthread_create error");
        }
    }

    for(i = 0; i < MAX_CAPACITY; i++)
    {
        pthread_join(producer_tid[i], NULL);
        pthread_join(consumer_tid[i], NULL);
    }
    return 0;
}
