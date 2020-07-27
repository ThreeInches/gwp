#include <iostream>
#include <thread>
#include <mutex>
#include <cstdio>

using namespace std;

class singleton
{
public:
    int* GetInstance()
    {
        return &m_data;
    }
private:
    static int m_data;
};

int singleton::m_data = 10;

int main()
{
    singleton a;
    singleton b;
    
    printf("a = %p\n", a.GetInstance());
    printf("b = %p\n", b.GetInstance());
    return 0;
}
