#include "cppdownload.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

CppDownLoad::CppDownLoad(QObject *parent) : QObject(parent)
  , mNetManager(new QNetworkAccessManager(this))
  , mNetReply(nullptr)
  , mDataBuffer(new QByteArray)
{
    setPosts({"Item1", "Item2", "Item3", "Item4"});

}

void CppDownLoad::downloadPosts(int number)
{
    const QUrl API_ENDPOINT("http://api.icndb.com/jokes/random/" + QString::number(number));
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);
    mNetReply = mNetManager->get(request);
    connect(mNetReply, &QIODevice::readyRead, this, &CppDownLoad::dataReadyRead);
    connect(mNetReply, &QNetworkReply::finished, this, &CppDownLoad::dataReadFinished);
}

void CppDownLoad::removeLast()
{
    if(false == m_posts.isEmpty()){
        m_posts.removeLast();
        emit postChanged(m_posts);
    }
}

QStringList CppDownLoad::posts()
{
    return m_posts;
}

void CppDownLoad::setPosts(QStringList posts)
{
    if (m_posts == posts)
        return;
    m_posts = posts;
    emit postChanged(m_posts);
}

void CppDownLoad::dataReadyRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

void CppDownLoad::dataReadFinished()
{
    if(mNetReply->error()){
        qDebug() << "There was some error : " << mNetReply->errorString();
    }
    else{
        //    {
        //        "type": "success",
        //        "value":  /// QJsonArray array = data["value"].toArray();
        //        [
        //            {
        //                "id": 268,
        //                "joke": "He who lives by the sword, ....",
        //                "categories": ["explicit"]
        //            },
        //            {
        //                "id": 110,
        //                "joke": "You know how they say if ....",
        //                "categories": []
        //            }
        //        ]
        //    }
        QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
        QJsonObject data = doc.object();
        QJsonArray array = data["value"].toArray();
        qDebug() << "Number of posts" << array.size();

        for(int i = 0 ; i < array.size(); i ++) {
            QJsonObject object = array.at(i).toObject();
            QString post = object["joke"].toString(); // "He who lives by the sword, ...."
            m_posts.append(post);
        }
        mDataBuffer->clear();
        emit postChanged(m_posts);
    }
}
