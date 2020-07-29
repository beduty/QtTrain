#ifndef SESSION_H
#define SESSION_H

#include <algorithm>
#include <string>
#include <list>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

//   Session클래스는 서버에 접속한 클라이언트(ip::tcp::socket)이며,
// 데이터 송신, 수신을 한다.
//   TcpServer클래스는 Session클래스는 가지며,
// 클라이언트의 접속을 받아들이는 기능을 한다.
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
