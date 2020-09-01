#include "wxmultifiledownload.h"
#include "ui_wxmultifiledownload.h"
#include <QNetworkReply>
#include <QMessageBox>

/// NetWork상으로 여러 요청을 했을 때,요청만큼 Finished되었을때 처리할 Slot을 만들어줘야 한다.
/// 여기서는 QPlainTextEdit에 줄 별로 입력된 url 만큼 이미지 받아다가 새로운 화면을 만들어준다.
/// 따라서 유동적인 Slot을 만들기 위해서 QSignalMapper를 사용한다!

WxMultiFileDownload::WxMultiFileDownload(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WxMultiFileDownload)
{
    ui->setupUi(this);
    connect(ui->load, &QPushButton::clicked, this, &WxMultiFileDownload::load);

    m_networkManager = new QNetworkAccessManager(this);
    m_imageFinishedMapper = new QSignalMapper(this);

    connect(m_imageFinishedMapper, SIGNAL(mapped(QObject*)),this, SLOT(imageFinished(QObject*)));
    // QSignalMapper m_imageFinishedMapper 에 imageFinished를 연결시킨다.
    /// m_imageFinishedMapper로 시그널을 보내면, m_imageFinishedMapper에 연결된 imageFinished가 콜백된다.
}

WxMultiFileDownload::~WxMultiFileDownload()
{
    delete ui;
}

void WxMultiFileDownload::load()
{
    QStringList urls = ui->urls->toPlainText().split("\n", QString::SkipEmptyParts);
    for(const QString& url : urls)
    {
        QNetworkRequest request(url);
        QNetworkReply *reply = m_networkManager->get(request);
        connect(reply, SIGNAL(finished()), m_imageFinishedMapper, SLOT(map()));
        m_imageFinishedMapper->setMapping(reply, reply);
        /// url의 Request로 받은 응답을 QSignalMapper m_imageFinishedMapper에 등록한다.
        /// 응답완료 포인터 reply로 데이터가 들어오면 (finished), m_imageFinishedMapper에 연결된 slot이 콜백된다.
        /// setMapping(reply, reply);로 reply를 넣는 것은
        /// connect(m_imageFinishedMapper, SIGNAL(mapped(QObject*)),this, SLOT(imageFinished(QObject*)));
        /// 에서 QObject* 과 QObject*에 해당되는 값이다.
    }
}

void WxMultiFileDownload::imageFinished(QObject *replyObject)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(replyObject);
    if(!reply)
        return;

    QString url = reply->url().toString();
    if(reply->error() != QNetworkReply::NoError)
    {
        QMessageBox::critical(this, "", tr("Failed to load %1 : %2").arg(url).arg(reply->errorString()));
    }
    else
    {
        QByteArray data = reply->readAll();
        QPixmap pixmap;
        if(!pixmap.loadFromData(data)){
            QMessageBox::critical(this, "", tr("Failed to load pixmap from %1").arg(url));
        }
        else{
            QLabel *label = new QLabel();
            label->setWindowTitle(url);
            label->setPixmap(pixmap);
            label->show();
        }
    }
    reply->deleteLater();
}



























