#ifndef CHATCLIENT_H
#define CHATCLIENT_H
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Protocol.h"
#include <deque>

class ChatClient
{
public:
    ChatClient(boost::asio::io_service& io_service);
    ~ChatClient();

public:
    bool IsConnecting(){return m_ClientSocket.is_open();}
    void LoginOK(){ m_bIsLogin = true; }
    bool IsLogin() {return m_bIsLogin;}
    void Connect(boost::asio::ip::tcp::endpoint endpoint);
    void Close();
    void PostSend(const bool bImmediately, const int nSize, char* pData);

private:
    void PostReceive();
    void handle_connect(const boost::system::error_code& error);
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void handle_receive(const boost::system::error_code& error, size_t bytes_transferred);
    void ProcessPacket(const char* pData);

private:
    boost::asio::io_service& m_IOService;
    boost::asio::ip::tcp::socket m_ClientSocket;

    std::array<char , 512> m_ReceiveBuffer;
    int m_nPacketBufferMark;
    char m_PacketBuffer[MAX_RECEIVE_BUFFER_LEN*2];
    CRITICAL_SECTION m_lock;
    std::deque<char*> m_SendDataQueue;
    bool m_bIsLogin;
};

#endif // CHATCLIENT_H
