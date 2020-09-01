#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsRectItem *item1 = createComplexItem(100,60,8);
    scene.addItem(item1);

    QGraphicsRectItem *item2 = createComplexItem(100,60,8);
    scene.addItem(item2);
    item2->setPos(200,0);
    item2->setRotation(20);

    QGraphicsEllipseItem *circle1 = scene.addEllipse(0,0,100,50);
    circle1->setBrush(Qt::red);
    QGraphicsEllipseItem *circle2 = scene.addEllipse(50,0,100,50);
    circle2->setBrush(Qt::green);
    QGraphicsEllipseItem *circle3 = scene.addEllipse(0,25,100,50);
    circle3->setBrush(Qt::blue);
    QGraphicsEllipseItem *circle4 = scene.addEllipse(50,25,100,50);
    circle4->setBrush(Qt::gray);
    circle4->setZValue(1);
    circle3->setFlag(QGraphicsItem::ItemIsSelectable, true);
    circle3->setFlag(QGraphicsItem::ItemIsMovable, true);

    QGraphicsView view(&scene);
    view.show();

    return a.exec();
}



QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius)
{
    QRectF rect(-width/2, -height/2, width, height);
    QGraphicsRectItem *parent = new QGraphicsRectItem(rect);
    QRectF circleBoundary(-radius, -radius, 2*radius, 2*radius);
    for(int i = 0; i < 4; i ++)
    {
        QGraphicsEllipseItem *child = new QGraphicsEllipseItem(circleBoundary, parent);
        child->setBrush(Qt::black);
        QPointF pos;
        switch (i)
        {
        case 0:
            pos = rect.topLeft();
            break;
        case 1:
            pos = rect.bottomLeft();
            break;
        case 2:
            pos = rect.topRight();
            break;
        case 3:
            pos = rect.bottomRight();
            break;
        }
        child->setPos(pos);
    }
    parent->setFlag(QGraphicsItem::ItemIsSelectable, true);
    parent->setFlag(QGraphicsItem::ItemIsMovable, true);

    return parent;
}















