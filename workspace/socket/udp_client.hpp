#include "udp_socket.hpp"

class UdpClient
{
public:
    UdpClient(const string& ip, uint16_t prot)
        :m_ip(ip)
         ,m_prot(prot)
    {
        assert(m_sock.Socket());
    }

    ~UdpClient()
    {
        m_sock.Close();
    }

    bool RecvFrom(string* buf)
    {
        return m_sock.RecvFrom(buf);
    }

    bool SendTo(const string& buf)
    {
        return m_sock.SendTo(buf, m_ip, m_prot);
    }

private:
    UdpSocket m_sock;
    string m_ip;
    uint16_t m_prot;
};
