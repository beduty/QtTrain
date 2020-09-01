#include "filedownload.h"
#include <QPushButton>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFileDialog>
FileDownload::FileDownload(QWidget *parent) : QWidget(parent)
{
    m_network_manager = new QNetworkAccessManager(this);
    m_edit = new QPlainTextEdit;
    m_edit->setReadOnly(true);

    QPushButton* button = new QPushButton(tr("Load File"));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_edit);
    layout->addWidget(button);
    setLayout(layout);

    connect(button, &QPushButton::clicked, this, &FileDownload::startDownload);
    // 버튼을 클릭하면 데이터를 다운받도록 한다.
    connect(m_network_manager,&QNetworkAccessManager::finished, this, &FileDownload::downloadFinished);
    // 지정한 작업이 끝나면 finished가 비동기로 오는구나!!!
}

FileDownload::~FileDownload()
{

}

void FileDownload::startDownload()
{
    //QUrl url("https://localhost/testData/version.txt");
    QUrl url("https://www.google.com/robots.txt");
    QNetworkRequest request(url);
    m_network_manager->get(request);
    // url의 데이터를 받아온다. 작업이 완료되면 QNetworkAccessManager::finished 시그널이 들어온다!
}

void FileDownload::downloadFinished(QNetworkReply *reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        const QString error = reply->errorString();
        m_edit->setPlainText(error);
        return;
    }
    const QByteArray content = reply->readAll();

    auto path = QFileDialog::getSaveFileName();
    QFile  file(path);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&file);
    stream << content;
    file.close();

    m_edit->setPlainText(QString::fromUtf8(content));
    reply->deleteLater();
}
