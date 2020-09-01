#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "regularpolygon.h"
#include <QQuickView>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    ///////////////////////////////////////////////////////////

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setSamples(16);
    QSurfaceFormat::setDefaultFormat(format);
    qmlRegisterType<RegularPolygon>("RegularPolygon", 1, 0, "RegularPolygon");

    ///////////////////////////////////////////////////////////
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
