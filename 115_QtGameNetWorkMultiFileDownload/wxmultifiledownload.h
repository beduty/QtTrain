#ifndef WXMULTIFILEDOWNLOAD_H
#define WXMULTIFILEDOWNLOAD_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class WxMultiFileDownload; }
QT_END_NAMESPACE

class WxMultiFileDownload : public QWidget
{
    Q_OBJECT

public:
    WxMultiFileDownload(QWidget *parent = nullptr);
    ~WxMultiFileDownload();

private:
    Ui::WxMultiFileDownload *ui;
    QNetworkAccessManager *m_networkManager;
    QSignalMapper *m_imageFinishedMapper;

private slots:
    void load();
    void imageFinished(QObject* replyObject);
};
#endif // WXMULTIFILEDOWNLOAD_H
