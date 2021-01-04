#ifndef STAIRCHART_H
#define STAIRCHART_H

#include <QObject>
#include <QQuickPaintedItem>
#include "stair.h"


// Chart 데이터 모델과 차트 그리기를 수행한다.
// 1. 데이터는 모델로 관리한다. --> QList<Stair*> m_stairs;
// 2. 모델로부터 데이터 받아서 onPaint에서 Chart를 그린다.(QPainter)
// 3. 모델의 데이터는 어디서 추가하나..?
//    - Cpp 모델의 경우, C++에서 데이터 채우면 QML에서 변화를 감지하여 GUI 업데이트 한다.
//    - Qml에서 Chart데이터를 구성한다고 하면 어떻게 해야할까?? -> QQmlListProperty!
// 4. QQmlListProperty
///   - QML에서 model 설정할 수 있는 인터페이스를 뺴줘야 한다. -> StairChart 클래스
///   - QML에서 Model을 설정할 수 있도록 객체 인터페이스 빼줘야 한다. -> Stair 클래스
///   - Model 인터페이스 받아서 List([..]) 내부에 객체 인스턴스 추가해준다!
///   - Model 인터페이스 역할을 하는 것이 Q_PROPERTY(QQmlListProperty<Stair> stairs ..)
///      -> 이를 QML에서 알아들을 수 있도록 Q_CLASSINFO("DefaultProperty", "stairs")
///   - QML에서는 stairs: [..] 내부에 Stair{..} 인스턴스 추가해준다.
//         StairChart{
//             stairs : [
//                  Stair{
//                      color: "red"
//                      ...
//                  }
//                  Stair{}
//                  Stair{}
//             ]
//         }
// 5. Getter는 QQmlListProperty<Stair> 이지만, Member는 QList<Stair*> m_stairs;로 관리한다.
///  member인 QList<Stair*>를 어떻게 관리하나?
///   -> 0) 추가 // 개수반환 // 값 1개반환(idx) // 삭제
///   -> 1) QList<..*> 용 인터페이스를 만든다.
///   -> 2) QList-> QQmlListProperty로 변환할 메소드를 정의한다.
///   -> 3) QML에서 호출할 Q_PROPERTY를 만든다.

class StairChart : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QColor bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_PROPERTY(QQmlListProperty<Stair> stairs READ stairs NOTIFY stairsChanged)
    Q_CLASSINFO("DefaultProperty", "stairs")
    // QML에서는 stairs : [...] 로 List구성한다.

public:
    explicit StairChart(QQuickItem *parent = nullptr);

signals:
    void titleChanged(QString title);
    void bgColorChanged(QColor bgColor);
    void stairsChanged();

public:
    void paint(QPainter *painter); 
    QQmlListProperty<Stair> stairs();

public:
    QString title() const;
    QColor bgColor() const;

public slots:
    void setTitle(QString title);
    void setBgColor(QColor bgColor);

public:
    // QList<Stair*>용 인터페이스
    void appendStair(Stair*);
    int stairCount() const;
    Stair *stair(int) const;
    void clearStairs();

private:
    // QList-> QQmlListProperty로 변환할 때 필요한 메소드
    /// QQmlListProperty(QObject *object, void *data
    ///                  , QQmlListProperty::AppendFunction append
    ///                  , QQmlListProperty::CountFunction count
    ///                  , QQmlListProperty::AtFunction at
    ///                  , QQmlListProperty::ClearFunction clear
    /// ) 에 넣어주기 위한 append,count, at, clear 함수를 정의한다.
    /// QML에서 알아서 이를 사용한다.
    static void appendStair(QQmlListProperty<Stair>*, Stair*);
    static int stairCount(QQmlListProperty<Stair>*);
    static Stair* stair(QQmlListProperty<Stair>*, int);
    static void clearStairs(QQmlListProperty<Stair>*);




    static void appendStair2(QQmlListProperty<Stair>* list, Stair* stair);
    void drawStair(QPainter *painter, QRect mRect, QColor mColor, qreal barValue,int startingPoint);
    void drawScale(QPainter *painter, QRect mRect);

private:
    QString m_title;
    QColor m_bgColor;
    //QQmlListProperty<Stair> m_stairs;
    QList<Stair*> m_stairs;
};

#endif // STAIRCHART_H
