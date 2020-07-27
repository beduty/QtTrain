#include "widget.h"
#include <QApplication>
#include "mydialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDialog* dialog = new MyDialog;
    dialog->show();

//    Widget w;
//    w.show();
    return a.exec();
}
