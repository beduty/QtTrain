#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include "carinfo.h"
#include "carinfoproxy.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;


    // [QML에서 C++ 클래스를 사용하는 방법1]
//    // QML에서 C++ 클래스 접근할 수 있도록, 클래스의 인스턴스를
//    // QML엔진의 전역 컨텍스트로 설정한다.
//    // QML에서는 carData.speed로 객체의 속성에 접근할 수 있다.
//    //   ( Q_PROPERTY 항목에만 접근가능!, WRITE 설정되어있는 경우 직접 변경도 가능하다)
//    CarInfo cinfo;
//    engine.rootContext()->setContextProperty("carData", &cinfo);

    // [QML에서 C++ 클래스를 사용하는 방법2]
    // 아예 QObject로 만든 클래스를 QML 객체로 만들수 있다!
    // --> qmlRegisterType 템플릿함수를 쓰면 가능하다!
    QString msg = QStringLiteral("Objects of type CarInfoEngine cannot be created321321");
    qmlRegisterUncreatableType<CarInfoEngine>("CarInfo", 1, 0, "CarInfoEngine", msg);
    qmlRegisterType<CarInfoProxy>("CarInfo", 1,0, "CarInfo");

    // QML을 실행한다. main.qml 내용이 실행된다.
    // CarInfo 클래스의 인스턴스를 바탕으로 QML 객체 구성한다.
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
