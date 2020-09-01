#ifndef CPPLISTDATA_H
#define CPPLISTDATA_H

#include <QObject>
#include <QVector>
#include <QVariantList>
#include <QVariantMap>
class cppListData : public QObject
{
    Q_OBJECT
public:
    explicit cppListData(QObject *parent = nullptr);
    Q_INVOKABLE void vectorToCpp(QVector<QString> vector);
    Q_INVOKABLE QVector<QString> vectorFromCpp();

    Q_INVOKABLE void listMapToCpp(QVariantList list, QVariantMap map);
    Q_INVOKABLE QVariantList listFromCpp();
    Q_INVOKABLE QVariantMap mapFromCpp();

private:
    QVector<QString> mVector;
};

#endif // CPPLISTDATA_H
