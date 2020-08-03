#include "session.h"
#include <QDebug>

Session::Session(boost::asio::io_service &io_service, int nSessionId, Server *pServer)
    :m_pServer(pServer),m_nSessionId(nSessionId), m_ServerSocket(io_service)
{

}

Session::~Session()
{
    m_ServerSocket.close();
}

void Session::PostReceive()
{
    memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));
    m_ServerSocket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
                                   boost::bind(&Session::handle_receive, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred)
                                   );
}

void Session::handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    if(error)
    {
        if(error == boost::asio::error::eof)
            qDebug() << "Disconnected From Client";
        else {
            qDebug() << "Error No : " << error.value() << " error message : " << error.message().c_str() ;
        }
    }
    else {
        PACKET_HEADER* pHeader = (PACKET_HEADER*)&m_ReceiveBuffer[0];
        if(pHeader->nID == REQ_IN)
        {
            qDebug() << "LogIn Request !!";
            auto pPacket = static_cast<PKT_REQ_IN*>(pHeader);
            SetName(pPacket->szName);
            QString szClientName = QString::fromLocal8Bit(pPacket->szName);
            qDebug() << szClientName << "LogIn Accepted!";
            emit login_user(m_nSessionId, szClientName);
        }
        else if(pHeader->nID == REQ_CHAT)
        {
            qDebug() << "Data In!!";
            auto pPacket = static_cast<PKT_REQ_CHAT*>(pHeader);
            qDebug() << "Msg from Client : " << pPacket->szMessage << ", Msg Size : " << bytes_transferred;

            //QString szText = "<<<<<<< Msg from Client : " + QString::fromUtf8(pPacket->szMessage);
            emit send_message(QString::fromStdString(m_Name), QString::fromUtf8(pPacket->szMessage));

            char szMsg[128] = {0,};
            sprintf_s(szMsg, 128-1, "Ack!");
            m_WriteMessage = szMsg;
            PostSend(m_WriteMessage.length(),szMsg);
        }
		PostReceive();
    }
}

void Session::PostSend(const int nSize, char *pData)
{
    char* pSendData = nullptr;
    pSendData = new char[nSize];
    memcpy(pSendData, pData , nSize);
    m_SendDataQueue.push_back(pSendData);
    boost::asio::async_write(m_ServerSocket, boost::asio::buffer(pSendData,nSize),
                             boost::bind(&Session::handle_write, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
}

void Session::handle_write(const boost::system::error_code &, size_t)
{
    delete[] m_SendDataQueue.front();
    m_SendDataQueue.pop_front();
    if(false == m_SendDataQueue.empty())
    {
        //char*
    }
    PostReceive();
}
