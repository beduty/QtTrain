#include <QNetworkRequest>
#include <QDebug>
#include "appwrapper.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQmlContext>

AppWrapper::AppWrapper(QObject *parent) : QObject(parent),
    mNetManager(new QNetworkAccessManager(this)),
    mNetReply(nullptr),
    mDataBuffer(new QByteArray)
{

}

void AppWrapper::fetchPosts(int number)
{
    const QUrl API_ENDPOINT("http://api.icndb.com/jokes/random/" + QString::number(number));
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);
    mNetReply = mNetManager->get(request);
    connect(mNetReply, &QIODevice::readyRead, this, &AppWrapper::dataReadyRead);
    connect(mNetReply, &QNetworkReply::finished, this, &AppWrapper::dataReadFinished);
}

void AppWrapper::removeLast()
{
    if(false == mJokes.isEmpty()){
        mJokes.removeLast();
        resetModel();
    }
}

QStringList AppWrapper::jokes() const
{
    return mJokes;
}

bool AppWrapper::initialize()
{
    mEngine.rootContext()->setContextProperty("Wrapper", this);
    resetModel();

    mEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if(mEngine.rootObjects().isEmpty()){
        return false;
    }
    else{
        return true;
    }
}

void AppWrapper::dataReadyRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

void AppWrapper::dataReadFinished()
{
    // Parse the JSON
    if(mNetReply->error()){
        qDebug() << "There was some error : " << mNetReply->errorString();
    }else{
        // Turn the data into a json document
        QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
        // Grab the value array
        QJsonObject data = doc.object();

        QJsonArray array = data["value"].toArray();
        qDebug() << "Number of jokes" << array.size();

        for(int i = 0; i< array.size(); i ++){
            QJsonObject object = array.at(i).toObject();
            QString joke = object["joke"].toString();
            mJokes.append(joke);
            //qDebug() << joke;
        }
        if(array.size() != 0){
            resetModel();
        }
        // Clear the buffer
        mDataBuffer->clear();
    }
}

void AppWrapper::resetModel()
{
    mEngine.rootContext()->setContextProperty("myModel", QVariant::fromValue(mJokes));
    // Why??
    // 인터넷에서 다운 데이터를 QML로 넘겨야 한다. (QStringLIst)
    // 많은 양의 데이터를 넘기면 복사할 때 시간이 오래걸릴 수 밖에 없겠지??
    // Q_PROPERTY 보다는 Q_INVOKABLE이 낫다. 하지만 이역시도 비효율적이다.
    //
    // --> C++에서 모델을 만들고, 이것을 setContextProperty로 QML에 노출시켜주는 방법이 좋다!
    //     복사하고 자시고 할 필요가 없기 때문!
}































