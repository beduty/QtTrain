#include "cppdata.h"
#include <QtDebug>
cppData::cppData(QObject *parent) : QObject(parent)
{

}

void cppData::getData(QColor color)
{
    qDebug() << "cppData Get Called! color : " << color;
    emit sendInt(123);
    emit sendDouble(123.456);
    emit sendBoolRealFloat(true, 34.12, 456.5);
    emit sendStringUrl("String from c++", QUrl("http://www.google.com"));
    emit sendColorFont(QColor(126,230,63), QFont("Times", 20, QFont::Bold));
    emit sendDate(QDate::currentDate()); // QDate(2020,08,23)
    emit sendPoint(QPoint(145, 408), QPointF(20.15,416.8));
    emit sendSize(QSize(200,500), QSizeF(700.0,95.1));
    emit sendRect(QRect(100,100,300,300), QRectF(105.5, 105.6, 200.4, 200.5));
}
