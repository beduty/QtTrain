#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "stair.h"
#include "stairchart.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<StairChart>("StairChart", 1,0, "StairChart");
    qmlRegisterType<Stair>("StairChart", 1,0, "Stair");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}