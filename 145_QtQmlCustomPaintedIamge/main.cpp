#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "learnqtlogo.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<LearnQtLogo>("QtLogo", 1,0, "Logo");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
