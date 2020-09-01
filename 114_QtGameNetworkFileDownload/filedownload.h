#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QPlainTextEdit>
#include <QNetworkReply>

class FileDownload : public QWidget
{
    Q_OBJECT
public:
    explicit FileDownload(QWidget *parent = nullptr);
    virtual ~FileDownload();

private slots:
    void startDownload();
    void downloadFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager *m_network_manager;
    QPlainTextEdit *m_edit;
};

#endif // FILEDOWNLOAD_H
