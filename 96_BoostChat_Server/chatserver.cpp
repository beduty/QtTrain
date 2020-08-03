#include "chatserver.h"
ChatServer::ChatServer(boost::asio::io_service &io_service)
    :m_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT_NUMBER))
{
    m_io_service = &io_service;
    m_bIsAccepting = false;
}

ChatServer::~ChatServer()
{
    for(size_t i  = 0; i < m_SessionList.size(); ++i ){
        if(m_SessionList[i]){
            m_SessionList[i]->Socket().close();
        }
        delete m_SessionList[i];
    }
}

void ChatServer::Init(const int nMaxSessionCount)
{
    for(int i = 0; i < nMaxSessionCount; ++i)
    {
        // nMaxSessionCount만큼 세션공간을 만든다.(클라이언트 정보가 저장된다.)
        Session* pSession = new Session(i, *m_io_service, this);
        m_SessionList.push_back(pSession);
        m_SessionQueue.push_back(i);
    }
}

void ChatServer::Start()
{
    std::cout << "Server Start.." << std::endl;
    PostAccept();
}

bool ChatServer::PostAccept()
{
    // m_SessionQueue가 empty이면 MAX_SESSION_COUNT 만큼 클라이언트가 연결된 상태!
    if(true == m_SessionQueue.empty()){
        m_bIsAccepting = false;
        return false;
    }
    m_bIsAccepting = true;

    // 사용하지 않는 세션번호 하나 가져온다.
    int nSessionID = m_SessionQueue.front();
    m_SessionQueue.pop_front();

    // 클라이언트로부터 연결요청받으면, 할당해놓은 소켓에서 새로운 연결을 받아들인다.
    m_acceptor.async_accept(m_SessionList[nSessionID]->Socket(),
                            boost::bind(&ChatServer::handle_accept, this,
                                        m_SessionList[nSessionID],
                                        boost::asio::placeholders::error)
                            );
    return true;
}

void ChatServer::handle_accept(Session *pSession, const boost::system::error_code &error)
{
    // 클라이언트 연결되면 콜백된다.
    if(!error)
    {
        std::cout << "Client Connected! Session Id : " << pSession->SessionID() << std::endl;
        pSession->Init(); // 접속처리되면,
        pSession->PostReceive(); // 연결된 곳(클라이언트)로부터 데이터 받을 준비를 한다.
        PostAccept(); // 또 다시 연결 받기 위한 준비를 한다.
    }
    else{
        std::cout << "Error No : " << error.value() << " error Message : " << error.message() << std::endl;
    }
}

void ChatServer::CloseSession(const int nSessionId)
{
    std::cout << "Client Connection Exit. Session Id : " << nSessionId << std::endl;

    // 클라이언트 연결이 해제되고, 사용하던 nSessionId는 재활용할 수 있으므로,
    // Queue에 Id를 넣는다.
    m_SessionList[nSessionId]->Socket().close();
    m_SessionQueue.push_back(nSessionId);

    if(m_bIsAccepting == false)
        PostAccept(); // 여기서는 모든 클라이언트들이 해제될 때서야만 Server가 다시 Accept가된다.
}

void ChatServer::ProcessPacket(const int nSessionId, const char *pData)
{
    PACKET_HEADER* pheader = (PACKET_HEADER*) pData;
    switch (pheader->nID)
    {
    case REQ_IN:{
            PKT_REQ_IN* pPacket = (PKT_REQ_IN*) pData;
            m_SessionList[nSessionId]->SetName(pPacket->szName);
            std::cout << "Client Log In!   Name : " << m_SessionList[nSessionId]->GetName() << std::endl;
            PKT_RES_IN SendPkt;
            SendPkt.Init();
            SendPkt.bIsSucess = true;
            // 클라이언트에게 로그인 요청의 결과(true)를 보내준다.
            m_SessionList[nSessionId]->PostSend(false, SendPkt.nSize,(char*)&SendPkt);
        }
        break;
    case REQ_CHAT:{
            PKT_REQ_CHAT* pPacket = (PKT_REQ_CHAT*) pData;
            PKT_NOTICE_CHAT SendPkt;
            SendPkt.Init();
            strncpy_s(SendPkt.szName, MAX_NAME_LEN, m_SessionList[nSessionId]->GetName(), MAX_NAME_LEN-1);
            strncpy_s(SendPkt.szMessage, MAX_MESSAGE_LEN, pPacket->szMessage, MAX_NAME_LEN-1);

            size_t nTotalSessionCount = m_SessionList.size();
            for(size_t i = 0; i < nTotalSessionCount; ++i)
            {
                if(m_SessionList[i]->Socket().is_open())
                    m_SessionList[i]->PostSend(false, SendPkt.nSize, (char*)&SendPkt);
            }
        }
        break;
    }
    return;
}






















