#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpServer; }
QT_END_NAMESPACE

/// 와... QTcpServer 되게 좋다!!!
/// 1. 기본적으로 비동기. ( Accept(NewConnetion), remove(Disconnected))
/// 2. 소켓클래스도 QTcpServer에 포함되어 Multi Client 사용하기 되게 편하다.
///     --> QTcpSocket* 은 QTcpServer::nextPendingConnection()을 통해서 얻어오기 때문에 따로 관리할 필요가 없다.
///     --> 받아온 QTcpSocket*은 QVector로 관리하여 클라이언트로 부터 메시지 들어오면 받아다가 모든 클라이언트에 뿌려줄때만 사용한다.
///     --> QTcpServer가 제거될때 알아서 QTcpSocket*도 없어진다. 따라서 클라이언트와 연결끊어질 때 socket은 deleteLater() 해주면 된다.
/// 3. QVector<QTcpSocket*> 을 쓰면 멀티 클라이언트 관리가 용이하다.
///     --> QVector.removeOne(QTcpSocket*)을 쓰면 그냥 포인터만 넘기면 알아서 위치를 찾아 지워준다!
/// 4. Signal-Slot 패턴에서 sender()를 쓰면, Signal보낸 QObject를 알 수 있다.
///     -> 이를 활용하면 멀티 클라이언트 중에서 어떤 클라이언트가 메시지를 보내온 것인지 알 수 있다.
/// 5. QHash<QTcpSocket*, QByteArray>를 사용하면 QTcpSocket별로 들어온 메시지 관리를 할 수 있다.
///
/// ---> QTcpSocket을 계속 늘리기만 했고, 끊어졌을 때 재사용 방안을 마련해야한다.
/// ----> 여기서는 Socket을 deleteLater했기때문에 재사용이 안된다고 봐야 한다.

class TcpServer : public QWidget
{
    Q_OBJECT

public:
    TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

private slots:
    void newConnection();    // QTcpServer의 NewConection시그널 처리한다.
    void removeConnection(); // QTcpSocket::disconnected 시그널 처리한다.
    void readyRead();        //QTcpSocket::readyRead 시그널 처리한다.
    void on_disconnectClients_clicked();

private:
    Ui::TcpServer *ui;
    QTcpServer *m_server; // 서버! 되게 좋다!
    QVector<QTcpSocket*> m_clients; // 클라이언트 연결될때마다 소켓 하나씩 늘린다.
    QHash<QTcpSocket*, QByteArray> m_receivedData; // 소켓별로 들어온 데이터를 관리한다.
    //--> m_receivedData[QTcpSocket*] 해주면 해당 소켓의 데이터를 확인 할 수 있다.

    void newMessage(QTcpSocket* sender, const QString& message);
};
#endif // TCPSERVER_H
