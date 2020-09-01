#ifndef SINEITEM_H
#define SINEITEM_H
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class SineItem : public QGraphicsItem
{
public:
    SineItem();
    float maxX();
    void setMaxX(float value);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    float m_maxX = 50;
};

#endif // SINEITEM_H
