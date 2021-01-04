#ifndef STAIRCHART_H
#define STAIRCHART_H

#include <QObject>
#include <QQuickPaintedItem>
class StairChart : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit StairChart(QQuickItem *parent = nullptr);

public:
// QQuickPaintedItem interface
    void paint(QPainter *painter);

private:
    void drawStair(QPainter* painter, QRect mRect, QColor mColor, qreal barValue, int startingPoint);
    void drawScale(QPainter* painter, QRect mRect);

};

#endif // STAIRCHART_H
