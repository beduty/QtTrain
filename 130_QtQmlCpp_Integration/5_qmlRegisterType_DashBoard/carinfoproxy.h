#ifndef CARINFOPROXY_H
#define CARINFOPROXY_H
#include <QObject>
#include "carinfo.h"
/// 프록시 패턴.
///   1. 일종의 비서(대리자)다.
///   2. 인터페이스 역할만 하여 외부의 요청을 수행하는 역할을 한다.
///   3. 여기서는 CarInfoProxy를 사용하여 QML과의 인터페이스를 수행한다.
///   4. Q_PROPERTY 의 READ는 실제 객체인 CarInfo m_car;에서 수행한다.
///   5. 프록시 패턴을 위해서 외부와의 인터페이스를 만들어준 것처럼,
///       대리자와 실제 객체간에도 요청하고 응답을 받는 인터페이스가 필요하다.
///
///   --> 가져다 쓰는 QML 입장에서는 인터페이스만 알면되기 때문에 간편하다!

class CarInfoProxy : public QObject
{
    Q_OBJECT
    /// CarInfo의 Q_PROPERTY인 CarInfoEngine과 speed, distance에 접근 할 수 있도록,
    /// QML에 인터페이스 마련해주도록 동일하게 Q_PROPERY 대리자를 만든다.
    Q_PROPERTY(CarInfoEngine *engine READ engine NOTIFY engineChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)

public:
    explicit CarInfoProxy(QObject *parent = nullptr);
    CarInfoEngine * engine() const;
    int speed() const;
    double distance() const;
    bool visible() const;

public slots:
    void setSpeed(int speed);
    void setDistance(double distance);
    void setVisible(bool v);

signals:
    void engineChanged(CarInfoEngine * engine);
    void speedChanged(int speed);
    void distanceChanged(double distance);
    void visibleChanged(bool visible);

private:
    CarInfo m_car;
    // 프록시 패턴이므로 CarInfo 하나만 유지한다.
//    CarInfoEngine * m_engine;
//    int m_speed;
    //    double m_distance;
    bool m_visible;
};

#endif // CARINFOPROXY_H
