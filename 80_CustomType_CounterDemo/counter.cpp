#include "counter.h"
#include <QDebug>
Counter::Counter(QObject *parent) : QObject(parent),m_up(true), m_count(0), m_timer(new QTimer(this))
{
    qDebug() << "Created Counter instance";
    m_timer->setInterval(500);
    connect(m_timer, &QTimer::timeout, [=](){
        if(m_up){
            ++m_count;
        }else{
            --m_count;
        }
        emit countChanged(m_count);  // 여기서 보내줘야 QML에서 Reactive하게 값을 변경해줄 수 있다. (PROPERTY BINDING!!!)

        qDebug() << "Cur Count : " << m_count;
    });
}

int Counter::count() const
{
    return m_count;
}

void Counter::setCount(int count)
{
    if (m_count == count)
        return;

    m_count = count;
    emit countChanged(m_count);
}

void Counter::start()
{
    m_timer->start();
}

void Counter::stop()
{
    m_timer->stop();
}

bool Counter::up() const
{
    return m_up;
}

void Counter::setUp(bool up)
{
    if (m_up == up)
        return;

    m_up = up;
    emit upChanged(m_up);
}