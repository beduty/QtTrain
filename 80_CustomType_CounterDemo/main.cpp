#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "counter.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 이제 이거를 안써도 된다!!!
    Counter counter2;
    engine.rootContext()->setContextProperty("MyCounter2", &counter2);

    // 이게 더 편하네!!!
    qmlRegisterType<Counter>("com.blikoon.counter", 1,0, "MyCounter");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return   -1;

    return app.exec();
}
