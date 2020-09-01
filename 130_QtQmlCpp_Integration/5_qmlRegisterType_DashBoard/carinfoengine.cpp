#include "carinfoengine.h"
#include <QtDebug>
CarInfoEngine::CarInfoEngine(QObject *parent) : QObject(parent),
    m_gear(4)
{

}

int CarInfoEngine::gear() const
{
    return m_gear;
}

int CarInfoEngine::rpm() const
{
    return m_rpm;
}

void CarInfoEngine::setGear(int gear)
{
    if (m_gear == gear)
        return;

    qDebug() << "gear Changed! : " << gear;
    m_gear = gear;
    emit gearChanged(m_gear);
}

void CarInfoEngine::setRpm(int rpm)
{
    if (m_rpm == rpm)
        return;
    qDebug() << "rpm Changed! : " << rpm;
    m_rpm = rpm;
    emit rpmChanged(rpm);
}
