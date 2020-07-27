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
    //Q_PROPERTY(bool up READ up WRITE setUp NOTIFY upChanged)
    Q_PROPERTY(Counting::CountDirection counting READ counting WRITE setCounting NOTIFY countingChanged)

public:
    //bool up() const;
    int count() const;
    Counting::CountDirection counting() const;

public slots:
    //void setUp(bool up);
    void setCount(int count);
    void setCounting(Counting::CountDirection counting);

    // Qml에서 사용하기 위해서는 Q_INVOKABLE이 필요하다.
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void countChanged(int count);
    void upChanged(bool up);
    void countingChanged(Counting::CountDirection counting);

private:
    int m_count;
    //bool m_up;
    QTimer* m_timer;
    Counting::CountDirection m_counting;
};

#endif // COUNTER_H
