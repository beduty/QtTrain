#include "hellowidget.h"
#include <QApplication>
#include <QPushButton>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // QApplication의 핵심기능은 EventLoop를 관리해주는 역할이다.
    // retun a.axec(); 를 통해 EventLoot가 돈다.
    //  여기서 마우스, 키보드등의 Input,타이머 이벤트등을 분배하는 역할을 한다.
    QPushButton button("Close");
    button.show();

    //QObject::connect(sender, SIGNAL, receiver, SLOT);
    QObject::connect(&button, SIGNAL(clicked(bool)), &app, SLOT(quit()));
    // QPushButton클래스에서 제공하는 Clicked(bool) 시그널,
    // QApplication에서 제공하는 quit() 슬롯을 연결한다.
    // SIGNAL들어오면 연결된 SLOT이 실행된다!



//    HelloWidget w;
//    w.show();
    return app.exec();
}
