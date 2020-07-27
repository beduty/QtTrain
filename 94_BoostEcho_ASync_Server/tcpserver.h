#ifndef TCPSERVER_H
#define TCPSERVER_H

#include<boost/asio.hpp>
#include "session.h"

class TcpServer
{
public:
    TcpServer(boost::asio::io_service& io_service);
    ~TcpServer();
private:
    void startAccept();
    void handle_accept(Session* pSession, const boost::system::error_code& error);

private:
    int m_nSeqNumber;
    boost::asio::ip::tcp::acceptor m_acceptor;
    Session* m_pSession;
    boost::asio::io_service *m_ioService;
};

#endif // TCPSERVER_H
