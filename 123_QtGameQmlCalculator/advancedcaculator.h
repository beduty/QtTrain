#ifndef ADVANCEDCACULATOR_H
#define ADVANCEDCACULATOR_H

#include <QObject>

class AdvancedCaculator : public QObject
{
    Q_OBJECT
public:
    explicit AdvancedCaculator(QObject *parent = nullptr);
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_INVOKABLE double factorial(int argument);
    /// Q_INVOKABLE은 QML에서 메소드를 호출할 수 있다.
    /// 클래서에서 허용된 부분만 가져다 쓸 수 있도록 해야 하는데, Q_INVOKABLE이 이런 역할을 한다.
    /// 자바스크립트 코드는 Q_INVOKABLE로 선언된 메소드만 엑세스할 수 있다.
    ///
    /// Q_GADGET 매크로를 쓰면, 자바스크립트에서 C++ 데이터 유형을 사용할 수 있다.
    /// Q_PROPERTY 매크로를 쓰면, 노출되어야 하는 속성을 선언할 수 있다.
    ///
signals:
    void typeChanged(int type);

public:
    int m_type = 1;
    int type() const;
public slots:
    void setType(int type);
};

#endif // ADVANCEDCACULATOR_H
