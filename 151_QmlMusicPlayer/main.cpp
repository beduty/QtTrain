#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QSettings>
int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Music Player");
    QGuiApplication::setOrganizationName("QtProject");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QGuiApplication app(argc, argv);

    QIcon::setThemeName("musicplayer");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
