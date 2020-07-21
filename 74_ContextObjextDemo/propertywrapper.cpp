#include "propertywrapper.h"

PropertyWrapper::PropertyWrapper(QObject *parent) : QObject(parent),
    m_lastname("LastName"),
    m_firstname("FirstName"),
    m_timer(new QTimer(this)),
    m_random_number(0)
{
    //
    srand(time(NULL));
    QStringList list;
    list << "Steward"<< "Johanson"<<"Oliver"<<"David"<<"Snowden"<<"Kevin"<<"Mathson"<<"Gray";
    connect(m_timer, &QTimer::timeout, [=](){
        m_random_number = rand() % (list.size());
        setfirstname(list[m_random_number]);
    });
    m_timer->start(1000);
}

QString PropertyWrapper::lastname() const
{
    return m_lastname;
}

QString PropertyWrapper::firstname() const
{
    return m_firstname;
}

void PropertyWrapper::setlastname(QString lastname)
{
    if (m_lastname == lastname)
        return;

    m_lastname = lastname;
    emit lastnameChanged(m_lastname);
}

void PropertyWrapper::setfirstname(QString firstname)
{
    if (m_firstname == firstname)
        return;

    m_firstname = firstname;
    emit firstnameChanged(m_firstname);
}
