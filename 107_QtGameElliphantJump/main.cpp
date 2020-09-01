#include <QApplication>
#include "player.h"
#include "myscene.h"
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Player player = new Player(this);

    MyScene scene;
    QGraphicsView view;
    view.setRenderHint(QPainter::Antialiasing);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setScene(&scene);
    view.setFixedSize(scene.sceneRect().size().toSize());
    view.show();

    return a.exec();
}
