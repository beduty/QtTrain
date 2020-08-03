#include "chatclient.h"
#include <iostream>

ChatClient::ChatClient(boost::asio::io_service &io_service)
    :m_IOService(io_service),
      m_ClientSocket(io_service)
{
    m_bIsLogin = false;
    InitializeCriticalSectionAndSpinCount(&m_lock, 4000);
}

ChatClient::~ChatClient()
{
    EnterCriticalSection(&m_lock);
    while (false == m_SendDataQueue.empty())
    {
        delete[] m_SendDataQueue.front();
        m_SendDataQueue.pop_front();
    }
    LeaveCriticalSection(&m_lock);
    DeleteCriticalSection(&m_lock);
}

void ChatClient::Connect(boost::asio::ip::tcp::endpoint endpoint)
{
    m_nPacketBufferMark = 0;
    m_ClientSocket.async_connect(endpoint,
                                 boost::bind(&ChatClient::handle_connect, this,
                                             boost::asio::placeholders::error)
                                 );
}

void ChatClient::Close()
{
    if(m_ClientSocket.is_open())
        m_ClientSocket.close();
}

void ChatClient::PostSend(const bool bImmediately, const int nSize, char *pData)
{
    char* pSendData = nullptr;
    EnterCriticalSection(&m_lock);
    if(false == bImmediately)
    {
        pSendData = new char[nSize];
        memcpy(pSendData, pData, nSize);
        m_SendDataQueue.push_back(pSendData);
    }
    else
        pSendData = pData;

    if(bImmediately || m_SendDataQueue.size() < 2)
    {
        boost::asio::async_write(m_ClientSocket, boost::asio::buffer(pSendData, nSize),
                                 boost::bind(&ChatClient::handle_write, this,
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred)
                                );
    }
    LeaveCriticalSection(&m_lock);
}

void ChatClient::PostReceive()
{
    memset(&m_ReceiveBuffer, '\0', sizeof (m_ReceiveBuffer));
    m_ClientSocket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
                                   boost::bind(&ChatClient::handle_receive, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred)
                                   );
}

void ChatClient::handle_connect(const boost::system::error_code &error)
{
    if(!error)
    {
        std::cout << "Server Connection Success!" << std::endl;
        std::cout << "Input your name : " << std::endl;
        PostReceive();
    }
    else
        std::cout << "Server Connection Fail. error No: " << error.value() << " error Message: " << error.message() << std::endl;
}

void ChatClient::handle_write(const boost::system::error_code &error, size_t bytes_transferred)
{
    EnterCriticalSection(&m_lock);
    delete[] m_SendDataQueue.front();
    m_SendDataQueue.pop_front();

    char* pData = nullptr;
    if(m_SendDataQueue.empty() == false)
        pData = m_SendDataQueue.front();
    LeaveCriticalSection(&m_lock);

    if(pData != nullptr){
        PACKET_HEADER* pHeader = (PACKET_HEADER*)pData;

//        switch (pHeader->nID)
//        {
//        case RES_IN:
//            {
//                PKT_RES_IN* pPacket = (PKT_RES_IN*)pData;
//                LoginOK();
//                if(pPacket->bIsSucess)
//                    std::cout << "Client Login :  Success" <<std::endl;
//                else
//                    std::cout << "Client Login :  Fail" <<std::endl;
//            }
//            break;
//        case NOTICE_CHAT:
//            {
//                PKT_NOTICE_CHAT* pPacket = (PKT_NOTICE_CHAT*)pData;
//                std::cout << pPacket->szName << " : " << pPacket->szMessage << std::endl;
//            }

//        }
        PostSend(true, pHeader->nSize+10, pData);
    }
}

void ChatClient::handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    if( error ){
        if( error == boost::asio::error::eof ){
            std::cout << "Disconnect From Client" << std::endl;
        }
        else{
            std::cout << "error No: " << error.value() << " error Message: " << error.message() << std::endl;
        }
        Close();
    }
    else{
        memcpy(&m_PacketBuffer[m_nPacketBufferMark], m_ReceiveBuffer.data(), bytes_transferred);
        int nPacketData = m_nPacketBufferMark + bytes_transferred;
        int nReadData =0;
        while (nPacketData > 0)
        {
            if(nPacketData < sizeof(PACKET_HEADER))
                break;
            PACKET_HEADER* pHeader = (PACKET_HEADER*)&m_PacketBuffer[nReadData];
            if(pHeader->nSize <= nPacketData)
            {
                ProcessPacket(&m_PacketBuffer[nReadData]);
                nPacketData -= pHeader->nSize;
                nReadData += pHeader->nSize;
            }
            else
                break;
        }

        if(nPacketData > 0)
        {
            char TempBuffer[MAX_RECEIVE_BUFFER_LEN] = {0,};
            memcpy(&TempBuffer[0], &m_PacketBuffer[nReadData], nPacketData);
            memcpy(&m_PacketBuffer[0], &TempBuffer[0], nPacketData);
        }
        m_nPacketBufferMark = nPacketData;
        PostReceive();
    }

}

void ChatClient::ProcessPacket(const char *pData)
{
    PACKET_HEADER* pheader = (PACKET_HEADER*) pData;
    switch (pheader->nID)
    {
    case RES_IN:
        {
            PKT_RES_IN* pPacket = (PKT_RES_IN*)pData;
            LoginOK();
            if(pPacket->bIsSucess)
                std::cout << "Client Login :  Success" <<std::endl;
            else
                std::cout << "Client Login :  Fail" <<std::endl;
        }
        break;
    case NOTICE_CHAT:
        {
            PKT_NOTICE_CHAT* pPacket = (PKT_NOTICE_CHAT*)pData;
            std::cout << pPacket->szName << " : " << pPacket->szMessage << std::endl;
        }

    }
}
