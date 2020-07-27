#include "mydialog.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QLineEdit>
#include <QVBoxLayout>

MyDialog::MyDialog(QWidget *parent):QDialog(parent)
{
    // new로 Stack이 아닌, Heap에 생성하는 것을 추천한다. (QWidget 사용하는 경우에)
    lineEdit = new QLineEdit;
    QObject::connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(myTextChanged(const QString&)));
    //connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(myTextChanged(const QString&)));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    setLayout(layout);

}

void MyDialog::closeEvent(QCloseEvent *event)
{
    //event->ignore(); // 들어온 이벤트 무시할 수 있다.
    //event->accept(); // 들어온 이벤트 받아들이다.

    QMessageBox::StandardButton yesno = QMessageBox::question(this, "Exit", "yes or no", QMessageBox::Yes|QMessageBox::No);
    if(yesno == QMessageBox::Yes){
        event->accept();
    }
    else if(yesno == QMessageBox::No){
        event->ignore();
    }
}

void MyDialog::myTextChanged(const QString &text)
{
    if(text == "qt5"){
        // 커스텀한 시그널을 부르자!
        emit onKeywordMatched(text);
    }

}
