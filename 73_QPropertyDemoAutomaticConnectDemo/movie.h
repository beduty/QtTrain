#ifndef MOVIE_H
#define MOVIE_H

#include <QObject>

class Movie : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString mainCharcter READ mainCharcter WRITE setmainCharcter NOTIFY mainCharcterChanged)
    Q_PROPERTY(QString title READ title WRITE settitle NOTIFY titleChanged)
public:
    explicit Movie(QObject *parent = nullptr);
    QString mainCharcter() const;
    QString title() const;

public slots:
    void setmainCharcter(QString mainCharcter);
    void settitle(QString title);

signals:
    void mainCharcterChanged(QString mainCharcter);
    void titleChanged(QString title);
private:
    QString m_mainCharcter;
    QString m_title;

};

#endif // MOVIE_H
