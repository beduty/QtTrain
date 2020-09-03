#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "joke.h"

// ListView의 아이템인 Joke클래스를 QList<Joke*>를 저장한다.
// DataSource클래스는 QList<Joke*>에 Item을 Add 또는 Remove하는 인터페이스를 제공한다.
// Add는 QNetworkAccessManager로 데이터를 웹에서 받아온다. Json으로 들어온 데이터를 Parsing하고 addJoke한다.!
class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = nullptr);
    void addJoke(Joke* joke);
    QList<Joke*> dataItems();
    Q_INVOKABLE void addJoke();
    Q_INVOKABLE void addJoke(const QString& jokeParam);
    Q_INVOKABLE void removeJoke(int index);
    Q_INVOKABLE void removeLastJoke();
    Q_INVOKABLE void fetchJokes(int number);

signals:
    void preItemAdded();
    void postItemAdded();
    void preItemRemoved(int index);
    void postItemRemoved();

private slots:
    void dataReadyRead();
    void dataReadFinished();

private:
    QNetworkAccessManager *mNetManager;
    QNetworkReply *mNetReply;
    QByteArray *mDataBuffer;
    QList<Joke*> mJokes;
};

#endif // DATASOURCE_H
