#ifndef OBJECTLISTWRAPPER_H
#define OBJECTLISTWRAPPER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "person.h"

// Object 리스트상의 변화가 있을때 (내용변경, 내용추가)
// Context Property를 다시 설정해준다!!

class ObjectListWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ObjectListWrapper(QObject *parent = nullptr);
    bool initialize();
    Q_INVOKABLE void setNames(int index, const QString &names);
    Q_INVOKABLE void setAge(int index, const int &age);
    Q_INVOKABLE void setFavoriteColor(int index, const QString &favoriteColor);
    Q_INVOKABLE QList<QObject*> persons() const;
    Q_INVOKABLE void addPerson();
    Q_INVOKABLE void callTest();

private:
    void populateModelWithData();
    void resetModel();
    void printPersons();
    QList<QObject*> mPersons; // QML에서 알아먹을수 있도록 QObject를 쓰고, static_cast<Person*>으로 접근한다.
    QQmlApplicationEngine mEngine;
};

#endif // OBJECTLISTWRAPPER_H
