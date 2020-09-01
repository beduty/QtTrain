#include "tcpclient.h"
#include "ui_tcpclient.h"

TcpClient::TcpClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpClient)
    , m_socket(new QTcpSocket(this))   // 소켓 초기화
{
    ui->setupUi(this);
    ui->address->setText(QHostAddress(QHostAddress::LocalHost).toString());
    ui->port->setValue(52693);   // 연결할 내용 미리 초기화 해놓는다.
    ui->text->setFocus();

    // 시그널 들어오면 처리한 슬롯들 연결해준다.
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::readyRead);
    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::connectedToServer);
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpClient::disconnectByServer);
}

TcpClient::~TcpClient()
{
    delete ui;
}


void TcpClient::on_text_returnPressed()
{
    const QString text = ui->text->text().simplified();
    if(text.isEmpty() || m_socket->state() != QAbstractSocket::ConnectedState){
        return;
    }
    QString message = QStringLiteral("%1 : %2").arg(m_userName).arg(ui->text->text());
    QByteArray messageArray = message.toUtf8();
    messageArray.append(23); // 끝 문자 넣는다!
    m_socket->write(messageArray);   // 소켓을 통해 서버로 메시지 보낸다.
    ui->text->clear();
}

void TcpClient::readyRead()
{
    if(m_socket->state() != QAbstractSocket::ConnectedState){
        return;
    }

    // 서버로부터 들어오는 메시지를 버퍼에 저장한다.
    // 끝문자가 들어오지 않으면 끊겨 들어오는 것이므로 while의 break를 한다.
    m_receivedData.append(m_socket->readAll());
    while (true) {
        int endIndex = m_receivedData.indexOf(23);
        if(endIndex < 0){
           break;
        }

        // 끝문자가 검색되면 끝문자까지 않고, 해당부분의 내용을 지운다.
        // 이어져서 뒤에 올 메시지가 들어 올 수도 있기때문에 버퍼의 처음~(endIndex +1) 까지만 지운다.
        QString message = QString::fromUtf8(m_receivedData.left(endIndex));
        m_receivedData.remove(0, endIndex +1);
        newMessage(message);
    }
}

void TcpClient::connectedToServer()
{
    ui->chat->appendPlainText(tr("== Connected to server."));
    updateGui(QAbstractSocket::ConnectedState);
}

void TcpClient::disconnectByServer()
{
    ui->chat->appendPlainText(tr("== Disconnected by server."));
    updateGui(QAbstractSocket::UnconnectedState);
}

void TcpClient::updateGui(QAbstractSocket::SocketState state)
{
    // 서버 연결되면 Text쓸 부분이 활성화 되어야 하고  Connect 버튼은 비활성화 되어야 한다.
    // 이러한 GUI 객체의 상태 업데이트 부분을 수행한다.
    const bool connected = (state == QAbstractSocket::ConnectedState);
    const bool unconnected = (state == QAbstractSocket::UnconnectedState);

    ui->connect->setEnabled(unconnected);
    ui->address->setEnabled(unconnected);
    ui->port->setEnabled(unconnected);
    ui->user->setEnabled(unconnected);

    ui->disconnect->setEnabled(!unconnected);
    ui->chat->setEnabled(connected);
    ui->text->setEnabled(connected);
}

void TcpClient::newMessage(const QString &message)
{
    // 서버로 메시지 보내면 서버가 응답해온다.
    // 다른 클라이언트가 메시지를 보내도 서버가 모든 클라이언트에게 응답보낸다.
    // 그 응답을 PlainText에 기록한다.
    ui->chat->appendPlainText(message);
}

void TcpClient::on_connect_clicked()
{
    // 커넥트 버튼 누를때 콜백된다.
    const QString user = ui->user->text().simplified();
    if(user.isEmpty()){
        ui->chat->appendPlainText(tr("== Unable to connect to server. "
                                     "You must define an user name."));
        return;
    }
    m_userName = user;
    if(m_socket->state() != QAbstractSocket::ConnectedState){
        ui->chat->appendPlainText(tr("== Connecting ..."));
        // 소켓을 연결한다. (Ip주소와 Port번호를 입력해준다.)
        m_socket->connectToHost(ui->address->text(), ui->port->value());
        updateGui(QAbstractSocket::ConnectingState);
    }
}

void TcpClient::on_disconnect_clicked()
{
    // DisConnect 버튼 누를때 콜백된다.
    if(m_socket->state() != QAbstractSocket::ConnectingState){
        ui->chat->appendPlainText(tr("== Abort connectin."));
    }
    // 소켓의 연결 부분을 해제한다.
    m_socket->abort();
    updateGui(QAbstractSocket::UnconnectedState);
}
