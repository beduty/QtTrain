#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "person.h"
#include "datasource.h"

class PersonModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DataSource* dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)

    enum PersonRoles{
        NamesRole = Qt::UserRole +1,
        FavoriteColorRole,
        AgeRole
    };
public:
    explicit PersonModel(QObject *parent = nullptr);
    DataSource* dataSource() const;

public slots:
    void setDataSource(DataSource* dataSource);

signals:
    void dataSourceChanged(DataSource* dataSource);

public:
// QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QHash<int, QByteArray> roleNames() const;

private:
    DataSource* m_dataSource;
    bool m_signalConnected;

};

#endif // PERSONMODEL_H
