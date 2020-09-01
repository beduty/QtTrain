#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "personmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    PersonModel mModel;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", &mModel);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
