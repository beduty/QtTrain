#include "view.h"
#include <QSpinBox>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QGraphicsLinearLayout>
#include <QPushButton>

View::View(QWidget *parent)
    :QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(new QGraphicsScene);

    QSpinBox *box = new QSpinBox;
    QGraphicsProxyWidget *proxyItem = new QGraphicsProxyWidget;
    proxyItem->setWidget(box);
    scene()->addItem(proxyItem);
    proxyItem->setRotation(45);
    proxyItem->setPos(100,50);
    /////////////////////////////////
    QGraphicsProxyWidget *edit = scene()->addWidget(new QLineEdit("Some Text"));
    QGraphicsProxyWidget *button = scene()->addWidget(new QPushButton("Click me!"));
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout;
    layout->addItem(edit);
    layout->addItem(button);
    QGraphicsWidget *graphicsWidget = new QGraphicsWidget;
    graphicsWidget->setLayout(layout);
    graphicsWidget->setPos(100,100);
    scene()->addItem(graphicsWidget);
    /////////////////////////////////
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(0);
    //proxy->setPos(100,100);
    proxy->setWidget(new QLineEdit(QObject::tr("Some Text232323")));
    scene()->addItem(proxy);
}

View::~View()
{
    // 뷰가 파기될 때 Scene을 삭제해줘야 한다.
    delete scene();
}

void View::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if(event->isAccepted())
        return;

    switch (event->button())
    {
        case Qt::RightButton:
        {
            QGraphicsItem *item = itemAt(event->pos());
            if(item){
                delete item;
            }
            event->accept();
            break;
        }
        default:
            break;
    }
}

void View::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    if(event->isAccepted())
    {
        return;
    }
    const qreal factor = 1.1;
    if(event->angleDelta().y()>0)
    {
        scale(factor,factor);
    }
    else{
        scale(1/factor, 1/factor);
    }
    event->accept();
}















