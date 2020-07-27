#include "thread_pool.hpp"

void func1(int data)
{
    int sec = (data % 3) + 1;
    cout << "thread:" << pthread_self() << "+++get data:" << data << "sleep:" << sec << endl;
    sleep(sec);
}

void func2(int data)
{
    cout << "func2 thread:" << pthread_self() << "---func2 data:" << data << endl;
    sleep(1);
}

int main()
{
    ThreadPool pool;
    srand((unsigned int)time(NULL));
    int value = rand() % 1024;

    for(int i = 0; i < MAX_CAPACITY; i++)
    {
        MyTask task;
        if(i % 2 == 0)
        {
            task.SetTask(value, func1);
        }
        else
        {
            task.SetTask(value, func2);
        }
        pool.Push(task);
    }

    sleep(1000);
    return 0;
}
