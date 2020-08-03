#ifndef SESSION_H
#define SESSION_H
#include <deque>
#include <QObject>
#include "Protocol.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
class Server;
class Session : public QObject
{
	Q_OBJECT
public:
    Session(boost::asio::io_service& io_service, int nSessionId, Server* pServer);
    ~Session();
    boost::asio::ip::tcp::socket& socket(){return m_ServerSocket;}
    void PostReceive();
private:
    void handle_write(const boost::system::error_code&, size_t);
    void handle_receive(const boost::system::error_code&, size_t);
//////////////////////////////////////////////////////////////////
private:
    Server* m_pServer;
    std::string m_Name;
    std::deque<char*> m_SendDataQueue;
    int m_nSessionId;
    char m_PacketBuffer[MAX_RECEIVE_BUFFER_LEN*2];
public:
    void PostSend(const int nSize, char* pData);
    int SessionID() {return  m_nSessionId;}
    const char* GetName(){return  m_Name.c_str();}
    void SetName(const char* pszName){m_Name = pszName;}
//////////////////////////////////////////////////////////////////
private:
    std::string m_WriteMessage;
    std::array<char, MAX_RECEIVE_BUFFER_LEN> m_ReceiveBuffer;
    boost::asio::ip::tcp::socket m_ServerSocket;

signals:
    void send_message(const QString& name, const QString& msg);
    void login_user(int nID, const QString& msg);
};

#endif // SESSION_H
