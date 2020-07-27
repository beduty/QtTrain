#include "widget.h"
#include <QApplication>
#include "mydialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyDialog* dialog = new MyDialog;

    QObject::connect(dialog, SIGNAL(onKeywordMatched(const QString&)), &app, SLOT(quit()));
    dialog->show();


//    Widget w;
//    w.show();
    return app.exec();
}
