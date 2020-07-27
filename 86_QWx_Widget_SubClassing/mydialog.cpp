#include "mydialog.h"
#include <QMessageBox>
#include <QCloseEvent>

MyDialog::MyDialog(QWidget *parent) : QDialog(parent)
{

}

void MyDialog::closeEvent(QCloseEvent * event)
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
