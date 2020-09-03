#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString names READ names WRITE setNames NOTIFY nameChanged)
    Q_PROPERTY(QString favoriteColor READ favoriteColor WRITE setFavoriteColor NOTIFY favoriteColorChanged)

public:
    explicit Person(QObject *parent = nullptr);    
    Person(const QString &names, const QString &favoriteColor, const int &age, QObject *parent = nullptr);
    int age() const;
    QString names() const;
    QString favoriteColor() const;

public slots:
    void setAge(int age);
    void setNames(QString names);
    void setFavoriteColor(QString favoriteColor);

signals:
    void ageChanged(int age);
    void nameChanged(QString names);
    void favoriteColorChanged(QString favoriteColor);

private:
    int m_age;
    QString m_names;
    QString m_favoriteColor;
};

#endif // PERSON_H
