#include "cpppokedata.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

cppPokeData::cppPokeData(QObject *parent) : QObject(parent)
  , mNetManager(new QNetworkAccessManager(this))
  , mNetReply(nullptr)
  , mDataBuffer(new QByteArray)
{
}

void cppPokeData::fetch()
{
    const QUrl API_ENDPOINT("https://raw.githubusercontent.com/Biuni/PokemonGO-Pokedex/master/pokedex.json");
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);
    mNetReply = mNetManager->get(request);
    connect(mNetReply, &QIODevice::readyRead, this, &cppPokeData::dataReadyRead);
    connect(mNetReply, &QNetworkReply::finished, this, &cppPokeData::dataReadFinished);
}

QStringList cppPokeData::imgUrls() const
{
    return m_imgUrls;
}

void cppPokeData::dataReadyRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

void cppPokeData::dataReadFinished()
{
    if(mNetReply->error()){
        qDebug() << "There was some error : " << mNetReply->errorString();
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
        QJsonObject data = doc.object();
        QJsonArray array = data["pokemon"].toArray();
        for(int i = 0; i < array.size(); ++i){
//            QString string = QString("https://raw.githubusercontent.com/fanzeyi/pokemon.json/master/images/%1.png")
//                                            .arg(array.at(i)["id"].toInt(), 3, 10, QLatin1Char('0'));
            QString string = array.at(i)["name"].toString();
            m_imgUrls.push_back(string);
            if(i==20)
                break;
        }
        emit imgUrlsChanged(m_imgUrls);
    }
}











