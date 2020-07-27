#ifndef SESSION_H
#define SESSION_H

#include <algorithm>
#include <string>
#include <list>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

class Session
{
public:
    Session(boost::asio::io_service& io_service);
    boost::asio::ip::tcp::socket& socket(){return m_Socket;};
    void PostReceive();

private:
    void handle_write(const boost::system::error_code&, size_t);
    void handle_recieve(const boost::system::error_code& , size_t);
private:
    std::string     m_WriteMessage;
    std::array<char, 128>   m_ReceiveBuffer;
    boost::asio::ip::tcp::socket    m_Socket;
};

#endif // SESSION_H
