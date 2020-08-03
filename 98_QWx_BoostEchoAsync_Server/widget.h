#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "server.h"
#include <memory>

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
    void onMessage(const QString &name, const QString & msg);
    void onUserLogin(int ,const QString& msg);
    void onAccepted();
private:
    Ui::Widget *ui;
	//Server* m_pServer;
    std::shared_ptr<Server> m_pServer;
    
};
#endif // WIDGET_H
