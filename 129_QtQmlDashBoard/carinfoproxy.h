#ifndef CARINFOPROXY_H
#define CARINFOPROXY_H

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

class CarInfoProxy : public QObject {
    Q_OBJECT
    Q_PROPERTY(CarInfoEngine *engine READ engine NOTIFY engineChanged)
    //Q_PROPERTY(bool visible READ visible NOTIFY visibleChanged)
    Q_PROPERTY(int speed READ speed  WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged)
public:
    CarInfoProxy(QObject *parent = 0);
    CarInfoEngine *engine() const;
    //bool visible() const;
    //void setVisible(bool v);
    int speed() const;
    void setSpeed(int v);
    double distance() const;
    void setDistance(double d);
signals:
    void engineChanged();
    //void visibleChanged(bool);
    void speedChanged(int);
    void distanceChanged(double);
private:
    CarInfo m_car;
};

#endif // CARINFOPROXY_H
