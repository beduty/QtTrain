#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "boost/bind.hpp"
#include "boost/asio.hpp"

const char SERVER_IP[] = "127.0.0.1";
const unsigned short PORT_NUMBER = 31400;

class TcpClient
{
public:
    TcpClient(boost::asio::io_service& io_service);
    void Connect(boost::asio::ip::tcp::endpoint& endpoint);
private:
    void PostWrite();
    void handle_connect(const boost::system::error_code& error);
    void handle_write(const boost::system::error_code&, size_t);
private:
    boost::asio::io_service& m_io_service;
    boost::asio::ip::tcp::socket m_Socket;
    int m_nSeqNumber;
    std::array<char, 128> m_ReceiveBuffer;
    std::string m_WriteMessage;
};

#endif // TCPCLIENT_H
