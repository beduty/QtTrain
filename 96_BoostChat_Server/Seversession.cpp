#include "Seversession.h"
#include <iostream>
#include "chatserver.h"
Session::Session(int nSessionId, boost::asio::io_service &io_service, ChatServer *pServer)
    :m_nSessionID(nSessionId), m_serverSocket(io_service), m_pServer(pServer)
{

}

Session::~Session()
{
    while (m_SendDataQueue.empty() == false) {
        delete [] m_SendDataQueue.front();
        m_SendDataQueue.pop_front();
    }
}

void Session::Init()
{
    m_nPacketBufferMark= 0;
}

void Session::PostReceive()
{
    // 서버소켓에서는 async_read_some로 연결된 곳(클라이언트)에서 보낸 데이터를 받는다.
    // 받은 데이터는 m_ReveiveBuffer로 들어온다.
    m_serverSocket.async_read_some(
                boost::asio::buffer(m_ReveiveBuffer),
                boost::bind(&Session::handle_receive, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred)
                );
}

void Session::PostSend(const bool bImmediately, const int nSize, char *pData)
{
    char* pSendData = nullptr;
    if(false == bImmediately)
    {
        pSendData = new char[nSize];
        memcpy(pSendData, pData, nSize);
        m_SendDataQueue.push_back(pSendData);
    }
    else
        pSendData = pData;

    if(bImmediately == false && m_SendDataQueue.size()>1)
    {
        return ;
    }


    // 비동기로 데이터를 전송할 때, 데이터 실체인 pSendData가 보내진다.
    // pSendData는 새로 할당한 데이터이다. 언제 지울까??
    // async_write는 비동기함수이므로, 데이터가 다 보내졌을때까지 지워지지 않는데, 그렇기 때문에 언제 데이터를 지워야 할지 애매하다.
    // 만약 비동기함수 호출하고 바로 지우게되면, 데이터가 이상하게 짤려서 보내질 것이다.
    // 그래서 m_SendDataQueue에 데이터를 저장한다. 다 보내지고나서, handle_write가 호출될 때 m_SendDataQueue에 저장해놓았던 데이터를 지운다!
    boost::asio::async_write(m_serverSocket, boost::asio::buffer(pSendData, nSize),
                             boost::bind(&Session::handle_write, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
}

void Session::handle_write(const boost::system::error_code &error, size_t bytes_transferred)
{
    delete[] m_SendDataQueue.front();
    m_SendDataQueue.pop_front();
    if(m_SendDataQueue.empty() == false)
    {
        char* pData = m_SendDataQueue.front();
        PACKET_HEADER* pHeader = (PACKET_HEADER*)pData;
        PostSend(true, pHeader->nSize, pData);
    }
}

void Session::handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    // 연결된 곳(클라이언트)에서 데이터 받으면 콜백된다.
    if(error)
    {
        if(error == boost::asio::error::eof){
            std::cout<< "Disconnected from Client!" << std::endl;
        }
        else{
            std::cout << "Error No : " << error.value() << "  error Message : " << error.message() << std::endl;
        }
        m_pServer->CloseSession(m_nSessionID);
    }
    else{
        // 받은 데이터를 패킷 버퍼에 저장.
        memcpy(&m_PacketBuffer[m_nPacketBufferMark], m_ReveiveBuffer.data(), bytes_transferred);
        int nPacketData = m_nPacketBufferMark + bytes_transferred;
        int nReadData = 0;

        // 받은 데이터를 모두 처리할 때까지 반복
        while (nPacketData >0 )
        {
            // 이상한 데이터 들어온건지 검사한다. (1차 필터링)
            if(nPacketData < sizeof (PACKET_HEADER))
                break;

            // 처리할 수 있는만큼 데이터가 있다면 패킷을 처리.
            // pHeader->nSize는 PACKET_HEADER를 상속받은 PKT_REQ_IN또는 PKT_REQ_CHAT의 크기가 전달된다.
            // 클라이언트에서 연속되어 보내면, 데이터가 붙어서 들어오는 경우가 있는데, 이를 대비하여,
            // pHeader->nSize만 받는다. 남은 데이터는 저장했다가, 그다음에는 잘려서 들어오는 데이터와 붙여서 처리한다.
            PACKET_HEADER* pHeader = (PACKET_HEADER*)&m_PacketBuffer[nReadData];
            if(nPacketData >= pHeader->nSize)
            {
                // 패킷처리할만큼 데이터가 들어왔다면 처리.
                m_pServer->ProcessPacket(m_nSessionID, &m_PacketBuffer[nReadData]);
                nPacketData -= pHeader->nSize;
                nReadData += pHeader->nSize;
            }
            else
            {
                // 패킷처리할만큼 데이터가 들어오지 않았다면 중단!.
                break;
            }
        }
        if(nPacketData > 0)
        {
            // 여기는 클라이언트의 연속된 데이터 송신으로인하여 데이터가 붙어서 들어왔고, 그로인해서
            // pHeader->nSize만큼 쓰고 남은 데이터들이 있는 경우에 들어온다.
            // 남은 데이터는 m_PacketBuffer에 저장되어, 다음에 짤려들어올 데이터를 뒤에 붙여서 사용한다.

            // nPacketData -= pHeader->nSize;
            // nReadData += pHeader->nSize; 된 상황에서 nPacketData는 쓰고 남은 데이터의 크기이다.
            // nReadData는 붙어서 들어온 데이터중 쓰고 남은 데이터의 첫 시작점 Idx가된다.
            char TempBuffer[MAX_RECEIVE_BUFFER_LEN] = {0,};
            memcpy(&TempBuffer[0], &m_PacketBuffer[nReadData], nPacketData); // 남은 데이터가 저장된다.
            memcpy(&m_PacketBuffer[0], &TempBuffer[0], nPacketData); // 다음 데이터 들어올것을 대비하여 0번부터 다시 채운다.
        }
        m_nPacketBufferMark = nPacketData;
        // 남은 데이터를 m_PacketBuffer의 0번Idx부터 채웠고, 그다음 들어오는 데이터는 m_nPacketBufferMark부터
        // 채워나가면, 끊어져서 들어오는 데이터들도 제대로 다시 받을 수 있다!!!
        // 정상적인 데이터가 들어왔다면, nPacketData는 0일 것이므로, m_nPacketBufferMark은 0이되어 처음부터 그냥 데이터 받으면 된다!
        PostReceive();// 다시 데이터 받을 준비한다!
    }
}























