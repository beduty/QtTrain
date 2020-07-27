#include "counter.h"
#include <QDebug>
Counter::Counter(QObject *parent) : QObject(parent),/* m_up(true),*/
    m_count(0),
    m_timer(new QTimer(this)),
    m_counting(Counting::CountDirection::UP)
{
    qDebug() << "Create Counter Instance";
    m_timer->setInterval(500);
    connect(m_timer, &QTimer::timeout, [=](){

        if(m_counting == Counting::CountDirection::UP )
            ++m_count;
        else
            --m_count;

        emit countChanged(m_count);
    });

}

int Counter::count() const
{
    return m_count;
}

//bool Counter::up() const
//{
//    return m_up;
//}

void Counter::start()
{
    m_timer->start();
}

void Counter::stop()
{
    m_timer->stop();
}

Counting::CountDirection Counter::counting() const
{
    return m_counting;
}

void Counter::setCounting(Counting::CountDirection counting)
{
    if (m_counting == counting)
        return;

    m_counting = counting;
    emit countingChanged(m_counting);
}

void Counter::setCount(int count)
{
    m_count = count;
}

//void Counter::setUp(bool up)
//{
//    if (m_up == up)
//        return;

//    m_up = up;
//    emit upChanged(m_up);
//}
