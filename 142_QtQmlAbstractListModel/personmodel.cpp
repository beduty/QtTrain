#include "personmodel.h"
#include <QtDebug>

PersonModel::PersonModel(QObject *parent) : QAbstractListModel(parent)
{
    addPerson(new Person("Jamie Lannister", "red", 33));
    addPerson(new Person("Marry Lane", "cyan", 26));
    addPerson(new Person("Steve Moors", "yellow", 44));
    addPerson(new Person("Victor Trunk", "dodgerblue", 30));
    addPerson(new Person("Ariel Geeny", "blue", 33));
    addPerson(new Person("Knut Vikran", "lightblue", 26));
}

void PersonModel::addPerson(Person *person)
{
    const int index = mPersons.size();
    // 해당 모델을 사용하는 View가 변화를 인지할 수 있도록
    // Insert하기 전에 호출해줘야 한다.
    beginInsertRows(QModelIndex(), index, index);
    mPersons.append(person);
    endInsertRows(); // model 변경완료를 View에게 알린다.
}

void PersonModel::addPerson()
{
    Person *person = new Person("Added Person", "yellowgreen", 45, this);
    addPerson(person);
}

void PersonModel::addPerson(const QString &names, const int &age)
{
    Person *person = new Person(names, "yellowgreen", age);
    addPerson(person);
}

void PersonModel::removePerson(int index)
{
    // 해당 모델을 사용하는 View가 변화를 인지할 수 있도록
    // Remove하기 전에 호출해줘야 한다.
    beginRemoveRows(QModelIndex(), index, index);
    mPersons.removeAt(index);
    endRemoveRows();// model 변경완료를 VIew에게 알린다.
}

void PersonModel::removeLastPerson()
{
    removePerson(mPersons.size() -1);
}

int PersonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return  mPersons.size();
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= mPersons.count())
        return QVariant();

    // 행과 열(Role)에 해당되는 데이터를 리턴한다.
    // 이는 QML에서 알아차리기 위함이며, 해당 데이터의 GUI만 Refresh된다!
    Person* person = mPersons[index.row()];
    if(role == NamesRole)
        return person->names();
    if(role == FavoriteColorRole)
        return person->favoriteColor();
    if(role == AgeRole)
        return person->age();
    return QVariant();
}

bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Person* person = mPersons[index.row()];
    bool somethingChanged = false;

    switch (role)
    {
        case NamesRole :
        {
            if(person->names() != value.toString()){
                qDebug() << "Changing names for " << person->names();
                person->setNames(value.toString());
                somethingChanged = true;
            }
            break;
        }
        case FavoriteColorRole :
        {
            if(person->favoriteColor() != value.toString()){
                qDebug() << "Changing color for " << person->names();
                person->setFavoriteColor(value.toString());
                somethingChanged = true;
            }
            break;
        }
        case AgeRole :
        {
            if(person->age() != value.toInt()){
                qDebug() << "Changing age for " << person->names();
                person->setAge(value.toInt());
                somethingChanged = true;
            }
            break;
        }
    }
    if(somethingChanged){
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const
{
    // QML에서 리스트 모델을 변경하기 위해서는
    //  -> Qt::ItemIsEditable를 리턴해주는 flags()로 재정의 해줘야한다.
    if(!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PersonModel::roleNames() const
{
    // QML에서는 여기서 지정한 QByteArray 즉, "names2"로 데이터의 Role에 접근할 수 있다.
    QHash<int , QByteArray> roles;
    roles[NamesRole] = "names2";
    roles[FavoriteColorRole] = "favoriteColor2";
    roles[AgeRole] = "age2";
    return roles;
}













