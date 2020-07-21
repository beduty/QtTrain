#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQmlContext>
#include "appwrapper.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AppWrapper wrapper;
    if(false == wrapper.initialize()){
        return -1;
    }

//    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty("Wrapper", &wrapper);
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    engine.load(url);
//    if(engine.rootObjects().isEmpty())
//        return -1;

    return app.exec();
}
