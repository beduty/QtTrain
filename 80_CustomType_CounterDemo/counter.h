#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>

class Counter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
    Q_PROPERTY(bool up READ up WRITE setUp NOTIFY upChanged)

public:
    explicit Counter(QObject *parent = nullptr);

public:
    bool up() const;
    int  count() const;
    void setUp(bool up);
    void setCount(int count);

    //Helper Methods
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void upChanged(bool up);
    void countChanged(int count);

private:
    bool m_up;
    int m_count;
    QTimer *m_timer;
};

#endif // COUNTER_H
