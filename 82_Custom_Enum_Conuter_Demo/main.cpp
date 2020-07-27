#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "counter.h"
#include "counting.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Counter>("com.blikoon.counter",1,0, "MyCounter");

    // main.qml에서 생성하려고 하면 에러 발생한다. qmlRegisterUncreatableType 이기 때문에!
    qmlRegisterUncreatableType<Counting>("com.blikoon.counter", 1,0, "MyCounting",
                                         "Can't instantiate Counting from QML.Not Allowed");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
