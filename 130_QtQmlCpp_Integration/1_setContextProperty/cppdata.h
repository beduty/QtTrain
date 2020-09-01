#ifndef CPPDATA_H
#define CPPDATA_H
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
class cppData : public QObject
{
    Q_OBJECT
public:
    explicit cppData(QObject *parent = nullptr);
signals:
    void sendInt(int param);
    void sendDouble(double doubleParam);
    void sendBoolRealFloat(bool boolParam, qreal realParam, float floatParam);
    void sendStringUrl(QString stringParam, QUrl urlParam);
    void sendColorFont(QColor colorParam, QFont fontParam);
    void sendDate(QDate dateParam);
    void sendPoint(QPoint pointParam, QPointF pointfParam);
    void sendSize(QSize sizeParam, QSizeF sizefParam);
    void sendRect(QRect rectParam, QRectF rectfParam);

public slots:
    void getData(QColor color);
};

#endif // CPPDATA_H
