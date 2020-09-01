#ifndef MYSCENE_H
#define MYSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include "player.h"
#include "backgrounditem.h"
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

// 큰~~ World중에서 Scene으로 표현된다.
// MyScene에서는 World와 Scene을 모두 관리한다.
//   -> initPlayField() 는 World 즉 이미지를 부르고, Scene을 초기화 한다. -> 배경 및 객체들을 부른다.
//   -> Timer로 움직이다. timeout 시그널받아서 movePlayer() 슬롯함수가 호출된다.


class MyScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)

public:
    explicit MyScene(QObject *parent = 0);

private:
    void initPlayField();
    void jump();
    void addHorizontalInput(int input);
    void applyParallax(qreal ratio, QGraphicsItem* item);
    qreal jumpFactor() const;

private:
    int m_fieldWidth; // 코끼리가 움직일 수 있는 가상거리
    qreal m_groundLevel; // 코끼기가 놓이는 바닥 위치
    qreal m_minX; // 코끼리가 움직일 수 있는 최소 위치
    qreal m_maxX; // 코끼리 맨 오른쪽 위치
    qreal m_currentX; // 현재 코끼리의 위치 (World상의 코끼리가 이동한 위치)
    QTimer m_timer; // 주기마다 timeout() 시그널을 받는다.
    int m_velocity;
    int m_worldShift; // 코끼리 제자리, 배경이 움직이며 이동효과. 배경이 얼마나 이동했는지 저장한다.
    int m_jumpHeight;
    qreal m_jumpFactor;
    int m_horizontalInput;

    Player* m_player;   // 코끼리로 대변되는 인스턴스 이다!
    BackgroundItem *m_sky; //  그냥 png 이미지만 부른다.
    BackgroundItem *m_trees;
    BackgroundItem *m_grass;
    QPropertyAnimation *m_jumpAnimation;
    QGraphicsRectItem *m_coins;


    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void jumpFactorChanged(qreal jumpFactor);

private slots:
    void movePlayer(); // timeout 시그널에 대응하는 slot함수
    void checkTimer();
    void checkColliding();
    void setJumpFactor(qreal jumpFactor);
};

#endif // MYSCENE_H
