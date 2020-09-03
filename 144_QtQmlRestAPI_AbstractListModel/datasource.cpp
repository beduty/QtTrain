#include "datasource.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

DataSource::DataSource(QObject *parent) : QObject(parent),
    mNetManager(new QNetworkAccessManager(this)),
    mNetReply(nullptr),
    mDataBuffer(new QByteArray)
{

}

void DataSource::fetchJokes(int number)
{
    const QUrl API_ENDPOINT("http://api.icndb.com/jokes/random/" + QString::number(number));
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);

    mNetReply = mNetManager->get(request);
    connect(mNetReply, &QIODevice::readyRead, this, &DataSource::dataReadyRead);
    connect(mNetReply, &QNetworkReply::finished, this, &DataSource::dataReadFinished);
}

void DataSource::addJoke(Joke *joke)
{
    emit preItemAdded();
    mJokes.append(joke);
    emit postItemAdded();
}

void DataSource::addJoke()
{
    Joke *joks = new Joke("Test Joke Added First", this);
    addJoke(joks);
}

void DataSource::addJoke(const QString &jokeParam)
{
    Joke *joke = new Joke(jokeParam,this);
    addJoke(joke);
}

void DataSource::removeJoke(int index)
{
    emit preItemRemoved(index);
    mJokes.removeAt(index);
    emit postItemRemoved();
}

void DataSource::removeLastJoke()
{
    if(!mJokes.isEmpty()){
        removeJoke(mJokes.size()-1);
    }
}

QList<Joke *> DataSource::dataItems()
{
    return mJokes;
}

void DataSource::dataReadyRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

void DataSource::dataReadFinished()
{
    // Parse the Json
    if(mNetReply->error())
        qDebug() << "Thers was some error : " << mNetReply->errorString();
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
        QJsonObject data = doc.object();
        QJsonArray array = data["value"].toArray();
        qDebug() << "Number of jokes : " << array.size();
        for(int i = 0; i < array.size(); i++){
            QJsonObject object = array.at(i).toObject();
            QString joke = object["joke"].toString();
            addJoke(joke);
        }
        mDataBuffer->clear();
    }
}






















