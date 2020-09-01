#include "carinfoproxy.h"

CarInfoProxy::CarInfoProxy(QObject *parent) : QObject(parent)
{
    // Proxy 패턴이 QML과 직접 소통을 하지만,
    // Proxy와 실제 객체와의 연결도 필요하다.
    connect(&m_car, &CarInfo::enginChanged,this, &CarInfoProxy::engineChanged);
    connect(&m_car, &CarInfo::speedChanged, this, &CarInfoProxy::speedChanged);
    connect(&m_car, &CarInfo::distanceChanged, this, &CarInfoProxy::distanceChanged);
    m_car.setVisible(true);
}

CarInfoEngine *CarInfoProxy::engine() const
{
    return m_car.engine();
}

int CarInfoProxy::speed() const
{
    return m_car.speed();
}

double CarInfoProxy::distance() const
{
    return m_car.distance();
}

bool CarInfoProxy::visible() const
{
    return m_car.isVisible();
}

void CarInfoProxy::setSpeed(int speed)
{
    m_car.setSpeed(speed);
}

void CarInfoProxy::setDistance(double distance)
{
    m_car.setDistance(distance);
}

void CarInfoProxy::setVisible(bool v)
{
    if(v == visible()) return;
    m_car.setVisible(v);
    emit visibleChanged(v);
}
