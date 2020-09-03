#ifndef JOKE_H
#define JOKE_H

#include <QObject>

// Item 클래스를 만들어준다.
// ListView의 Model 하나를 이루는 정보를 담기 위해서 사용한다.
class Joke : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString joke READ joke WRITE setJoke NOTIFY jokeChanged)
public:
    explicit Joke(const QString &joke, QObject *parent = nullptr);
    QString joke() const;

public slots:
    void setJoke(QString joke);

signals:
    void jokeChanged(QString joke);

private:
    QString m_joke;
};

#endif // JOKE_H
