#ifndef CARINFO_H
#define CARINFO_H
#include <QObject>
#include <QWidget>
#include "carinfoengine.h"

namespace Ui {
class CarInfo;
}
// .pro에 QT += widgets를 추가해줘야한다.
class CarInfo : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(CarInfoEngine* engine READ engine NOTIFY enginChanged)
    // QML에서 클래스멤버(CarInfoEngine)에 접근할 수 있는 인터페이스다.

public:
    explicit CarInfo(QWidget *parent = nullptr);
    ~CarInfo();
    int speed() const;
    int distance() const;
    CarInfoEngine* engine() const;

public slots:
    void setSpeed(int speed);
    void setDistance(double distance);

signals:
    void speedChanged(int speed);
    void distanceChanged(double distance);
    void enginChanged(CarInfoEngine* engine);

private:
    Ui::CarInfo *ui;
    CarInfoEngine* m_engine;
};

#endif // CARINFO_H
