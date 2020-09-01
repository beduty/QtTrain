#ifndef CARINFO_H
#define CARINFO_H

#include <QObject>
#include <QWidget>
#include <QDate>
namespace Ui {
    class Form;
}

class CarInfoEngine;
class CarInfo : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(CarInfoEngine* engine READ engine NOTIFY engineChanged)

public:
    CarInfo();
    int speed() const;
    double distance() const;
    CarInfoEngine* engine() const;
    void setSpeed(int speed);
    void setDistance(double distance);

private:
    // 그냥 UI 상에 기록된 값을 쓰고자 클래스 멤버를 주석처리했다.
//    int m_speed;
//    double m_distance;
signals:
    void speedChanged(int speed);
    void distanceChanged(double distance);
    void engineChanged();

private:
    Ui::Form *ui;
    CarInfoEngine* m_engine;
};

#endif // CARINFO_H



