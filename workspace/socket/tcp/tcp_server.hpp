#include "tcp_socket.hpp"
#include <functional>

typedef function<void(const string& req, string* resp)> Handler;

class TcpServer
{
public:
    TcpServer(const string& ip, uint16_t port)
        :m_ip(ip)
         ,m_port(port)
    {

    }

    bool Start(Handler handler)
    {
        CHECK_RET(m_listen_sock.Socket());
        CHECK_RET(m_listen_sock.Bind(m_ip, m_port));
        CHECK_RET(m_listen_sock.Listen(5));
        
        while(1)
        {
            TcpSocket new_sock;
            string ip;
            uint16_t port = 0;
            if(!m_listen_sock.Accept(&new_sock, &ip, &port))
            {
                continue;
            }
            printf("[client %s %d] connect!\n", ip.c_str(), port);
            while(1)
            {
                string req;
                int ret = new_sock.Recv(&req);
                if(ret != 0)
                {
                    printf("[client %s %d] disconnect!\n", ip.c_str(), port);
                    new_sock.Close();
                    break;
                }
                string resp;
                handler(req, &resp);
                new_sock.Send(resp);
                printf("[%s:%d] req:%s, resp:%s\n", ip.c_str(), port, req.c_str(), resp.c_str());
            }
        }

        return true;
    }
private:
    TcpSocket m_listen_sock;
    string m_ip;
    uint16_t m_port;
};
