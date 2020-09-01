#include "counter.h"

Counter::Counter(QObject *parent) : QObject(parent)
  , m_timer(new QTimer)
  , m_count(0)
  , m_counting(Counting::CountDirection::UP)
{
    m_timer->setInterval(500);
    connect(m_timer, &QTimer::timeout, [=](){
        if(m_counting == Counting::CountDirection::UP)
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

Counting::CountDirection Counter::counting() const
{
    return m_counting;
}

void Counter::setCount(int count)
{
    if (m_count == count)
        return;

    m_count = count;
    //emit countChanged(m_count);
}

void Counter::setCounting(Counting::CountDirection counting)
{
    if (m_counting == counting)
        return;

    m_counting = counting;
    emit countingChanged(m_counting);
}

void Counter::start()
{
    m_timer->start();

}

void Counter::stop()
{

    m_timer->stop();
}
