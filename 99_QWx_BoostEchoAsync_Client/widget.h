#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
#include "client.h"
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnConnect_clicked();
    void on_btnSend_clicked();
    void onConnect_Successed();
    void onConnect_Failed();
    void onReceive_Message(const QString& msg);

private:
    Ui::Widget *ui;
    Client* m_pClient = nullptr;
};
#endif // WIDGET_H
