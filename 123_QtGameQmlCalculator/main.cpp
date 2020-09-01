#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "advancedcaculator.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    /// QML에서는 UI를 담당하고, C++로 무거운 계산을 수행하도록 할 수 있다.
    /// C++클래스를 JavaScript객체로 바꿔야 QML 파일에서 사용할 수 있다.
    /// QQmlApplicationEngine이 QJSEngine을 상속받았기 때문에 가능하다.
    /// 바꾼 자바스크립트 객체는 QML엔진에 삽입할 수 있다.
    ///
    ///
    ///

//    QQmlApplicationEngine engine;
//    CppWorker worker;
//    engine.rootContext()->setContextProperty("BWorker", &worker);


    engine.rootContext()->setContextProperty("advancedCalculator", (new AdvancedCaculator));
    //    engine.globalObject().setProperty("advancedCalculator",
//        engine.newQObject(new AdvancedCaculator));
    /// 1. QML에서 가져다 쓸 수 있도록, 클래스를 만들고,engine에 주입한다.
    /// 2. advancedCalculator 전역변수로 사용할 수 있다.
    /// --> C++ 객체를 QML엔진에서 엑세스할 수 있는 JavaScript 객체로 노출한다..
    return app.exec();


    // 싱글톤버전
    /// QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    /// QGuiApplication app(argc, argv);
    /// qmlRegisterSingletonType("CalculatorApp", 1, 0, "AdvancedCalculator",
    ///         [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QJSValue {
    ///     Q_UNUSED(scriptEngine);
    ///     return engine->newQObject(new AdvancedCaculator);
    /// });
    /// QQmlApplicationEngine engine;
    /// const QUrl url(QStringLiteral("qrc:/main.qml"));
    /// engine.load(url);
    /// if(engine.rootObjects().isEmpty())
    ///     return -1;
    /// return app.exec();
}
