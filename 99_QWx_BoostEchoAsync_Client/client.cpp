#include "client.h"
#include <QDebug>
//Client::Client(QObject *parent) : QObject(parent)
//  ,m_nSeqNumber(0)
//  , m_Socket(m_ioService)
//{
//    worker = std::thread([&](){
//        m_ioService.run();
//    });
//}

Client::Client(boost::asio::ip::tcp::endpoint ep, QObject *parent)
  : QObject(parent)
  , m_nSeqNumber(0)
  , m_Socket(m_ioService)
{
    Connect(ep);
    worker = std::thread([&](){
        m_ioService.run();
    });
}

Client::~Client()
{
    m_ioService.stop();
    worker.join();
    m_Socket.close();
}

void Client::PostReceive()
{
    memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));
    m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
                             boost::bind(&Client::handle_receive, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
}

void Client::Connect(boost::asio::ip::tcp::endpoint &endPoint)
{
    m_Socket.async_connect(endPoint,
                           boost::bind(&Client::handle_connect,
                                       this,
                                       boost::asio::placeholders::error)
                           );
	PostReceive();
}

void Client::SendMsg(QString &msg)
{
    if(m_Socket.is_open() == false)
        return;
    //PostWrite(msg);
    PKT_REQ_CHAT requestChat;
    requestChat.Init();
	strncpy_s(requestChat.szMessage, MAX_MESSAGE_LEN, msg.toStdString().c_str(), MAX_MESSAGE_LEN);

	char* pSendData = nullptr;
	pSendData = new char[requestChat.nSize];
	memcpy(pSendData, (void*)&requestChat, sizeof(requestChat));
    m_SendDataQueue.push_back(pSendData);
    qDebug() << requestChat.szMessage ;

    m_WriteMessage = msg.toStdString();
    boost::asio::async_write(m_Socket,
                             boost::asio::buffer(pSendData, requestChat.nSize),
                             boost::bind(&Client::handle_write,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                             );
    PostReceive();
}

void Client::LogIn(QString szName)
{
    PKT_REQ_IN requestLogIn;
    requestLogIn.Init();
    strncpy_s(requestLogIn.szName, MAX_NAME_LEN, szName.toStdString().c_str(), MAX_NAME_LEN-1);

    /////
    char* pSendData = nullptr;
    pSendData = new char[requestLogIn.nSize];
    memcpy(pSendData, (void*)&requestLogIn, sizeof(requestLogIn));
    m_SendDataQueue.push_back(pSendData);

    boost::asio::async_write(m_Socket, boost::asio::buffer(pSendData, requestLogIn.nSize),
                             boost::bind(&Client::handle_write, this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred)
                            );
	PostReceive();
    /////
}

void Client::PostWrite(QString msg)
{





//    if(m_Socket.is_open() == false)
//        return;
//    m_WriteMessage = msg.toStdString();
//    boost::asio::async_write(m_Socket,
//                             boost::asio::buffer(m_WriteMessage),
//                             boost::bind(&Client::handle_write,
//                                         this,
//                                         boost::asio::placeholders::error,
//                                         boost::asio::placeholders::bytes_transferred)
//                             );
//    PostReceive();
}

void Client::handle_connect(const boost::system::error_code &err)
{
    if(err){
        qDebug() << "Connect Failed ! ";// << err.message().c_str();
        emit connectFail();
    }
    else{
        qDebug() << "Connected! ";
		emit connectSuccess();
    }
}

void Client::handle_write(const boost::system::error_code &, size_t)
{
    delete[] m_SendDataQueue.front();
    m_SendDataQueue.pop_front();
}

void Client::handle_receive(const boost::system::error_code &error, size_t bytes_transferred)
{
    if(error){
        if(error == boost::asio::error::eof){
            qDebug() << "Disconnected from Server.";
            //PostWrite("Disconnected from Server.");
        }
        else{
//            QString szLog = QString("Error No : %1  Error Message :  ").arg(error.value());
//            szLog += QString::fromStdString(error.message());
//            PostWrite(szLog);
            qDebug() << "Error No : " << error.value() << " error message : " << error.message().c_str() ;
        }
    }
    else{
        const std::string strRecvMessage = m_ReceiveBuffer.data();
        qDebug() << "Message from Server : " << strRecvMessage.c_str()
                 << ",  Received Size : " << bytes_transferred ;
		QString szData = QString::fromStdString(strRecvMessage);
		emit receive_message(szData);
        PostReceive();
    }
}













