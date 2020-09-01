#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "counting.h"
#include "counter.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Counter>("MyCounter", 1,0, "MyCounter");
    ///Counter 클래스에서 Q_PROPERTY(Counting::CountDirection counting ... 를 썼다.
    /// 이 형식은 QML에서 모른다. C++ 클래스를 QML 객체로 사용할 수 있게끔 등록해준다.
    /// UnCreatableType 인 이유는 생성은 불가능하기 때문이다.
    /// "Counting" 클래스는 QML에서 객체 생성이 불가능하다.
    /// 오로지, Counter클래스의 멤버로서 속성 혹은 열거값 제공하는 경우에만 사용한다!
    qmlRegisterUncreatableType<Counting>("MyCounter", 1,0, "MyCounting",
                                         "Can't instantiate Counting from QML.Not Allowed");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
