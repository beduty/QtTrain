#ifndef CPPTIMER_H
#define CPPTIMER_H

#include <QObject>
#include <QTimer>

class cppTimer : public QObject
{
    Q_OBJECT
public:
    explicit cppTimer(QObject *parent = nullptr);

signals: // emit
    void ackQml(QString parameter);
    void timerTrigger(QString value);

public slots:
    void cppSlot();

private:
    QTimer *mTimer;
    int mValue;
};

#endif // CPPTIMER_H
