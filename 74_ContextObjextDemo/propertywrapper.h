#ifndef PROPERTYWRAPPER_H
#define PROPERTYWRAPPER_H

#include <QObject>
#include <QTimer>
class PropertyWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastname READ lastname WRITE setlastname NOTIFY lastnameChanged)
    Q_PROPERTY(QString firstname READ firstname WRITE setfirstname NOTIFY firstnameChanged)


public:
    explicit PropertyWrapper(QObject *parent = nullptr);

private:
    QString m_lastname;
    QString m_firstname;
    QTimer *m_timer;
    int m_random_number;

public:
    QString lastname() const;
    QString firstname() const;

public slots:
    void setlastname(QString lastname);
    void setfirstname(QString firstname);

signals:
    void lastnameChanged(QString lastname);
    void firstnameChanged(QString firstname);
};

#endif // PROPERTYWRAPPER_H
