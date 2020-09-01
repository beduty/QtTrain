#include <QGuiApplication>
#include <QQmlContext>
#include "cpptimer.h"
#include "movie.h"
#include "cppdata.h"
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;

    cppTimer timer;
    engine.rootContext()->setContextProperty("MyTimer", &timer);

    Movie movie;
    movie.setTitle("Titanic");
    movie.setCharacter("Leonardo D");
    engine.rootContext()->setContextProperty("Movie", &movie);

    cppData data;
    engine.rootContext()->setContextProperty("CppData", &data);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
