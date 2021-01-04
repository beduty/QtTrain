#include "stairchart.h"
#include <QPainter>
#include <QBrush>
#include <QPen>


StairChart::StairChart(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setWidth(400);
    setHeight(400);
}

void StairChart::drawStair(QPainter *painter, QRect mRect, QColor mColor, qreal barValue,int startingPoint)
{
    painter->setPen(mColor);
    painter->setBrush(QBrush(mColor));
    painter->drawRect(mRect.bottomLeft().x()+startingPoint,
                      mRect.bottomLeft().y()-barValue,
                      50,
                      barValue);
}

void StairChart::drawScale(QPainter *painter, QRect mRect)
{
    QPen mPen;
    mPen.setWidth(2);
    mPen.setColor(Qt::black);
    painter->setPen(mPen);

    painter->drawLine(mRect.bottomLeft()+QPoint(0,0),mRect.bottomLeft()+QPoint(20,0));
    painter->drawText(mRect.bottomLeft()+QPoint(3,-10),"0");

    painter->drawLine(mRect.bottomLeft()+QPoint(0,-100),mRect.bottomLeft()+QPoint(20,-100));
    painter->drawText(mRect.bottomLeft()+QPoint(3,-110),"100");

    painter->drawLine(mRect.bottomLeft()+QPoint(0,-200),mRect.bottomLeft()+QPoint(20,-200));
    painter->drawText(mRect.bottomLeft()+QPoint(3,-210),"200");

    painter->drawLine(mRect.bottomLeft()+QPoint(0,-300),mRect.bottomLeft()+QPoint(20,-300));
    painter->drawText(mRect.bottomLeft()+QPoint(3,-310),"300");
}

void StairChart::paint(QPainter *painter)
{
    QRect mRect(0,0,width(),height());
    painter->save();
    QPen mPen;
    mPen.setColor(Qt::gray);
    mPen.setWidth(3);
    painter->setPen(mPen);
    painter->setBrush(QBrush(bgColor()));
    painter->drawRect(mRect);

    painter->drawText(mRect.topLeft() + QPoint(30,30), title());
    for(int i = 0; i < m_stairs.size(); i++)
    {
        Stair* stair = m_stairs[i];
        painter->setPen(stair->color());
        painter->setBrush(QBrush(stair->color()));
        QRect stairRect(mRect.bottomLeft().x() + stair->from(),
                        mRect.bottomLeft().y() - stair->value(),
                        50, stair->value());
        painter->drawRect(stairRect);
        painter->setPen(Qt::white);
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(stairRect.topLeft().x()+10,
                          stairRect.topLeft().y()+10,
                          25,25);
        painter->setFont(QFont("Consolas", 10, QFont::Bold));
        painter->setPen(Qt::black);
        painter->drawText(stairRect.adjusted(15,15,0,0),stair->text());
    }
    painter->setFont(QFont("Consolas", 10));
    drawScale(painter, mRect);
    painter->restore();
}

QQmlListProperty<Stair> StairChart::stairs()
{
//    return  QQmlListProperty<Stair>(this, this, &StairChart::appendStair2,
//                                    nullptr, nullptr,nullptr);
    return QQmlListProperty<Stair>(this, this,
                                   &StairChart::appendStair,
                                   &StairChart::stairCount,
                                   &StairChart::stair,
                                   &StairChart::clearStairs);
}

QString StairChart::title() const
{
    return m_title;
}

QColor StairChart::bgColor() const
{
    return m_bgColor;
}

void StairChart::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void StairChart::setBgColor(QColor bgColor)
{
    if (m_bgColor == bgColor)
        return;

    m_bgColor = bgColor;
    emit bgColorChanged(m_bgColor);
}

void StairChart::appendStair(Stair *stair)
{
    m_stairs.append(stair);
}

int StairChart::stairCount() const
{
    return m_stairs.count();
}

Stair *StairChart::stair(int index) const
{
    return m_stairs.at(index);
}

void StairChart::clearStairs()
{
    m_stairs.clear();
}

void StairChart::appendStair(QQmlListProperty<Stair> *list, Stair *stair)
{
    reinterpret_cast<StairChart*>(list->data)->appendStair(stair);
}

int StairChart::stairCount(QQmlListProperty<Stair> *list)
{
    return reinterpret_cast<StairChart*>(list->data)->stairCount();
}

Stair *StairChart::stair(QQmlListProperty<Stair> *list, int idx)
{
    return  reinterpret_cast<StairChart*>(list->data)->stair(idx);
}

void StairChart::clearStairs(QQmlListProperty<Stair> *list)
{
    reinterpret_cast<StairChart*>(list->data)->clearStairs();
}

void StairChart::appendStair2(QQmlListProperty<Stair> *list, Stair *stair)
{
    StairChart* chart = qobject_cast<StairChart*> (list->object);
    if(chart){
        stair->setParent(chart);
        chart->m_stairs.append(stair);
        chart->stairsChanged();
    }
}



















