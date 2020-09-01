#include "sineitem.h"
#include <QtMath>
#include <QPen>
static const float MAX_X = 50;

SineItem::SineItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

float SineItem::maxX()
{
    return m_maxX;
}

void SineItem::setMaxX(float value)
{
    if (m_maxX == value) {
        return;
    }
    prepareGeometryChange();
    m_maxX = value;
}

QRectF SineItem::boundingRect() const
{
    return QRectF(0,-1,m_maxX, 2);
}

void SineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 그래프의 크기가 커질 수록(휠 줌을 확대할 수록) levelOfDetailFromTransform의 항목의 값이 커진다.
    // 줌을 할수록 좀 더 자세한 표현을 할 수가 있게 된다! 줌이 없을때는 러프해져서 연산을 아낄수 있다.
    const qreal detail = QStyleOptionGraphicsItem::levelOfDetailFromTransform(
                painter->worldTransform());
    const qreal dx = 1/detail;

    QPen pen;
    pen.setCosmetic(true);
    if(option->state & QStyle::State_Selected){
        pen.setColor(Qt::green);
    }

    painter->setPen(pen);
    const int steps = qRound(m_maxX/dx);
    QPointF previousPoint(0,sin(0));
    for(int i =1; i < steps; ++i)
    {
        const float x = dx *i;
        QPointF point(x, sin(x));
        painter->drawLine(previousPoint, point);
        previousPoint = point;
    }
    Q_UNUSED(option); // 사용하지 않는 인수에 대한 컴파일러 경고를 억제한다.
    Q_UNUSED(widget);
}

void SineItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        float x = event->pos().x();
        QPointF point(x,sin(x));
        static const float r = 0.3;
        QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(-r,-r,2*r, 2*r, this);
        ellipse->setPen(Qt::NoPen);
        ellipse->setBrush(QBrush(Qt::red));
        ellipse->setPos(point);
        event->accept();
    }
    else{
        event->ignore();
    }
}






















