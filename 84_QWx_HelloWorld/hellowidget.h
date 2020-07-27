#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class HelloWidget; }
QT_END_NAMESPACE

class HelloWidget : public QWidget
{
    Q_OBJECT

public:
    HelloWidget(QWidget *parent = nullptr);
    ~HelloWidget();

private:
    Ui::HelloWidget *ui; // 디자인 결과등을 저장하는 객체.
    // .ui에서 디자인한 내용을 바탕으로 알아서 클래스 만들어준다.
    // 객체의 종류와 이름, 위치,시그널, 슬롯 등을 알아서 설정해준다. (사용자가 따로 신경쓰지 않도록)
    // 결과 파일로 "ui_hellowidget.h"가 생성되는데, 이것은 Build시스템이 만들어준다.
    // 해당 부분은 hellowidget.cpp의 상단에 #include "ui_hellowidget.h"로 들어가 있다.
};
#endif // HELLOWIDGET_H
