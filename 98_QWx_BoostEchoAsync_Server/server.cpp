#include "server.h"
#include <QDebug>

Server::Server(int nPortNum, int nMaxSessionCount)
    : m_acceptor(m_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), nPortNum))
    , work(new boost::asio::io_service::work(m_ioService))
{
    m_bIsAccepting = false;

    for(int i = 0; i < nMaxSessionCount; ++i)
    {
        Session* pSession = new Session(m_ioService,i,this);
        m_SessionList.push_back(pSession);
        m_SessionQueue.push_back(i);
        connect(pSession, SIGNAL(send_message(QString, QString)), this, SLOT(onMessage(QString, QString)));
        connect(pSession, SIGNAL(login_user(int, QString)), this, SLOT(onUserLogin(int, QString)));
    }

    if(true == m_SessionQueue.empty())
    {
        m_bIsAccepting = false;
        return;
    }
    m_bIsAccepting = true;

    // 사용하지 않는 세션번호 하나 가져온다.
    int nSessionID = m_SessionQueue.front();
    m_SessionQueue.pop_front();

    // 클라이언트로부터 연결요청받으면, 할당해놓은 소켓에서 새로운 연결을 받아들인다.
    m_acceptor.async_accept(m_SessionList[nSessionID]->socket(),
                            boost::bind(&Server::handle_accept, this,
                                        m_SessionList[nSessionID],
                                        boost::asio::placeholders::error)
                            );
    worker = std::thread([&](){
        m_ioService.run();
    });
}

void Server::onMessage(const QString &name, const QString & msg)
{
    emit send_message(name, msg);
	size_t nTotalSessionCnt = m_SessionList.size();
	for (size_t i = 0; i < nTotalSessionCnt; ++i)
	{
		if (m_SessionList[i]->socket().is_open()) {
			QString szData = name + " : " + msg;
			m_SessionList[i]->PostSend(szData.size(), szData.toLocal8Bit().data());
		}
	}
}

void Server::onUserLogin(int nID, const QString &msg)
{
    emit login_user(nID, msg);
}

Server::~Server()
{
    m_ioService.stop();
    worker.join();
    work.reset();
    for(size_t i  = 0; i < m_SessionList.size(); ++i ){
        if(m_SessionList[i]){
            m_SessionList[i]->socket().close();
        }
        delete m_SessionList[i];
    }
}

void Server::startAccept()
{
//    qDebug() << "Client Listening...";
//    Session* pSession = new Session(m_ioService,0,this);
//    m_acceptor.async_accept(m_pSession->socket(),
//                            boost::bind(&Server::handle_accept, this,
//                                        m_pSession, boost::asio::placeholders::error)
//                            );
//    emit acceptClient();
}

void Server::handle_accept(Session *pSession, const boost::system::error_code &error)
{
    if(!error)
    {
        emit acceptClient();
        qDebug() << "Client Connect Success!!";
        pSession->PostReceive();
		{
			if (true == m_SessionQueue.empty())
			{
				m_bIsAccepting = false;
				return;
			}
			m_bIsAccepting = true;

			// 사용하지 않는 세션번호 하나 가져온다.
			int nSessionID = m_SessionQueue.front();
			m_SessionQueue.pop_front();

			// 클라이언트로부터 연결요청받으면, 할당해놓은 소켓에서 새로운 연결을 받아들인다.
			m_acceptor.async_accept(m_SessionList[nSessionID]->socket(),
				boost::bind(&Server::handle_accept, this,
					m_SessionList[nSessionID],
					boost::asio::placeholders::error)
			);
		}
    }
}
