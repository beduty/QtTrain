#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius, bool bTextTransformIgnore);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;
    QGraphicsRectItem *item1 = createComplexItem(100,60,8, true);
    scene.addItem(item1);
    QGraphicsRectItem *item2 = createComplexItem(100,60,8, true);
    scene.addItem(item2);
    item2->setPos(200,0);
    item2->setRotation(20);
    QGraphicsRectItem *item3 = createComplexItem(100,60,8, false);
    scene.addItem(item3);
    item3->setPos(100,100);
    item3->setRotation(150);

    QGraphicsView view(&scene);
    view.resize(800,600);
    view.show();
    view.setRenderHint(QPainter::Antialiasing);
    view.scale(2,2);
    view.setDragMode(QGraphicsView::RubberBandDrag);

    ////////////////////////////////////////////////////////
    QRect rect = scene.sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    // 1. setRect로 장면의 직사각형을 결정한다. -> QRectF가 콜백
    // 2. QImage에 넣을때는 QRect가 되어야 하므로 toAlignedRect()로 반올림 하여 QRect를 받아온다.
    // 3. 받아온 Rect로 QImage를 만든다. (아직 초기화되지 않았다.)

    QPainter painter(&image);
    // 만든 QImage를 바탕으로 QPainter객체를 만든다.
    scene.render(&painter);
    // Scene에 Render로 Painter객체를 쓰면, image로 저장된다.
    image.save("scene.png");
    // 이미지를 저장한다.
    return a.exec();
}



QGraphicsRectItem *createComplexItem(qreal width, qreal height, qreal radius, bool bTextTransformIgnore)
{
    QRectF rect(-width/2, -height/2, width, height);
    rect.translate(0.5,0.5);
    QGraphicsRectItem *parent = new QGraphicsRectItem(rect);
    QPen pen = parent->pen();
    pen.setCosmetic(true);
    parent->setPen(pen);

    QRectF circleBoundary(-radius, -radius, 2*radius, 2*radius);
    for(int i = 0; i < 4; i++)
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

        if(bTextTransformIgnore == true)
        {
            QGraphicsSimpleTextItem *text =
                    new QGraphicsSimpleTextItem(QString::number(i), child);
            text->setBrush(Qt::green);
            QTransform transform;
            transform.translate(-text->boundingRect().width() / 2,
                                -text->boundingRect().height() / 2);
            text->setTransform(transform);
            text->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        }
        else{
            QGraphicsSimpleTextItem *text =
                new QGraphicsSimpleTextItem(QString::number(i), child);
            text->setBrush(Qt::green);
            text->setPos(-text->boundingRect().width() / 2,
                         -text->boundingRect().height() / 2);
            text->setBrush(Qt::green);
        }
    }
    parent->setFlag(QGraphicsItem::ItemIsSelectable, true);
    parent->setFlag(QGraphicsItem::ItemIsMovable, true);
    return parent;
}















