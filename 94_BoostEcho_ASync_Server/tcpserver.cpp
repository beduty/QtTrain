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

    // 세션(클라이언트, 소켓)을 받을 준비를 한다.
    m_pSession = new Session(*m_ioService);

    // 비동기로 접속을 처리한다.(접속될때까지 대기하지 않는다.)
    // 접속이 완료되면 호출할 콜백함수 (handle_accept(..))도 정의한다.
    m_acceptor.async_accept(m_pSession->socket(),
                            boost::bind(&TcpServer::handle_accept, this,
                                        m_pSession, boost::asio::placeholders::error));

}

void TcpServer::handle_accept(Session *pSession, const boost::system::error_code &error)
{
    // 비동기로 클라이언트 접속을 처리하고, 완료되면 콜백된다.
    // 해당 함수가 호출되면, 접속처리작업이 완료가 되었다는 뜻이된다!
    if(!error)
    {
        std::cout<< "Client Connect Success!!" << std::endl;

        // 접속이 성공했을 때, 접속한 클라이언트(세션)이 보내는 패킷을 받을 수있도록,
        // 소켓(세션, 클라이언트)에 받기작업을 요청해야 한다.
        // 해당작업을 하지 않으면 접속한 클라이언트가 보내는 데이터를 받지 못한다.
        // m_Socket.async_read_some을 해줘야, 데이터를 받을 수 있다.
        pSession->PostReceive();
    }
}
