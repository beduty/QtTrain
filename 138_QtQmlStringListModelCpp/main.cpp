#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

///  Model /View 구조의 개념
/// 1. Model은 데이터의 실체임과 동시에 다른 컴포넌트들과의 인터페이스를 제공한다.
/// 2. View는 Delegate를 통해서 렌더링을 수행하는데,
///    몇개를 만들지, 만들 때 어떤 정보를 가져올지를 Model에 접근하여 결정한다.
/// 3. Delegate는 사용자와의 인터페이스를 제공할 수 있는데, 변경사항이 생기면 Model과 View에 업데이트한다.
///
#include <QStringList>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QStringList continentList;
    continentList.append("Africa");
    continentList.append("Europe");
    continentList.append("America");
    continentList.append("Asia");
    continentList.append("Oceania");
    continentList.append("Antarctica");
    // 만들어준 리스트를 바로 QML로 넘겨줄 수 있다.
    // 단점은 어떠한 외부 응답에 의해 QStringList 모델의 변경등을 반영하지 못한다.
    // 그냥 Chunk만 받아오는 것이기 때문에!
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("continentModel", continentList);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
