#ifndef SESSION_H
#define SESSION_H
#include <deque>
#include <Protocol.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

class ChatServer;
/*
    세션이란.. 서버에서 클라이언트 정보를 저장하기 위한 공간!
    세션 != 클라이언트 -> 세션 = 클라이언트가 연결된 "서버"공간.
*/
class Session
{
public:
    Session(int nSessionId, boost::asio::io_service& io_service, ChatServer* pServer);
    ~Session();
public:
    void Init();
    void PostReceive();
    void PostSend(const bool bImmediately, const int nSize, char* pData);
public:
    int SessionID() {return m_nSessionID;}
    const char* GetName(){return m_Name.c_str();}
    void  SetName(const char* pszName) {m_Name = pszName;}
    boost::asio::ip::tcp::socket& Socket() {return m_serverSocket;}

private:
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);


private:
    int m_nSessionID;
    boost::asio::ip::tcp::socket m_serverSocket;
    // 새로 연결된 클라이언트에 할당할 소켓

    std::array<char, MAX_RECEIVE_BUFFER_LEN> m_ReveiveBuffer;
    int m_nPacketBufferMark;
    char m_PacketBuffer[MAX_RECEIVE_BUFFER_LEN*2];
    std::deque<char*> m_SendDataQueue;
    std::string m_Name;
    ChatServer* m_pServer;
};

#endif // SESSION_H
