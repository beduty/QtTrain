#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QMetaObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//1. Pen/////////////////////////
//    QGraphicsScene scene;
//    static const int SIZE = 100;
//    static const int MARGIN = 10;
//    static const int FIGURE_COUNT = 5;
//    static const int LINE_COUNT = 500;

//    for(int figureNum = 0; figureNum < FIGURE_COUNT; ++figureNum)
//    {
//        QPainterPath path;
//        path.moveTo(0,0);
//        for(int i = 0; i < LINE_COUNT; ++i)
//        {
//            path.lineTo(qrand() % SIZE, qrand()%SIZE);
//        }
//        QGraphicsPathItem *item = scene.addPath(path);
//        item->setPos(figureNum * (SIZE + MARGIN), 0);
//    }
//    QGraphicsView view(&scene);
//    view.resize(800,600);
//    view.show();
//    view.setRenderHint(QPainter::Antialiasing);


//2. Brush/////////////////////////
    QGraphicsScene scene;
    QGraphicsEllipseItem *item1 = scene.addEllipse(0,0,100,50);
    item1->setBrush(Qt::red);
    item1->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item1->setFlag(QGraphicsItem::ItemIsMovable, true);


    QGraphicsEllipseItem *item2 = scene.addEllipse(50, 0, 100, 50);
    item2->setBrush(Qt::green);
    QGraphicsEllipseItem *item3 = scene.addEllipse(0, 25, 100, 50);
    item3->setBrush(Qt::blue);
    QGraphicsEllipseItem *item4 = scene.addEllipse(50, 25, 100, 50);
    item4->setBrush(Qt::gray);

    item2->setZValue(1);

    QGraphicsView view(&scene);
    view.resize(800,600);
    view.show();
    view.setRenderHint(QPainter::Antialiasing);


    return a.exec();
}
