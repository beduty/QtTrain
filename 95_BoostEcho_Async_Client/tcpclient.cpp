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
    // 비동기 접속을 위해서 async_connect(비동기버전)을 사용한다.
    // 접속완료된 이후에는 TcpClient::handle_connect 가 콜백된다.
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

        // 연결되면, 비동기함수로 async_write를 사용하여 서버로 데이터를 보낸다.
        // 비동기 함수 호출안하면 비동기 요청이 없기때문에 io_service.run()이 끝난다.
        PostWrite();
    }
}

void TcpClient::PostWrite()
{
    if(m_Socket.is_open() == false)
        return;

    if(m_nSeqNumber > 7)
    {
        // 연결을 끊는다.
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
    // 비동기로 데이터 보내고, 다시 받을 준비를 한다. async_read_some
    PostReceive();
}

void TcpClient::PostReceive()
{
    // 데이터를 받으면, handle_receive가 콜백된다.
    // 받고 나면 다시 Echo해준다.
    memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));
    m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
                             boost::bind(&TcpClient::handle_receive, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
}

void TcpClient::handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    if(error)
    {
        if(error == boost::asio::error::eof)
            std::cout<<"Disconnected from Server."<<std::endl;
        else
            std::cout << "Error No : " << error.value() << " error Message : "
                      << error.message() << std::endl;
    }
    else{
        const std::string strRecvMessage = m_ReceiveBuffer.data();
        std::cout << "Message from Server : " << strRecvMessage
                  << ",  Received Size : " << bytes_transferred << std::endl;

        PostWrite();
    }
}


void TcpClient::handle_write(const boost::system::error_code &, size_t)
{

}
















