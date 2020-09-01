#include "widget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGestureEvent>
Widget::Widget(QWidget *parent)
    : QWidget(parent), m_selectionStart(-1), m_selectionEnd(-1)
{
}

Widget::~Widget()
{
}

void Widget::addPoint(unsigned yVal)
{
    m_points << qMax(0u, yVal);
    update();
}

void Widget::clear()
{
    m_points.clear();
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QRect exposedRect = event->rect(); // Widget 전체 크기 QRect(0,0 640x480)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    /// rect()는 App의 크기인(640x480)이다. QRect(0,0 640x480)
    /// 여기에 adjusted(10,10,-10,-10)을 하면 LeftTop의 X,Y는 +10씩 Offset되고,
    /// RightBottom의 X,Y는 -10씩 Offset되어 결국 Width와 Height는 20씩 줄어든다.
    QRect r = rect().adjusted(10, 10, -10, -10); //QRect(10,10 620x460)
    painter.drawRoundedRect(r, 20, 20); // 사각형에 Round를 준다.
    painter.save();

    r.adjust(2, 2, -2, -2); // 2Px씩 줄어드는 결과가 된다. QRect(12,12 616x456)
    painter.setViewport(r); /// QRect(12,12 616x456)를 캔버스로 지정한다. 나머지 부분에는 그릴 수 없다.
    r.moveTo(0, -r.height() / 2); // W,H는 그대로 X,Y만 바뀐다. QRect(0,-228 616x456)
    painter.setWindow(r); /// 좌표계가 변경된다. 이제 App상의 좌측 상단에 점을 찍으려고 하면, painter->drawPoint(0,-228); 해줘야 한다.
    drawselection(&painter, r, exposedRect);
    drawChart(&painter, r, exposedRect);
    painter.restore(); // Save한 좌표계로 되돌린다.
}

void Widget::drawChart(QPainter *painter, const QRect &rect, const QRect &exposedRect)
{
    painter->setPen(Qt::red);
    painter->drawLine(exposedRect.left(), 0, exposedRect.width(),0);
    //painter->drawPoint(0,-228); /// App상의 좌측상단에 점이 찍힌다.
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    const int lastPoint = qMin(m_points.size(), exposedRect.right()+1);
    for(int i = exposedRect.left(); i < lastPoint; ++i)
    {
        if(m_selectionStart <= i && i <= m_selectionEnd)
            painter->setPen(Qt::white); // 선택된 사각형 내부면 흰색 ,
        else
            painter->setPen(Qt::blue); // m_selectionStart > m_selectionEnd 이면 그대로  blue이다.
        painter->drawLine(i, -m_points.at(i), i, m_points.at(i));
        // setWindow에 의해서 0,0이 중심선으로 옮겨져 왔으므로
        // 중심선 기준으로 위아래 동일길이로 선이 그려진다.
    }
    painter->restore();
    Q_UNUSED(rect)
}

void Widget::drawselection(QPainter *painter, const QRect &rect, const QRect &exposedRect)
{
    if(m_selectionStart<0){
        return;
    }
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(palette().highlight());
    QRect selectionRect = rect;
    selectionRect.setLeft(m_selectionStart);
    selectionRect.setRight(m_selectionEnd);
     // m_selectionStart > m_selectionEnd 이면 QRect의 Width가 -음 의 값이된다!

    //painter->drawRect(selectionRect);
    painter->drawRect(selectionRect.intersected(exposedRect));
    // setWindow로 지정한 곳과 ExposedRect간 겹치는 부분만 그린다.
    // setWindow은 화면의 절반(중심선 아래), ExposedRect는 Widget전체 크기 이므로
    // 중심선 아래 화면의 절반만 그려진다.

    painter->restore();
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_selectionStart = m_selectionEnd = event->pos().x() - 12;
    emit selectionChanged();
    update();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    m_selectionEnd = event->pos().x()-12;
    emit selectionChanged();
    update();
}

int Widget::selectionStart() const
{
    return m_selectionStart;
}

int Widget::selectionEnd() const
{
    return m_selectionEnd;
}
