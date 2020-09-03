#ifndef JOKEMODEL_H
#define JOKEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "datasource.h"

// Joke 아이템을 QList<Joke*> 로 관리하는 DataSource를 QAbstractListModel의
// Private 멤버로 가지는 JokeModel이다.
// Model클래스는 QAbstractItemModel를 상속받고, 여러 재정의 함수를 정의한다.
class JokeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DataSource *datasource READ datasource WRITE setDatasource)
    enum ModelRoles{
        JokeDataRole = Qt::UserRole + 1
    };
public:
    explicit JokeModel(QObject *parent = nullptr);
    DataSource * datasource() const;

public slots:
    void setDatasource(DataSource * datasource);
signals:
public:
// QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QHash<int, QByteArray> roleNames() const;

private:
    DataSource * m_datasource;
    bool signalConnected = false;
};

#endif // JOKEMODEL_H
