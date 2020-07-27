#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex m_mutex;
class singleton
{
public:
    int* GetInstance()
    {
        if(m_data == NULL)
        {
            m_mutex.lock();
            if(m_data == NULL)
            {
                m_data = new int();
            }
            m_mutex.unlock();
        }
        return (int*)m_data;
    }
private:
    volatile static int* m_data;
};

volatile int* singleton::m_data = NULL;

int main()
{
    singleton a;
    singleton b;

    cout << "a = " << a.GetInstance() << endl;
    cout << "b = " << b.GetInstance() << endl;

    return 0;
}
