#include "person.h"

Person::Person(QObject *parent) : QObject(parent)
{

}

Person::Person(const QString &names, const QString &favoriteColor, const int &age, QObject *parent)
    :QObject(parent),m_age(age),m_names(names), m_favoriteColor(favoriteColor)
{

}

int Person::age() const
{
    return m_age;
}

QString Person::names() const
{
    return m_names;
}

QString Person::favoriteColor() const
{
    return m_favoriteColor;
}

void Person::setAge(int age)
{
    if (m_age == age)
        return;

    m_age = age;
    emit ageChanged(m_age);
}

void Person::setNames(QString names)
{
    if (m_names == names)
        return;

    m_names = names;
    emit nameChanged(m_names);
}

void Person::setFavoriteColor(QString favoriteColor)
{
    if (m_favoriteColor == favoriteColor)
        return;

    m_favoriteColor = favoriteColor;
    emit favoriteColorChanged(m_favoriteColor);
}
