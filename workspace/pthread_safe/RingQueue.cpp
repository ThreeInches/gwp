#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <semaphore.h>
#include <stdlib.h>

using namespace std;

#define MAX_CAPACITY 5
#define MAX_TID 4

template<class T>
class RingQueue
{
public:
    RingQueue(int cap = MAX_CAPACITY)
        :m_capacity(cap)
         ,m_array(cap)
    {
        m_producer_write = 0;
        m_consumer_read = 0;       
        sem_init(&m_mutex, 0, 1);
        sem_init(&m_producer_sem, 0, 0);
        sem_init(&m_consumer_sem, 0, cap);
    }

    ~RingQueue()
    {
        sem_destroy(&m_mutex);
        sem_destroy(&m_producer_sem);
        sem_destroy(&m_consumer_sem);
    }
    
    void Push(const int& data)
    {
        sem_wait(&m_consumer_sem);
        sem_wait(&m_mutex);
        m_array[m_producer_write] = data;
        m_producer_write = (m_producer_write + 1) % m_capacity;
        sem_post(&m_mutex);
        sem_post(&m_producer_sem); 
    }

    void Pop(int& data)
    {
        sem_wait(&m_producer_sem);
        sem_wait(&m_mutex);
        data = m_array[m_consumer_read];
        m_consumer_read = (m_consumer_read + 1) % m_capacity;
        sem_post(&m_mutex);
        sem_post(&m_consumer_sem);
    }
private:
    vector<T> m_array;
    int m_capacity;
    sem_t m_mutex;
    sem_t m_producer_sem;
    sem_t m_consumer_sem;
    int m_producer_write;
    int m_consumer_read;
};

void* thr_producer(void* queue)
{
    RingQueue<int>* qu = (RingQueue<int>*)queue;
    while(1)
    {
        int data = rand() % 1024;
        qu->Push(data);
        cout << "+++I producer a data:" << data << endl;
        sleep(1);
    }
    return NULL;
}

void* thr_consumer(void* queue)
{
    
    RingQueue<int>* qu = (RingQueue<int>*)queue;
    while(1)
    {
        int data;
        qu->Pop(data);
        cout << "---I consumer a data:" << data << endl;
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t producer_tid[MAX_TID];
    pthread_t consumer_tid[MAX_TID];
    int ret, i;
    RingQueue<int> queue;
    for(i = 0; i < MAX_TID; i++)
    {
        ret = pthread_create(&producer_tid[i], NULL, thr_producer, (void*)&queue);
        if(ret != 0)
        {
            perror("producer thread create failed\n");
        }
        ret = pthread_create(&consumer_tid[i], NULL, thr_consumer, (void*)&queue);
        if(ret != 0)
        {
            perror("producer thread create failed\n");

        }
    }

    for(i = 0; i < MAX_TID; i++)
    {
        pthread_join(producer_tid[i], NULL);
        pthread_join(consumer_tid[i], NULL);
    }

    return 0;
}
