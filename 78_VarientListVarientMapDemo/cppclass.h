#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

class CppClass : public QObject
{
    Q_OBJECT
public:
    explicit CppClass(QObject *parent = nullptr);

    Q_INVOKABLE void passFromQmlToCpp(QVariantList list, QVariantMap map);
    Q_INVOKABLE QVariantList getVariantListFromCpp();
    Q_INVOKABLE QVariantMap getVariantMappFromCpp();

    void setQmlRootObject(QObject* value);

signals:
public slots:
    void triggetJSCall();
private:
    QObject* qmlRootObject;
};

#endif // CPPCLASS_H
