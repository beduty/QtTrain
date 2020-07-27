#include "widget.h"
#include "ui_widget.h"
#include <QString>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , client(new asioClient)
{
    ui->setupUi(this);

    // ui Form에서도 가능하지만, 직접 Table Widget을 꾸며본다.
    ui->paramTable->setColumnCount(2);
    ui->paramTable->setHorizontalHeaderLabels(QString("key;value").split(";"));
    ui->paramTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->urlEdit->setText("http://127.0.0.1:5000/");

}

Widget::~Widget()
{
    delete ui;
    delete client;
}


void Widget::on_getBtn_clicked()
{
    //ui->urlEdit->text()
    client->get("www.boost.org", "/");
}
