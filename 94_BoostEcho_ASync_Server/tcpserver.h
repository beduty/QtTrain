#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<boost/asio.hpp>
#include "session.h"

//   Session클래스는 서버에 접속한 클라이언트(ip::tcp::socket)이며,
// 데이터 송신, 수신을 한다.
//   TcpServer클래스는 Session클래스는 가지며,
// 클라이언트의 접속을 받아들이는 기능을 한다.
class TcpServer
{
public:
    TcpServer(boost::asio::io_service& io_service);
    ~TcpServer();
private:
    // 클라이언트의 접속을 받아들인다.
    void startAccept();
    boost::asio::ip::tcp::acceptor m_acceptor;

private:
    void handle_accept(Session* pSession, const boost::system::error_code& error);

private:
    int m_nSeqNumber;
    Session* m_pSession;
    boost::asio::io_service *m_ioService;
};

#endif // TCPSERVER_H
