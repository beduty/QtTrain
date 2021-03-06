#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "errorlevel.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterUncreatableType<ErrorLevel>("com.blikoon.errorlevel",1,0, "MyErrorLevel",
                                           "Can't create ErrorLevel type in QML, Not Allowed.");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
