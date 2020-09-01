#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>
#include "counting.h"

class Counter : public QObject
{
    Q_OBJECT

public:
    explicit Counter(QObject *parent = nullptr);
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(Counting::CountDirection counting READ counting WRITE setCounting NOTIFY countingChanged)
    int count() const;
    Counting::CountDirection counting() const;

public slots:
    void setCount(int count);
    void setCounting(Counting::CountDirection counting);

    // Qml에서 사용하기 위해서는 Q_INVOKABLE이 필요하다.
    Q_INVOKABLE void start(); // 타이머 시작
    Q_INVOKABLE void stop();

signals:
    void countChanged(int count);
    void countingChanged(Counting::CountDirection counting);

private:
    QTimer* m_timer;
    int m_count;
    Counting::CountDirection m_counting;
};

#endif // COUNTER_H
