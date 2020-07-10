#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cppworker.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);



    QQmlApplicationEngine engine;
    CppWorker worker;
    engine.rootContext()->setContextProperty("BWorker", &worker);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);

    return app.exec();
}
