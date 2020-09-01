#include "person.h"

Person::Person(QObject *parent) : QObject(parent)
{

}

Person::Person(const QString &names, const QString &favoritecolor, const int &age, QObject *parent):
    QObject(parent),m_names(names),m_favoriteColor(favoritecolor),m_age(age)
{

}

QString Person::names() const
{
    return m_names;
}

QString Person::favoriteColor() const
{
    return m_favoriteColor;
}

int Person::age() const
{
    return m_age;
}

void Person::setNames(QString names)
{
    if (m_names == names)
        return;

    m_names = names;
    // 주석처리 안해주면 setNames 호출될 때마다 QML 갱신이 일어난다. 비싼연산이다.
    // ObjectListWrapper::resetModel() 에서 한번만 처리되도록 하기 위해서 주석처리한다.
    //emit namesChanged(m_names);
}

void Person::setFavoriteColor(QString favoriteColor)
{
    if (m_favoriteColor == favoriteColor)
        return;

    m_favoriteColor = favoriteColor;
    //emit favoriteColorChanged(m_favoriteColor);
}

void Person::setAge(int age)
{
    if (m_age == age)
        return;

    m_age = age;
    //emit ageChanged(m_age);
}
