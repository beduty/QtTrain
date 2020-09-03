#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "person.h"

// Q_PROPERTY(QList<QObject*> persons..)로 QML에 넘겨주면, mPersons의 Object들의 변경사항을
// QML이 알아차리고, GUI 갱신을 수행한다. 변경사항에 대해서만 Refresh를 하기 때문에 굉장히 좋다!
// 문제는 addPerson 하거나 remove할 때는 QList 자체의 변경사항이 있기때문에 GUI에서는 모든 내용을 다 Refresh해서 비싼작업이 되었다.

// QAbstractListModel클래스는 이 또한 해결해준다! 또한 사용하기 편하게 되어 있고, cpp 연산도 빠르기 때문에 좋다!!
// Model의 중요 개념은 다음과 같다.
// 1. Role : 섹션. 엑셀로 치면 열 제목에 해당된다. 데이터 유형이된다.
class PersonModel : public QAbstractListModel
{
    Q_OBJECT
    // Role은 섹션, Column 의 느낌이라고 보면된다.
    // QML에서 모델을 사용하려면 Role을 직접 정의해줘야한다.
    // Qt::UserRole과 함께 roleNames()으로 QML에서 접근하기 위한 QByteArray를 지정해줘야 한다.
    enum PersonRoles{
        NamesRole = Qt::UserRole +1,
        FavoriteColorRole,
        AgeRole
    };

public:
    explicit PersonModel(QObject *parent = nullptr);
    void addPerson(Person *person);
    Q_INVOKABLE void addPerson();
    Q_INVOKABLE void addPerson(const QString &names, const int &age);
    Q_INVOKABLE void removePerson(int index);
    Q_INVOKABLE void removeLastPerson();

public:
// QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    // QML에서 리스트 모델을 변경하기 위해서는
    //  1. Qt::ItemIsEditable를 리턴해주는 flags()를 재정의 해줘야한다.
    //  2. 실질적으로 데이터를 변경하고 dataChanged SIGNAL을 날려주는 setData도 재정의 해준다.
    //      -> QML에서는 model.names2 = text 로 해주면
    //      -> cpp에서는 setData(index, text, NamesRole)로 들어온다!
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // QML에서 모델의 데이터에 접근하기 위해서는 QML이 알아들을 수 있도록
    // role를 지정해줘야 한다!
    QHash<int, QByteArray> roleNames() const;

private:
    // 데이터 실체이다! QObject*로 안해도 된다!
    QList<Person*> mPersons;
};

#endif // PERSONMODEL_H
