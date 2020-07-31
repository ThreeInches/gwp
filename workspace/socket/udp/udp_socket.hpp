#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace std;

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

class UdpSocket
{
public:
    UdpSocket()
        :m_fd(-1)
    {

    }

    bool Socket()
    {
        m_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if(m_fd < 0)
        {
            perror("socket error\n");
            return false;
        }

        return true;
    }

    bool Close()
    {
        close(m_fd);
        return true;
    }

    bool Bind(const string& ip, uint16_t prot)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(prot);
        int ret = bind(m_fd, (sockaddr*)&addr, sizeof(addr));
        if(ret < 0)
        {
            perror("bind error\n");
            return false;
        }

        return true;
    }

    bool RecvFrom(string* buf, string* ip = NULL, uint16_t* prot = NULL)
    {
        char tmp[1024 * 10] = { 0 };
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        ssize_t read_size = recvfrom(m_fd, tmp, sizeof(tmp) - 1, 0, (sockaddr*)&peer, &len);
        if(read_size < 0)
        {
            perror("recvfrom error\n");
            return false;
        }

        buf->assign(tmp, read_size);

        if(ip != NULL)
        {
            *ip = inet_ntoa(peer.sin_addr);
        }
        if(prot != NULL)
        {
            *prot = ntohs(peer.sin_port);
        }
        return true;
    }

    bool SendTo(const string& buf, const string& ip, uint16_t prot)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(prot);
        ssize_t write_size = sendto(m_fd, buf.data(), buf.size(), 0, (sockaddr*)&addr, sizeof(addr));
        if(write_size < 0)
        {
            perror("sedto, error\n");
            return false;
        }

        return true;
    }

private:
    int m_fd;
};
