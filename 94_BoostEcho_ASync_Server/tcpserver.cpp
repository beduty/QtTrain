#include "tcpserver.h"
#include <iostream>

const unsigned short PORT_NUMBER = 31400;
TcpServer::TcpServer(boost::asio::io_service &io_service)
    : m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER))
{
    m_ioService = &io_service;
    m_pSession = nullptr;
    startAccept();
}

TcpServer::~TcpServer()
{
    if(m_pSession != nullptr)
        delete  m_pSession;
}

void TcpServer::startAccept()
{
    std::cout << "Client Listening..." << std::endl;
    m_pSession = new Session(*m_ioService);
    m_acceptor.async_accept(m_pSession->socket(),
                            boost::bind(&TcpServer::handle_accept, this,
                                        m_pSession, boost::asio::placeholders::error));

}

void TcpServer::handle_accept(Session *pSession, const boost::system::error_code &error)
{
    if(!error)
    {
        std::cout<< "Client Connect Success!!" << std::endl;
        pSession->PostReceive();
    }
}
