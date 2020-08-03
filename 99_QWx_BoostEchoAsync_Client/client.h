#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Protocol.h"
#include <deque>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(boost::asio::ip::tcp::endpoint ep, QObject *parent = nullptr);
    ~Client();
    void Connect(boost::asio::ip::tcp::endpoint& endPoint);
	void SendMsg(QString&);
    void LogIn(QString szName);
private:
    void PostWrite(QString);
    void PostReceive();
    void handle_connect(const boost::system::error_code& err);
    void handle_write(const boost::system::error_code&, size_t);
    void handle_receive(const boost::system::error_code &error, size_t bytes_transferred);
private:
    int m_nSeqNumber;
    std::thread worker;
    std::string m_WriteMessage;
    std::array<char, MAX_RECEIVE_BUFFER_LEN> m_ReceiveBuffer;
    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::socket m_Socket;
signals:
    void receive_message(const QString& msg);
    void connectSuccess();
    void connectFail();

/////////////////////////////////////////////////////////
public:
    bool IsLogin() {return m_bIsLogin;}
    void LogInOK() {m_bIsLogin = true;}
private:
    bool m_bIsLogin = false;
    std::deque<char*> m_SendDataQueue;
/////////////////////////////////////////////////////////
};

#endif // CLIENT_H
