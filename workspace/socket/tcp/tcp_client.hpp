#include "tcp_socket.hpp"

class TcpClient
{
public:
    TcpClient(const string& ip, const uint16_t port)
        :m_ip(ip)
         ,m_port(port)
    {
        m_sock.Socket();
    }

    ~TcpClient()
    {
        m_sock.Close();
    }

    bool Connect()
    {
        return m_sock.Connect(m_ip, m_port);
    }

    bool Recv(string* buf)
    {
        return m_sock.Recv(buf);
    }

    bool Send(const string& buf)
    {
        return m_sock.Send(buf);
    }

private:
    TcpSocket m_sock;
    string m_ip;
    uint16_t m_port;
};
