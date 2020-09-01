#include <QDebug>
#include "objectlistwrapper.h"

ObjectListWrapper::ObjectListWrapper(QObject *parent) : QObject(parent)
{
    populateModelWithData();
}

bool ObjectListWrapper::initialize()
{
    resetModel();
    mEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (mEngine.rootObjects().isEmpty())
        return false;
    return true;
}

void ObjectListWrapper::callTest()
{
    // 확인해보면 알겠지만, 모델내용중 하나가 바뀐다고 하여 모든 것이 업데이트 되지 않는데,
    // QML에서는 바뀐 것만 GUI 업데이트 한다!!
    // 하지만, List의 내용이 추가될 때(AddPerson) 모델의 값을 사용하는 GUI들이 업데이트 된다!>
    qDebug() << "call!" ;
}


void ObjectListWrapper::setNames(int index, const QString &names)
{
    qDebug() << "Changing names to : " << names;
    if(index >= mPersons.size())
        return;
    Person * person = static_cast<Person *> (mPersons.at(index));
    if( names!= person->names())
    {
        person->setNames(names);

    }
    printPersons();
}

void ObjectListWrapper::setAge(int index, const int &age)
{
    if(index >= mPersons.size())
        return;
    Person * person = static_cast<Person *> (mPersons.at(index));
    if( age!= person->age())
    {
        // setAge에서 mPersons.at(idx)의 emit SIGNAL 보내주고, QML에서는 이를 받아
        // age에 관련된 내용만 GUI업데이트를 하기 때문에
        // context Property를 다시 만들어주고 자시고 할 필요가 없다!
        person->setAge(age);
    }
    printPersons();
}

void ObjectListWrapper::setFavoriteColor(int index, const QString &favoriteColor)
{
    if(index >= mPersons.size())
        return;
    Person * person = static_cast<Person *> (mPersons.at(index));
    if( favoriteColor!= person->favoriteColor())
    {
        person->setFavoriteColor(favoriteColor);

    }
    printPersons();
}

QList<QObject *> ObjectListWrapper::persons() const
{
    return mPersons;
}

void ObjectListWrapper::addPerson()
{
    mPersons.append(new Person("New Person","green",32,this));
    // 여기서는 mPersons를 보낸다. 즉 모델 자체를 보내는 것이므로,
    // QML에서는 ListView 전체를 GUI 갱신 하게 된다!
    emit mypersonsChanged(mPersons);
}

QList<QObject *> ObjectListWrapper::mypersons() const
{
    return mPersons;
}

void ObjectListWrapper::setMypersons(QList<QObject *> mypersons)
{
    if (mPersons == mypersons)
        return;
    qDebug() << "set person";
    mPersons = mypersons;
    emit mypersonsChanged(mPersons);
}

void ObjectListWrapper::populateModelWithData()
{
    mPersons.append(new Person("John Doe","green",32,this));
    mPersons.append(new Person("Mary Green","blue",23,this));
    mPersons.append(new Person("Mitch Nathson","dodgerblue",30,this));
}

void ObjectListWrapper::resetModel()
{
    mEngine.rootContext()->setContextProperty("Wrapper",this);
    //mEngine.rootContext()->setContextProperty("myModel",QVariant::fromValue(persons()));

}

#include <QDateTime>
void ObjectListWrapper::printPersons()
{
    qDebug() << "-------------Persons--------------------";
    foreach (QObject * obj, mPersons) {
        Person * person = static_cast<Person *> (obj);
        qDebug() << person->names() << " " << person->age() << " " << person->favoriteColor();
    }
    qDebug() << "-------------UpdateDone--------------------" << QDateTime().currentDateTime();
}
