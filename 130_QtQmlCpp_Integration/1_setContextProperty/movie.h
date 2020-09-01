#ifndef MOVIE_H
#define MOVIE_H

#include <QObject>

class Movie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString character READ character WRITE setCharacter NOTIFY characterChanged)

public:
    explicit Movie(QObject *parent = nullptr);
    QString title() const;
    QString character() const;

public slots:
    void setTitle(QString title);
    void setCharacter(QString character);

signals:
    void titleChanged(QString title);
    void characterChanged(QString character);

private:
    QString m_title;
    QString m_character;
};

#endif // MOVIE_H
