#include "objectlistwrapper.h"
#include <QtDebug>

ObjectListWrapper::ObjectListWrapper(QObject *parent) : QObject(parent)
{
    populateModelWithData();
}

bool ObjectListWrapper::initialize()
{
    resetModel();
    mEngine.rootContext()->setContextProperty("Wrapper", this);
    //  QML에서는 Wrapper로 접근하여 setName등으로 cpp와 통신할 수 있다.
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    mEngine.load(url);
    if(mEngine.rootObjects().isEmpty())
        return false;
    return true;
}

void ObjectListWrapper::setNames(int index, const QString &names)
{
    qDebug() << "Changing names to : " << names;
    if(index >= mPersons.size())
        return;
    Person* person = static_cast<Person *>(mPersons.at(index));
    if(names != person->names())
    {
        // 데이터 모델 갱신후, QML에 업데이트 해준다.
        person->setNames(names);
        resetModel();
    }
    printPersons();
}

void ObjectListWrapper::setAge(int index, const int &age)
{
    if(index >= mPersons.size())
        return;
    Person* person = static_cast<Person*>(mPersons.at(index));
    if(age != person->age()){
        person->setAge(age);
        resetModel();
    }
    printPersons();
}

void ObjectListWrapper::setFavoriteColor(int index, const QString &favoriteColor)
{
    if(index >= mPersons.size())
        return;
    Person* person = static_cast<Person*>(mPersons.at(index));
    if(favoriteColor != person->favoriteColor())
    {
        person->setFavoriteColor(favoriteColor);
        resetModel();
    }
    printPersons();
}

QList<QObject *> ObjectListWrapper::persons() const
{
    return mPersons;
}

void ObjectListWrapper::addPerson()
{
    /// model에 데이터 추가하고, QML로 모델을 갱신한다.
    /// 갱신한 것을 받아서 QML에서도 Reactive하게 객체가 갱신된다.
    mPersons.append(new Person("New Person", "green", 32, this));
    resetModel();
}

void ObjectListWrapper::callTest()
{
    // QList<QObject*> mPersons의 내용 중 하나라도 바뀌면, QML의 리스트뷰가
    // 모두 갱신된다! 비싼 연산이다. delegate에서 호출되는 callTest()로 그것을 확인할 수 있다.
    qDebug() << "call!" ;
}

void ObjectListWrapper::populateModelWithData()
{
    // this는 QObject를 의미한다.
    // 부모 메모리 해제될때 New했던 메모리들도 같이 해제된다!
    mPersons.append(new Person("John Doe", "green", 32, this));
    mPersons.append(new Person("Mary Green", "blue",23, this));
    mPersons.append(new Person("Mitch Nathson", "dodgerblue", 30, this));
}

void ObjectListWrapper::resetModel()
{
    // Object 리스트상의 변화가 있을때 (내용변경, 내용추가)
    // Context Property를 다시 설정해준다!!
    // QML에서 model을 전달해주면 전달해준 값만 쓸 수 있다.
    // resetModel로 model을 갱신해주면 QML로도 전달된다! 이 방법을 통해서 cpp에서 QML로 통신할 수 있다!
    mEngine.rootContext()->setContextProperty("myModel", QVariant::fromValue(persons()));
}

void ObjectListWrapper::printPersons()
{
    qDebug() << "\n";
    qDebug() << "------------------Persons---------------";
    foreach(QObject* obj, mPersons){
        Person* person = static_cast<Person*>(obj);
        qDebug() << person->names() << " " << person->age() << " " << person->favoriteColor();
    }
}




