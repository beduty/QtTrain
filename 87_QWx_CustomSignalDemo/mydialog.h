#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QDialog>
#include <QString>
//#include <QLineEdit>
class QLineEdit;
class MyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget* parent = nullptr);
    void closeEvent(QCloseEvent *) override;

private:
    QLineEdit* lineEdit;
    // QLineEdit은 textChaned, editFinished 등의 시그널을 Emit한다.

private slots:
    void myTextChanged(const QString&);
signals:
    void onKeywordMatched(const QString&);
};

#endif // MYDIALOG_H
