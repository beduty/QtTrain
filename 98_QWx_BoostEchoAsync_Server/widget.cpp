#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "server.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_pServer(new Server(31400,5))
{
    ui->setupUi(this);
    connect(m_pServer.get(), SIGNAL(send_message(QString,QString)), this, SLOT(onMessage(QString,QString)));
    connect(m_pServer.get(), SIGNAL(acceptClient()), this, SLOT(onAccepted()));
    connect(m_pServer.get(), SIGNAL(login_user(int, QString)), this, SLOT(onUserLogin(int, QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onMessage(const QString &name, const QString &msg)
{
    QString szData = QString("%1 : %2").arg(name, msg);
    ui->lstLog->addItem(szData);
}

//void Widget::onMessage(const QString & msg)
//{
//    ui->lstLog->addItem(msg);
//}

void Widget::onUserLogin(int nId, const QString &msg)
{
    ui->lstClient->addItem(msg);
}

void Widget::onAccepted()
{
    ui->labelServerStatus->setText("Accepted!");
}
