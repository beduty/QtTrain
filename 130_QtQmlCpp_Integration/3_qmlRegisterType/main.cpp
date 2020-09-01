#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cpppokedata.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    cppPokeData pokeData;
    qmlRegisterType<cppPokeData>("PokeData",1,0,"PokeData");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
