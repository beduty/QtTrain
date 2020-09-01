#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsEllipseItem>

class Coin : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)
    /// opacity와 rect는 QGracphicItem의 기본 속성들이다.
    ///  이때문에 Getter와 Setter등을 직접 지정할 필요가 없다.
    ///  QGracphicItem를 상속받았기 때문에 pos, scale, rotation, rect, opacity등
    ///  다만, Animation의 propertyName 을 지정하기 위해서 Q_PROPERTY를 추가하였다.

public:
explicit Coin(QGraphicsItem *parent = 0);
//    qreal opacity() const;
//    QRectF rect() const;
    enum {Type = UserType +1};
    int type() const;
    void explode();

public slots:
//    void setOpacity(qreal opacity);
//    void setRect(QRectF rect);

private:
    qreal m_opacity;
    QRectF m_rect;
    bool m_explosion;
};

#endif // COIN_H
