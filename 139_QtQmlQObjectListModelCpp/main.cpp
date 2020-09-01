#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "person.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // QObject를 넘겨줌으로써, Q_PROPERTY 속성에 바로 접근할 수 있다.
    // QML에서 객체 만들때 속성값 받아와서 Delegate만들면 끝~~
    QList<QObject*> personList;
    // &engine으로 Parent를 주면 engine이 죽을 때 하위의 메모리 할당해둔것도 다 알아서 해제되기 때문!
    personList.append(new Person("John Doe C++","green",32,&engine));
    personList.append(new Person("Mary Green","blue",23,&engine));
    personList.append(new Person("Mitch Nathson","dodgerblue",30,&engine));
    personList.append(new Person("Daniel Sten","red",67,&engine));
    personList.append(new Person("John Doe C++","green",32,&engine));
    personList.append(new Person("Mary Green","blue",23,&engine));
    personList.append(new Person("Mitch Nathson","dodgerblue",30,&engine));
    personList.append(new Person("Daniel Sten","red",67,&engine));

    ///QML에서 사용할 때 아래와 같이 ListModel 해주는 것과 동일한 효과를 가진다.
//    ListModel{
//        id : mModelId
//        ListElement{
//            names : "Daniel Sten"; favoriteColor : "blue"; age : 10
//        }
//        ListElement {
//            names : "Stevie Wongers"; favoriteColor : "cyan"; age : 23
//        }
//        ListElement {
//            names : "Nicholai Ven"; favoriteColor : "red"; age : 33
//        }
//        ListElement {
//            names : "William Glen"; favoriteColor : "yellowgreen"; age : 45
//        }
//    }

    engine.rootContext()->setContextProperty("personModel", QVariant::fromValue(personList));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    if(engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
