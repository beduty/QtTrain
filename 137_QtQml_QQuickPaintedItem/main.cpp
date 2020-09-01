#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "outlinetextitem.h"
#include "outlinetextitemborder.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    qmlRegisterUncreatableType<OutlineTextItemBorder>(
         "OutlineTextItem", 1, 0, "OutlineTextTemBorder", "" );
    qmlRegisterType<OutlineTextItem>("OutlineTextItem", 1, 0, "OutlineTextItem");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
