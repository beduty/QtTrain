#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "propertywrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
//    QString lastName = "Doe";
//    QString firstName = "John";
//    engine.rootContext()->setContextProperty("mLastname", QVariant::fromValue(lastName));
//    engine.rootContext()->setContextProperty("mFirstname", QVariant::fromValue(firstName));

    PropertyWrapper propWrapper;
    propWrapper.setlastname("Doe");
    propWrapper.setfirstname("John");
    engine.rootContext()->setContextObject(&propWrapper);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
