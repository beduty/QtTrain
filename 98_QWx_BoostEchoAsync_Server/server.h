#ifndef SERVER_H
#define SERVER_H
#include <boost/asio.hpp>
#include "session.h"
#include <thread>
#include <QObject>
class Server : public QObject
{
	Q_OBJECT
public:
    Server(int nPortNum, int nMaxSessionCount);
    ~Server();
    //Session* getSession(){return m_pSession;}
private:
    void startAccept();
    void handle_accept(Session* pSession, const boost::system::error_code& error);
private slots:
    void onMessage(const QString& name,const QString& msg);
    void onUserLogin(int ,const QString& msg);
signals:
    void send_message(const QString& name, const QString& msg);
    void acceptClient();
    void login_user(int nID, const QString& msg);
private:
    //Session* m_pSession = nullptr;
    std::vector<Session*> m_SessionList;
    std::deque<int> m_SessionQueue;
    bool m_bIsAccepting;
    boost::asio::io_service m_ioService;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::shared_ptr<boost::asio::io_service::work> work;
    std::thread worker;
};

#endif // SERVER_H
