#include "cpplistdata.h"
#include <QDebug>
#include <QColor>
#include <QDate>

cppListData::cppListData(QObject *parent) : QObject(parent)
{
    mVector.append("one");
    mVector.append("two");
    mVector.append("three");
    mVector.append("four");
}

void cppListData::vectorToCpp(QVector<QString> vector)
{
    foreach(QString string, vector)
        qDebug() << string;
}

QVector<QString> cppListData::vectorFromCpp()
{
    return mVector;
}

void cppListData::listMapToCpp(QVariantList list, QVariantMap map)
{
    qDebug() << "Receive Variant List and Map from QML";
    qDebug() << "[ List ]";
    for(int i = 0; i< list.size(); i ++){
        qDebug() << "   Item " << i << list.at(i).toString();
    }
    qDebug() << "[ Map ]";
    for(int i = 0; i< map.size(); i ++){
        qDebug() << "   Item " << i << map[map.keys().at(i)].toString();
    }
}

QVariantList cppListData::listFromCpp()
{
    QVariantList list;
    list << 123.3 << QColor(Qt::cyan) << "Qt is great" << 10;
    return list;
}

QVariantMap cppListData::mapFromCpp()
{
    QVariantMap map;
    map.insert("movie", "Game of Thrones");
    map.insert("names", "John Snow");
    map.insert("role", "Main Character");
    map.insert("release", QDate(2011,4,17));
    return map;
}
