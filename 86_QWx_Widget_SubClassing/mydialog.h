#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QDialog>

class MyDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyDialog(QWidget* parent = nullptr);
    void closeEvent(QCloseEvent *) override;
    // 시그널, 스롯 말고도 Event를 제공한다.
      // 키보드, 마우스, 타이머 이벤트, 생성, 종료이벤트 등등
      // QDialog를 상속받았기 떄문에 허락된 이벤트에 한하여 재정의 할 수 있다.
};

#endif // MYDIALOG_H
