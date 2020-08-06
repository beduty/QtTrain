#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

// 1. Test
//    QGraphicsScene scene;
//    //scene.setSceneRect(0,20,100,100);
//    QGraphicsRectItem *rectItem = new QGraphicsRectItem(QRect(0,0,100,50));
//    scene.addItem(rectItem);
//    QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(QRect(0,50,25,25));
//    scene.addItem(circleItem);
//    QGraphicsSimpleTextItem *textItem = new QGraphicsSimpleTextItem(QObject::tr("Demo"));
//    scene.addItem(textItem);
//    QGraphicsView view(&scene);
//    //view.setAlignment(Qt::AlignTop | Qt::AlignLeft);
////    view.scale(5,5);
////    view.rotate(20);
//    view.show();


// 2. Test
//    QGraphicsScene scene;
//    scene.addLine(-100,0,100,0);
//    scene.addLine(0,-100,0,100);
//    QGraphicsItem* rectItem = scene.addRect(-25,-25,50,50);
//    rectItem->setPos(75,75);
//    rectItem->setRotation(45);
//    QGraphicsView view(&scene);
//    view.show();


// 3. Test
//    QGraphicsScene scene;
//    scene.addLine(-100,0,100,0);
//    scene.addLine(0,-100,0,100);
//    QGraphicsItem* rectItem = scene.addRect(50,50,50,50);
//    rectItem->setTransformOriginPoint(75,75);
//    rectItem->setRotation(45);
//    QGraphicsView view(&scene);
//    view.show();

// 4. Make Group!
    // QObject의 Parent를 하나 만들고, 하위에 Child들을 넣을 수 있다.
    // Children은 기존 Screne에 독립되고,
    // Parent 좌표에 상대적인 위치와 Parent의 Transform에 상대적인 Transform을 가진다.
    QGraphicsScene scene;
    QGraphicsRectItem *item1 = createComplexItem(100,60,8);
    scene.addItem(item1);

    QGraphicsRectItem *item2 = createComplexItem(100,60,8);
    scene.addItem(item2);
    item2->setPos(200,0);
    item2->setRotation(20);
    item2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item2->setFlag(QGraphicsItem::ItemIsMovable, true);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setDragMode(QGraphicsView::RubberBandDrag);
    view.show();


    return a.exec();
}



QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius)
{
    QRectF rect(-width/2, -height/2, width, height);
    rect.translate(0.5, 0.5);
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
//    parent->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    parent->setFlag(QGraphicsItem::ItemIsMovable, true);
    return parent;
}















