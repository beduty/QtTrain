#ifndef CPPCLASS_H
#define CPPCLASS_H
#include <QObject>
#include <QUrl>
#include <QColor>
#include <QFont>
#include <QDate>
#include <QPoint>
#include <QPointF>
#include <QSize>
#include <QSizeF>
#include <QRect>
#include <QRectF>
class CppClass : public QObject
{
    Q_OBJECT
public:
    explicit CppClass(QObject *parent = nullptr);

signals:
    void sendInt(int param);
    void sendDouble(double doubleParam);
    void sendBoolRealFloat(bool boolParam, qreal realParam, float floatParam);

    void sendStringUrl(QString stringParam, QUrl urlParam);
    void sendColorFont(QColor colorParam, QFont fontParam);
    void sendDate(QDate dateParam);
    void sendPoint(QPoint pointParam, QPointF pointfParam);
    void sendSize(QSize sizeParam, QSizeF sizeFParam);
    void sendRect(QRect rectParam, QRectF rectFParam);

public slots:
    void cppSlot();
    void receivePoint(QPoint point);
    void receiveRect(QRectF rect);

};
#endif // CPPCLASS_H
