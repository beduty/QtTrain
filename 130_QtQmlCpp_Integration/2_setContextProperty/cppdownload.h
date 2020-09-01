#ifndef CPPDOWNLOAD_H
#define CPPDOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class CppDownLoad : public QObject
{
    Q_OBJECT
public:
    explicit CppDownLoad(QObject *parent = nullptr);
    Q_PROPERTY(QStringList posts READ posts WRITE setPosts NOTIFY postChanged)
    Q_INVOKABLE void downloadPosts(int number);
    Q_INVOKABLE void removeLast();

    QStringList posts();

public slots:
    void setPosts(QStringList posts);
signals:
    void postChanged(QStringList mPosts);

private slots:
    void dataReadyRead();
    void dataReadFinished();

private:
    QNetworkAccessManager* mNetManager;
    QNetworkReply* mNetReply;
    QByteArray* mDataBuffer;
    QStringList m_posts;
};

#endif // CPPDOWNLOAD_H
