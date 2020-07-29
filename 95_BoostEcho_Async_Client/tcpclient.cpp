#include "tcpclient.h"
#include <iostream>
TcpClient::TcpClient(boost::asio::io_service &io_service):
    m_io_service(io_service),
    m_Socket(io_service),
    m_nSeqNumber(0)
{

}

void TcpClient::Connect(boost::asio::ip::tcp::endpoint &endpoint)
{
    m_Socket.async_connect(endpoint,
                           boost::bind(&TcpClient::handle_connect,
                                       this,
                                       boost::asio::placeholders::error));
}

void TcpClient::handle_connect(const boost::system::error_code &error)
{
    if(error)
        std::cout<<"Connect Failed : " << error.message() << std::endl;

    else{
        std::cout << "Connected" << std::endl;
        PostWrite();
    }
}

void TcpClient::PostWrite()
{
    if(m_Socket.is_open() == false)
        return;

    if(m_nSeqNumber > 7)
    {
        m_Socket.close();
        return;
    }
    ++ m_nSeqNumber;

    char szMessage[128] = {0,};
    sprintf_s(szMessage, 128-1, "%d - Send Message", m_nSeqNumber);
    m_WriteMessage = szMessage;

    boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
                             boost::bind(&TcpClient::handle_write,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
    PostRec
}

void TcpClient::handle_write(const boost::system::error_code &, size_t)
{

}
