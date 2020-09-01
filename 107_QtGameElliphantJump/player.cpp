#include "player.h"
#include <QDebug>
Player::Player(QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent), m_direction(0)
{
    QPixmap pixmap(":/resources/elephant.png");
    setPixmap(pixmap);
    setOffset(-pixmap.width()/2, -pixmap.height()/2);
    // Transform 하기 쉽도록 중심점Center로 옮긴다.
    qDebug() << pixmap.width() << pixmap.height();
}

int Player::direction() const
{
    return  m_direction;
}

void Player::setDirection(int direction)
{
    m_direction = direction;
    if(m_direction != 0){
        QTransform transform;
        if(m_direction < 0){
            transform.scale(-1,1); // 반대로 가기위해 뒤집었다.
        }
        setTransform(transform);
    }
}
