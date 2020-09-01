#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Player : public QGraphicsPixmapItem
{
public:
    Player(QGraphicsItem *parent = 0);
    int direction() const;
    void setDirection(int direction);

private:
    // 0이면 Stop, 1이면 우측 이동, -1이면 좌측이동.
    int m_direction;
};

#endif // PLAYER_H
