#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cassert>
#include <fcntl.h>

using namespace std;

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

#define CHECK_RET(exp) if(!exp){return false;}
#define BACKLOG 10

class TcpSocket
{
public:
    TcpSocket()
        :m_fd(-1)
    {

    }

    TcpSocket(int fd)
        :m_fd(fd)
    {

    }

    bool Socket()
    {
        m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(m_fd < 0)
        {
            perror("socket errror");
            return false;
        }
        printf("open fd = %d\n", m_fd);
        return true;
    }

    
    bool Close() const
    {
        close(m_fd);
        printf("close fd = %d\n", m_fd);
        return true;
    }

    bool Bind(const string& ip, uint16_t port) const
    {
       sockaddr_in addr;
       addr.sin_family = AF_INET;
       addr.sin_addr.s_addr = inet_addr(ip.c_str());
       addr.sin_port = htons(port);
       int ret = bind(m_fd, (sockaddr*)&addr, sizeof(addr));
       if(ret < 0)
       {
           perror("bind error");
           return false;
       }
       return true;
    }

    bool Listen(int backlog = BACKLOG)
    {
       int ret = listen(m_fd, backlog);
       if(ret < 0)
       {
           perror("listen error");
           return false;
       }
       return true;
    }

    bool Accept(TcpSocket* peer, string* ip = NULL, uint16_t* port = NULL)
    {
        sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        int new_sock = accept(m_fd, (sockaddr*)&peer_addr, &len);
        if(new_sock < 0)
        {
            perror("accept error");
            return false;
        }

        printf("accept fd = %d\n", new_sock);
        peer->m_fd = new_sock;
        if(ip != NULL)
        {
            *ip = inet_ntoa(peer_addr.sin_addr);
        }
        if(port != NULL)
        {
            *port = ntohs(peer_addr.sin_port);
        }
        return true;
    }

    bool Recv(string* buf) const
    {
        buf->clear();
        char tmp[1024 * 10] = { 0 };
        ssize_t read_size = recv(m_fd, tmp, sizeof(tmp), 0);
        if(read_size < 0)
        {
            perror("recv error");
            return false;
        }
        if(read_size == 0)
        {
            return false;
        }
        buf->assign(tmp, read_size);
        return true;
    }

    bool Send(const string& buf) const
    {
        ssize_t wirte_size = send(m_fd, buf.data(), buf.size(), 0);
        if(wirte_size < 0)
        {
            perror("send error");
            return false;
        }
        return true;
    }

    bool Connect(const string& ip, const uint16_t port) const
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        int ret = connect(m_fd, (sockaddr*)&addr, sizeof(addr));
        if(ret < 0)
        {
            perror("connect error");
            return false;
        }
        return true;
    }

    bool GetFd()
    {
        return m_fd;
    }

private:
    int m_fd;
};
