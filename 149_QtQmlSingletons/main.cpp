#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "singletonclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<SingletonClass>("SingleTon",1,0,"SingleTon"
                                             ,SingletonClass::singletonProvider);
//    qmlRegisterSingletonType<SingletonClass>("SingleTon",1,0,"SingleTon",
//                                             [](QQmlEngine *engine, QJSEngine *scriptEngine ){
//        Q_UNUSED(engine)
//        Q_UNUSED(scriptEngine)
//        SingletonClass* example = new SingletonClass();
//        return  example;
//    });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
