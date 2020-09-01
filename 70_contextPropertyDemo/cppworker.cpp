#include <QDebug>
#include "cppworker.h"
CppWorker::CppWorker(QObject *parent) : QObject(parent)
{

}

void CppWorker::regularMethod()
{
    qDebug() << "This is C++ talking, regularMethod called";

}

QString CppWorker::regularMehodWithReturn(QString name, int age)
{
    return QString(name + ":" + QString::number(age) + " years old");
}

void CppWorker::cppSlot()
{
    qDebug() << "This is C++ talking, cppSlot called.";
}

void CppWorker::othercall()
{
    qDebug() << "I'm Other. Component OnComplete!";
}

//#include <QDebug>
//#include "cppworker.h"
//CppWorker::CppWorker(QObject *parent) : QObject(parent)
//{
//}

//void CppWorker::regularMethod()
//{
//        qDebug()<<"This is C++ talking, regularMethod called";
//}
//QString CppWorker::regularMothodWithReturn(QString name, int age)
//{
//        return QString(name + " : " + QString::number(age) + " years old");
//}


















