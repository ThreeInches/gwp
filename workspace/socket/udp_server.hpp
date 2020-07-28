#include "udp_socket.hpp"
#include <functional>

typedef function<void(const string& rep, string* resp)> Handler;

class UdpServer
{
public:
    UdpServer()
    {
        assert(m_sock.Socket());
    }
    
    ~UdpServer()
    {
        m_sock.Close();
    }

    bool Start(const string& ip, uint16_t prot, Handler handler) 
    {
        bool ret = m_sock.Bind(ip, prot);
        if(!ret)
        {
            return false;
        }

        printf("Server started successfully\n");
        while(1)
        {
            string request;
            string remote_ip;
            uint16_t remote_prot;
            
            bool ret = m_sock.RecvFrom(&request, &remote_ip, &remote_prot);
            if(!ret)
            {
                continue;
            }

            string resp;
            handler(request, &resp);
            m_sock.SendTo(request, remote_ip, remote_prot);
            printf("[%s:%d]request:%s,resp:%s\n" ,remote_ip.c_str(), remote_prot, request.c_str(), resp.c_str());
        }
        m_sock.Close();
        return true;
    }

private:
    UdpSocket m_sock;
};
