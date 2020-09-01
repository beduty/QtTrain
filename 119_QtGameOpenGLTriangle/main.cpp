#include <QApplication>
#include "simpleglwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SimpleGLWindow window;
    window.resize(600,400);
    window.show();

    return a.exec();
}
