#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>
TcpServer::TcpServer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpServer)
    , m_server(new QTcpServer(this)) // 서버 초기화
{
    ui->setupUi(this);

    // 서버의 포트를 열고 클라이언트 접속을 기다린다! (비동기이다)
    if(!m_server->listen(QHostAddress::LocalHost, 52693))
    {
        ui->log->setPlainText(tr("Failure while starting server : %1")
                              .arg(m_server->errorString()));
        return;
    }
    ui->address->setText(m_server->serverAddress().toString());
    ui->port->setText(QString::number(m_server->serverPort()));

    connect(m_server, &QTcpServer::newConnection, this, &TcpServer::newConnection);
    /// 클라이언트가 연결되면 자동 Accept되며 QTcpServer::newConnection 시그널이 들어온다.!
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::newConnection()
{
    while (m_server->hasPendingConnections()) // 연결보류중인 것이 2개 이상일 수 있으므로 while~
    {
        /// m_server->hasPendingConnections()는 서버에 보류중인 연결이 있는 경우에 Treu가 된다.
        /// m_server->nextPendingConnection()는 보류중이던 연결을 수행하고 소켓을 리턴한다!
        QTcpSocket *socket = m_server->nextPendingConnection();

        m_clients << socket; // QVector<QTcpSocket*> 으로 관리한다
        ui->disconnectClients->setEnabled(true);
        ui->log->appendPlainText(tr("* New connection : %1, port %2")
                                 .arg(socket->peerAddress().toString()) // 클라이언트 소켓의 ip 주소를 받아온다.
                                 .arg(socket->peerPort())); // 클라이언트 소켓의 ip Port 번호를 받아온다.

        /// 새로 연결한 소켓의 Signal Slot을 등록한다.
        /// 클라이언트로부터 데이터 들어오거나, 연결이 끊길때 Slot이들어오는데,
        /// 슬롯 시작부분에서 sender()를 캐스팅하여 어떤 클라이언트로부터 들어온지 알 수 있다.
        ///     --> QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
        connect(socket, &QTcpSocket::disconnected, this, &TcpServer::removeConnection);
        connect(socket, &QTcpSocket::readyRead, this, &TcpServer::readyRead);
    }
}

void TcpServer::removeConnection()
{
    // 어떤 클라이언트가 연결이 끊긴것인이 어떻게 알까???
    // sender()를 사용하면 어떤 곳에서 Signal을 보낸 것인지 알 수 있다.
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket)
        return;
    ui->log->appendPlainText(tr("* Connection removed : %1, port %2")
                             .arg(socket->peerAddress().toString())
                             .arg(socket->peerPort()));
    ui->disconnectClients->setEnabled(!m_clients.isEmpty());

    m_clients.removeOne(socket); // QVector지만, 값을 넣으면 찾아서 지워준다.(가장 먼저 발견된 것만)
    m_receivedData.remove(socket); // QHash<QTcpSocket*, QByteArray>의 인자를 지운다.
    socket->deleteLater();//QTcpSocket은 QTcpServer로부터 왔다. QTcpServer 지워지면 소켓도 알아서 지워진다.
}

void TcpServer::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if(!socket)
        return;

    /// TCP 통신에서 모든 데이터들이 하나의 청크로 들어오지 않는다.
    /// 끊겨서 들어올수도 있은데, 이를 위해서 끝문자등을 확인해야 한다.(ASCII 코드 23 End of Transmission Block)
    /// 아래의 소스에서는 QHash<..>로 된 데이터 버퍼에 내용을 계속 뒤에 이어 붙인다.
    /// 그리고 While에서 buffer의 끝문자를 확인한다. 확인이 안되면 break되고, 다시 들어오는 데이터를 받는다.
    /// 끝문자가 확인되면 클라이언트에게 데이터를 보내고, 버퍼의 내용을 다시 비운다!

    QByteArray &buffer = m_receivedData[socket]; // QHash의 인자 하나를 레퍼런스로 받아온다.
    buffer.append(socket->readAll()); // 소켓에서 가져온 내용을 채운다.

    while (true) {
        int endIndex = buffer.indexOf(23); // 23이 끝문자이다! 끝문자 있는 인덱스가 곧 버퍼의 크기가 된다!
        if(endIndex < 0)
            break;
        QString message = QString::fromUtf8(buffer.left(endIndex)); // 버퍼 처음 ~ 끝문자 까지 내용을 캐싱한다.
        buffer.remove(0, endIndex +1); // 캐싱했으므로 버퍼내용은 지워준다.(endIndex +1는 길이이다.)
        // 이어져서 뒤에 올 메시지가 들어 올 수도 있기때문에 버퍼의 처음~(endIndex +1) 까지만 지운다.
        newMessage(socket, message); // 연결되어 있는 다른 클라이언트들한테 내용을 뿌려준다.
    }
}

void TcpServer::on_disconnectClients_clicked()
{
    // 서버 종료하면 모든 소켓을 다 닫는다~
    foreach(QTcpSocket *socket, m_clients){
        socket->close();
    }
    ui->disconnectClients->setEnabled(false); // Disconnect 버튼 다시 비활성화 한다.
}

void TcpServer::newMessage(QTcpSocket *sender, const QString &message)
{
    ui->log->appendPlainText(tr("Sending message : %1").arg(message));

    QByteArray messageArray = message.toUtf8();
    messageArray.append(23); // 마지막에 끝 문자를 넣는다.

    for(QTcpSocket *socket : m_clients)
    {
        if(socket ->state() == QAbstractSocket::ConnectedState){
            socket->write(messageArray); // 소켓에 메시지를 태운다. 연결된 클라이언트로 전달된다.
        }
    }
    Q_UNUSED(sender);
}






