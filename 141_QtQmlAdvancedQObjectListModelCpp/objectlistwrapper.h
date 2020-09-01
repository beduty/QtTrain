#ifndef OBJECTLISTWRAPPER_H
#define OBJECTLISTWRAPPER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "person.h"

/// 기존에는 모델의 변화가 있을 떄 context Property를 다시 설정함으로써
/// QML에 변화를 알렸다. QML에서 cpp를 조작할 수 있도록 Wrapper를 제공했고,
/// QML에서 변화를 일으키면 Context Property 다시 설정!!

/// 여기서는 아예 QList<QObject*>를 Q_PROPERY로 넘긴다!
/// QML에는 Wrapper만 제공하게되면, Wrapper를 통해서 mypersons getter로 모델을 가져올 수 있다.
/// Q_PROPERTY에 의해서 데이터 업데이트됨에 따라서 바로 QML로 전달되므로 좀 더 간단한 코딩이 된다!
/// Context Property 업데이트 안해주고 Signal 보내면 되기때문이다!
/// 업데이트가 굉장히 쉬워진다.


class ObjectListWrapper : public QObject
{
    Q_OBJECT
    // List 자체를 QML에 노출시킨다. 변화는 알아서 QML에서 알아채고, 업데이트 한다.
    Q_PROPERTY(QList<QObject*> mypersons READ mypersons WRITE setMypersons NOTIFY mypersonsChanged)
public:
    explicit ObjectListWrapper(QObject *parent = nullptr);
    bool initialize();
    Q_INVOKABLE void setNames(int index, const QString & names);
    Q_INVOKABLE void setAge(int index, const int & age);
    Q_INVOKABLE void setFavoriteColor(int index,const QString & favoriteColor);
    Q_INVOKABLE QList<QObject *> persons() const;
    Q_INVOKABLE void addPerson();
    QList<QObject*> mypersons() const;
    void setMypersons(QList<QObject*> mypersons);
    Q_INVOKABLE void callTest();
signals:
    void mypersonsChanged(QList<QObject*> mypersons);
private:
    void populateModelWithData();
    void resetModel();
    void printPersons();
    QList<QObject*> mPersons;//This should be QObject*, Person* is not going to work in QML
    QQmlApplicationEngine mEngine;
    //QList<QObject*> m_mypersons;
};

#endif // OBJECTLISTWRAPPER_H
