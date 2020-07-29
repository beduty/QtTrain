#include "session.h"
#include <iostream>
Session::Session(boost::asio::io_service &io_service):m_Socket(io_service)
{

}

void Session::PostReceive()
{
    // m_Socket.async_read_some을 해줘야, 데이터를 받을 수 있다.

    memset(&m_ReceiveBuffer, '\0', sizeof (m_ReceiveBuffer));
    m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
                             boost::bind(&Session::handle_recieve, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
    // m_ReceiveBuffer는 받은 데이터가 저장되는 버퍼이다.
    // 데이터가 들어오면, Session::handle_recieve가 비동기로 호출된다.
}

void Session::handle_recieve(const boost::system::error_code &error, size_t bytes_transferred2)
{
    // 인자로 같이 들어온 error로 에러처리할 수 있다.
    if(error)
    {
        if(error == boost::asio::error::eof)
        {
            std::cout << "Disconnected from Client" << std::endl;
        }
        else
        {
            std::cout << "error No: " << error.value() << " error Message: "
                << error.message() << std::endl;
        }
    }
    else
    {
        const std::string strRecvMessage = m_ReceiveBuffer.data();
        std::cout<<"Message From Client : " << strRecvMessage<< ", Msg Size : " << bytes_transferred2 <<std::endl;

        // 돌려줄 메시지를 만든다. (Echo)
        char szMessage[128] = {0,};
        sprintf_s(szMessage, 128-1, "Re : %s", strRecvMessage.c_str());
        m_WriteMessage = szMessage;

        // 소켓에 데이터 넣어주면, 연결된 클라이언트로 전송된다.
        // 전송이 완ㄹ료되면 비동기로 호출될 수 있게끔, handle_write함수도 정의한다.
        boost::asio::async_write(m_Socket, boost::asio::buffer(m_WriteMessage),
                                 boost::bind(&Session::handle_write, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred)
                                 );

        // 데이터를 다시 받을 수 있게끔, m_Socket.async_read_some을 해줘야 한다!!
        PostReceive();
    }
}

void Session::handle_write(const boost::system::error_code &, size_t)
{

}
