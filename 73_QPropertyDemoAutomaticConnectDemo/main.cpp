#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "movie.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Movie movie;
    movie.settitle("Titanic");
    movie.setmainCharcter("Leonardo D");

    engine.rootContext()->setContextProperty("Movie", &movie);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
