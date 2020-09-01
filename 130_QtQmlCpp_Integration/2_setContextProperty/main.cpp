#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cpplistdata.h"
#include "cppdownload.h"
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    cppListData cppLists;
    CppDownLoad cppDownLoader;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("CppLists", &cppLists);
    engine.rootContext()->setContextProperty("CppUrlDownloader", &cppDownLoader);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
