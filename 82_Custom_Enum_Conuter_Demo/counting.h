#ifndef COUNTING_H
#define COUNTING_H
#include <QObject>
class Counting : public QObject
{
    Q_OBJECT
private:
    explicit Counting(QObject *parent = nullptr);
public:
    enum CountDirection{
        UP,
        DOWN
    };
    Q_ENUM(CountDirection)
};

#endif // COUNTING_H
