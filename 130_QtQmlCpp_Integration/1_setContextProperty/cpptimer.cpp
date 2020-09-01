#include "cpptimer.h"

cppTimer::cppTimer(QObject *parent) : QObject(parent),
    mTimer(new QTimer(this)),
    mValue(0)
{
    connect(mTimer, &QTimer::timeout, [=](){
        ++mValue;
        emit timerTrigger(QString::number(mValue));
    });
    mTimer->start(1000);
}

void cppTimer::cppSlot()
{
    emit ackQml("ack from cpp");
}
