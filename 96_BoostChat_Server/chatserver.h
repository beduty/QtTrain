#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include "Protocol.h"
#include "Seversession.h"

class ChatServer
{
public:
    ChatServer(boost::asio::io_service& io_service);
    ~ChatServer();
public:
    void Init(const int nMaxSessionCount);
    void Start();
    void CloseSession(const int nSessionId);
    void ProcessPacket(const int nSessionId,const char*pData);

private:
    bool PostAccept();
    void handle_accept(Session* pSession, const boost::system::error_code& error);

private:
    std::vector<Session*> m_SessionList;
    /* 연결된 클라이언트 정보를 vector를 사용하였다.
     * 각 Session(클라이언트)는 ChatServer::Init()함수로 초기화한다.
     * nMaxSessionCount만큼 미리 할당한다!*/

    std::deque<int> m_SessionQueue;
    /*아직 사용하지 않는 Session의 Index번호를 저장한다.
     * 클라이언트로 부터 접속요청을 받을때마다 std::deque Queue에서
     * 사용하지 않는 세션번호를 가져와서 async_accept에 사용한다.*/

private:
    int m_nSeqNumber;
    bool m_bIsAccepting;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::io_service* m_io_service;
};

#endif // CHATSERVER_H
