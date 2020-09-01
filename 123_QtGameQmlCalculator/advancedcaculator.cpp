#include "advancedcaculator.h"
#include <limits>
AdvancedCaculator::AdvancedCaculator(QObject *parent) : QObject(parent)
{
    setType(4);
}

double AdvancedCaculator::factorial(int argument)
{
    if(argument<0)
        return std::numeric_limits<double>::quiet_NaN();
    if(argument>180)
        return std::numeric_limits<double>::infinity();

    double r = 1.0;
    for(int i = 2; i <= argument; ++i)
        r *= i;
    return r;
}

int AdvancedCaculator::type() const
{
    return m_type;
}

void AdvancedCaculator::setType(int type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}
