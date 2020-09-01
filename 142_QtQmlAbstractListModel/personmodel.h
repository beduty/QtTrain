#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "person.h"

class PersonModel : public QAbstractListModel
{
    Q_OBJECT
    // Role은 섹션, Column 의 느낌이라고 보면된다.
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
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Person*> mPersons;
};

#endif // PERSONMODEL_H
