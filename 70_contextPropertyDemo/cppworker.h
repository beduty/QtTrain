#ifndef CPPWORKER_H
#define CPPWORKER_H

#include <QObject>

class CppWorker : public QObject
{
    Q_OBJECT
public:
    explicit CppWorker(QObject *parent = nullptr);
    Q_INVOKABLE void     regularMethod();
    Q_INVOKABLE  QString  regularMehodWithReturn(QString name, int age);

public slots:
    void cppSlot();
    void othercall();
};

//#include <QObject>
//class CppWorker : public QObject
//{
//        Q_OBJECT
//public:
//        explicit CppWorker(QObject* parent = nullptr);
//        Q_INVOKABLE void regularMethod();
//        Q_INVOKABLE QString regularMothodWithReturn(QString name, int age);
//};


#endif // CPPWORKER_H
