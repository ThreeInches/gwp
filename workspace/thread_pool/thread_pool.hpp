#include <iostream>
#include <stdlib.h>
#include <queue>
#include <pthread.h>
#include <unistd.h>

using namespace std;

typedef void(*handler_t)(int data);

#define MAX_TID 10
#define MAX_CAPACITY 10

class MyTask
{
public:
    MyTask()
    {

    }

    void SetTask(int data, handler_t handler)
    {
        m_data = data;
        m_handler = handler;
    }

    void Run()
    {
        return m_handler(m_data);
    }
private:
    int m_data;
    handler_t m_handler;
};

class ThreadPool
{
public:
   ThreadPool(int cap = MAX_CAPACITY)
       :m_max(cap)
    {
        pthread_mutex_init(&m_mutex, NULL);
        pthread_cond_init(&m_cond, NULL);
        pthread_t tid;
        int ret;
        for(int i = 0; i < m_max; i++)
        {
            ret = pthread_create(&tid, NULL, thr_start, this);
            if(ret != 0)
            {
                cout << "pthread_creat failed" << endl;
                exit(-1);
            }
        }
    }

   ~ThreadPool()
   {
       pthread_mutex_destroy(&m_mutex);
       pthread_cond_destroy(&m_cond);
   }

   void Push(const MyTask& data)
   {
       pthread_mutex_lock(&m_mutex);
       m_qu.push(data);
       pthread_mutex_unlock(&m_mutex);
       pthread_cond_broadcast(&m_cond);
   }

   static void* thr_start(void* arg)
   {
       ThreadPool* ptr = (ThreadPool*)arg;
       while(1)
       {
           pthread_mutex_lock(&ptr->m_mutex);
           while(ptr->m_qu.empty())
           {
               pthread_cond_wait(&ptr->m_cond, &ptr->m_mutex);
           }
           MyTask task;
           task = ptr->m_qu.front();
           ptr->m_qu.pop();
           pthread_mutex_unlock(&ptr->m_mutex);
           task.Run();
       }
       return NULL;
   }
private:
    int m_max;
    queue<MyTask> m_qu;
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};
