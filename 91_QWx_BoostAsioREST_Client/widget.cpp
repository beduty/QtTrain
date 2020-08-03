#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QRegularExpression>

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
    QString url = ui->urlEdit->text();
    //client->get("www.boost.org", "/");
    QRegularExpression re("^(?:([A-Za-z]+):)?(\\/{0,3})([0-9.\\-A-Za-z]+)(?::(\\d+))?(?:\\/([^?#]*))?(?:\\?([^#]*))?(?:#(.*))?$");
    QRegularExpressionMatch match = re.match(url);
    if(match.hasMatch()){
        // "https://regex101.com/"   참조!
        auto hostName =  match.captured(3);
        auto urlPath = "/" + match.captured(5);
        client->get(hostName, urlPath);
    }


}
