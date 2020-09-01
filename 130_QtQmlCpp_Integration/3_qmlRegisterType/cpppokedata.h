#ifndef CPPPOKEDATA_H
#define CPPPOKEDATA_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QVariantMap>

class cppPokeData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList imgUrls READ imgUrls NOTIFY imgUrlsChanged)

public:
    explicit cppPokeData(QObject *parent = nullptr);
    Q_INVOKABLE void fetch();
    QStringList imgUrls() const;

signals:
    void imgUrlsChanged(QStringList imgUrls);

private slots:
    void dataReadyRead();
    void dataReadFinished();

private:
    QNetworkAccessManager *mNetManager;
    QNetworkReply *mNetReply;
    QByteArray* mDataBuffer;
    QStringList m_imgUrls;
};

#endif // CPPPOKEDATA_H
