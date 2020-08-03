#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "client.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    if(m_pClient)
        delete m_pClient;
    delete ui;
}

void Widget::on_btnConnect_clicked()
{
	if (m_pClient == nullptr) {
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 31400);
        m_pClient = new Client(endpoint, this);
        connect(m_pClient, SIGNAL(connectSuccess()), this, SLOT(onConnect_Successed()));
        connect(m_pClient, SIGNAL(connectFail()), this, SLOT(onConnect_Failed()));
        connect(m_pClient, SIGNAL(receive_message(QString)), this, SLOT(onReceive_Message(QString)));
    }
}

void Widget::on_btnSend_clicked()
{
	QString szData = ui->inputData->text();
	m_pClient->SendMsg(szData);
}

void Widget::onConnect_Successed()
{
    ui->connectionStatusLabel->setText("Connected!!");
    m_pClient->LogIn("TaeYeong");
}

void Widget::onConnect_Failed()
{
    if(m_pClient){
        delete m_pClient;
        m_pClient = nullptr;
    }
}

void Widget::onReceive_Message(const QString & msg)
{
	ui->commLog->addItem(msg);
}
