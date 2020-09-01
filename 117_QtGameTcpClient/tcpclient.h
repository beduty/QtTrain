#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QAbstractSocket>
#include <QtNetwork>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class TcpClient; }
QT_END_NAMESPACE


/// Tcp Client는 Server보다 신경쓸 것이 많지 않다.
/// 서버와 달리 연결된 Socket하나만 신경 써주면된다. 나머지는 다 GUI적인 부분 밖에 없다.
/// 구축된 소켓을 통해서 4가지의 작업을 한다.
///   1. QTcpSocket::readyRead 시그널 받아서 처리
///   2. QTcpSocket::connected 시그널 받아서 처리
///   3. QTcpSocket::disconnected 시그널 받아서 처리
///   4. 보낼 메시지 QTcpSocket::write(..)로 서버로 메시지 전송
///  --> 들어오는 시그널과 서버로 메시지 전송 부분만 작업해주면 된다.

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
private slots:
    void on_connect_clicked();
    void on_disconnect_clicked();

private slots:
    void readyRead();          //QTcpSocket::readyRead 시그널 처리
    void connectedToServer();  //QTcpSocket::connected 시그널 처리
    void disconnectByServer(); //QTcpSocket::disconnecte 시그널 처리
    void on_text_returnPressed(); // QTcpSocket::Write로 메시지 전송~!

private:
    Ui::TcpClient *ui;
    QTcpSocket *m_socket;
    QString m_userName;
    QByteArray m_receivedData;

    void updateGui(QAbstractSocket::SocketState state);
    void newMessage(const QString &message);
};
#endif // TCPCLIENT_H
