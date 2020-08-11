#include <iostream>
#include <unistd.h>
#include <string>
#include <fcntl.h>
#include <time.h>
#include <sys/select.h>

using namespace std;

int main()
{
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);

    timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    while(1)
    {
        cout << "开始监控" << endl;
        int ret = select(0 + 1, &fds, NULL, NULL, &tv);
        if(ret < 0)
        {
            cout << "select error" << endl;
            return -1;
        }
        else if(ret == 0)
        {
            cout << "wait timeout" << endl;
            continue;
            sleep(10);
        }
        if(FD_ISSET(0, &fds))
        {
            cout << "从标准输入读取数据" << endl;
            char buf[1024] = { 0 };
            int read_size = read(0, buf, 1023);
            if(read_size < 0)
            {
                cout << "read error" << endl;
                FD_CLR(0, &fds);
                return -1;
            }
            cout << "read buf: " << buf << endl;
        }
    }
    return 0;
}
