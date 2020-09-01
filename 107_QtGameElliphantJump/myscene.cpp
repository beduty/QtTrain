#include "myscene.h"
#include <QDebug>
#include "coin.h"

MyScene::MyScene(QObject *parent) :
    QGraphicsScene(parent)
  , m_fieldWidth(1500)
  , m_groundLevel(300)
  , m_minX(0)
  , m_maxX(0)
  , m_currentX(0)
  , m_velocity(4)
  , m_worldShift(0)
  , m_jumpHeight(180)
  , m_horizontalInput(0)
  , m_player(0)
  , m_sky(0)
  , m_trees(0)
  , m_grass(0)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_coins(0)
{
    initPlayField();

    m_timer.setInterval(30); // 지정만 하고, 플레이어가 키를 누를 때 시작한다.
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5,1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);
    /// 애니메이션 사용하기 위해서는 다음과 같은 설정이 필요하다.
    /// 0. PROPERTY 만들기
    ///      -  Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
    ///      -  string ".." 이름으로 속성에 접근할 수 있다.
    ///      -  알아서 Getter, Setter, Notify를 관리할 수 있다.
    ///      -  Animation의 setPropertyName으로 속성("jumpFactor")을 전달하면, 해당 속성이 애니메이션 동안 변경된다.
    ///      -  속성으로 전달한 "jumpFactor"가 일정 주기 동안 바뀌면서 jumpFactorChanged가 계속 콜백으로 호출된다.
    ///      -  jumpFactorChanged에서 캐릭터의 SetY를 해주면 Jump Animation이 된다!
    /// 1. QPropertyAnimation *m_jumpAnimation; // Animation 객체!~
    /// 2. Property 지정! _setPropertyName_ ( Animation으로 변화시킬 값을 의미한다. )
    /// 3. Property의 시작값, 끝값,
    /// 4. setKeyValueAt(..)으로 정해진주기의 N % 지났을 때의 시점의 값을 지정할 수 있다.
    ///      -> setKeyValueAt(0.5,1);는 Property로 전달한 값인
    ///         jumpFactor가 정해진 주기 800ms의 절반인 400ms시점에서의 값이 1이되어야 함을 의미한다.



}

void MyScene::initPlayField()
{
    setSceneRect(0,0,500,340);

    m_sky = new BackgroundItem(QPixmap(":/resources/sky.png"));
    addItem(m_sky);

    BackgroundItem *ground = new BackgroundItem(QPixmap(":/resources/ground.png"));
    ground->setPos(0,m_groundLevel);
    addItem(ground);

    m_trees = new BackgroundItem(QPixmap(":/resources/trees.png"));
    m_trees->setPos(0, m_groundLevel-m_trees->boundingRect().height());
    addItem(m_trees);

    m_grass = new BackgroundItem(QPixmap(":/resources/grass.png"));
    m_grass->setPos(0, m_groundLevel-m_grass->boundingRect().height());
    addItem(m_grass);

    m_player = new Player();
    m_minX = m_player->boundingRect().width() * 0.5;
    m_maxX = m_fieldWidth - m_player->boundingRect().width() * 0.5;
    m_player->setPos(m_minX, m_groundLevel - m_player->boundingRect().height()/2);
    m_currentX = m_minX;
    addItem(m_player);

    m_coins = new QGraphicsRectItem(0,0,m_fieldWidth, m_jumpHeight);
    m_coins->setPen(Qt::NoPen);
    m_coins->setPos(0, m_groundLevel - m_jumpHeight);
    const int xRange = (m_maxX - m_minX) * 0.94;
    for(int i = 0; i < 25 ; ++i){
        Coin *c = new Coin(m_coins);
        c->setPos(m_minX + qrand() % xRange, qrand() % m_jumpHeight);
    }
    addItem(m_coins);
}


void MyScene::movePlayer()
{
    // 일정거리 까지는 캐릭터만 움직이고 배경은 멈춰 있다가,
    // 그 다음부터는 캐릭터는 그대로있고 배경이 변경되면서 움직이는 효과를 준다.
    // -> m_currentX만 움직이고, m_worldShift는 그대로 이다.
    // -> 어느 시점 이후로는 m_currentX는 그대로이고, m_worldShift만 변경된다.

    const int direction = m_player->direction();
    if(0 == direction)
        return;

    const int dx = direction * m_velocity;
    qreal newX = qBound(m_minX, m_currentX + dx , m_maxX);
    // (m_currentX + dx) 값이 m_maxX보다 크면 m_maxX값을 리턴,
    // m_minX보다 작으면 m_minX값을 리턴한다. -> qBound.
    // m_minX~m_maxX의 거리는 전체 World에서 딱 캐릭터 이미지 width뺀 거리이다.

    if(newX == m_currentX)
        return;
    m_currentX = newX;
    // m_currentX는 Scene상의 X 위치가 아닌, World상의 X위치 이다.
    // Scene상의 위치로 바꿔줘야 한다.
    //   1. 처음에 움직일 때는 배경은 그대로, 캐릭터만 이동 (World 상의 X위치 & Scene상의 X위치 변경)
    //   2. 오른쪽으로 이동시 (맨오른쪽-150) X위치 부터는 World상의 X위치는 바뀌지만, Scene상의 X위치는 그대로
    //   --> 오른쪽 키보드 위치 눌리면 부조건 World상의 X는 ++,
    //       조건에 따라서 Scene상의 X 위치 조절해주는 offset요소가 필요!

    // 일정거리 움직이고나면 View가 바뀌어야 한다.
    // 코끼리와 Scene테두리 사이의 거리가 150미만일 때 뷰를 이동한다!
    //   1. m_worldShift는 배경이 움직인 거리를 저장한다.
    //   2. visiblePlayerPos는 Scene상에 코끼리가 위치한 X좌표!
    const int shiftBorder = 150;
    const int rightShiftBorder = width() - shiftBorder;
    const int visiblePlayerPos = m_currentX - m_worldShift;

    const int newWorldShiftLeft = shiftBorder - visiblePlayerPos;
    // [newWorldShiftLeft]
    //    - 테두리와 코끼리간 거리가 150px 미만이면 배경이 바뀐다.
    //    - visiblePlayerPos는 Scens상의 코끼리 위치를 나타낸다.
    //    - 150(shiftBorder) - VisiblePlayerPos 즉 150보다 가까워지면, newWorldShiftLeft가 (+)값을 가지게 된다!
    //    - newWorldShiftLeft가 양의 값이 되면, 배경을 바꿔 줘야 한다!. 코끼리도 더 이상 왼쪽으로 못오게 해야한다.
    //    - 배경이 움직인다.! ->>  m_worldShift -= newWorldShiftLeft;
    if(newWorldShiftLeft > 0){
        // 배경이 왼쪽으로 이동하는 순간이다.
        m_worldShift -= newWorldShiftLeft;
    }

    const int newWorldShiftRight = visiblePlayerPos - rightShiftBorder;
    if(newWorldShiftRight > 0){
        // 코끼리는 그대로, 배경이 바뀌는 순간이다! (오른쪽 이동효과)
        m_worldShift += newWorldShiftRight;
    }
    // [newWorldShiftRight]
    //    - 테두리와 코끼리간 거리가 150px 미만이면 배경이 바뀐다.
    //    - visiblePlayerPos는 Scene상의 코끼리 위치
    //    - rightShiftBorder는 오른쪽 테두리에서 150px를 뺀 값이다. 코끼리가 rightShiftBorder보다 가까워지면 ,
    ///      배경이 밀리면서 이동하는 코끼리가 이동하는 효과를 준다.
    //    - 배경이 바뀐다! (m_worldShift += newWorldShiftRight;)


    const int maxWorldShift = m_fieldWidth - qRound(width());
    m_worldShift = qBound(0,m_worldShift, maxWorldShift);
    //   m_worldShift가 0이상, maxWorldShift 이하임을 보장한다.


    qDebug()<< "Shift : " << m_worldShift ;
    qDebug()<< "X : " << m_currentX - m_worldShift ;
    qDebug()<< "newWorldShiftLeft : " << newWorldShiftLeft ;
    qDebug()<< "newWorldShiftRight : " << newWorldShiftRight ;
    m_player->setX(m_currentX - m_worldShift); //
    // m_currentX는 현재 코끼리의 위치 (World상의 코끼리가 이동한 위치)를 나타낸다.
    //  m_worldShift는 배경이 이동한 거리를 나타낸다.
    // 이 둘의 차이는 코끼리의 현재 Scene상의 위치를 나타낸다.

    // 배경움직이기.(가까운 배경은 빠르게, 먼 배경은 느리게 움직인다.)
    qreal ratio = qreal(m_worldShift)/ maxWorldShift;
    applyParallax(ratio, m_sky);
    applyParallax(ratio, m_grass);
    applyParallax(ratio, m_trees);

    //동전관련
    applyParallax(ratio, m_coins);
    checkColliding();
}

void MyScene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) // 누르고 있을때 들어오는 Input을 체크한다.
        return;

    // 꾹 누른경우에는 알아서 걸러진다.!
    switch (event->key()) {
        case Qt::Key_Right:
            addHorizontalInput(1);
            break;
        case Qt::Key_Left:
            addHorizontalInput(-1);
            break;

        case Qt::Key_Space:
            jump();
            break;
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;
    switch (event->key())
    {
        case Qt::Key_Right: {
            // 키보드 떼면 -1을 주어서 +1되었던 값을 다시 0으로 복귀시킨다.
            addHorizontalInput(-1);
            break;
        }
        case Qt::Key_Left: {
            addHorizontalInput(1);
            break;
        }
    }
}



void MyScene::checkTimer()
{
    if(m_player->direction() ==0)
        m_timer.stop();
    else if(!m_timer.isActive()){
        m_timer.start();
    }
}

void MyScene::checkColliding()
{
    // scene()->collidingItems(m_player)와 동일하다.
    // Scene내부의 GraphicsItem들과 m_player 간 충돌되었는지 확인한다.
    for(QGraphicsItem* item : collidingItems(m_player))
    {
        // m_player과 교차하는 item을 받고, 이것이 Coin 객체이면,
        // 충돌했다고 간주한다.
        // 배경이 밑으로 깔리기 때문에 대부분 배경들을 리턴할 것이다.
        //   그래서 BackgroundItem 클래스 shape()함수를 재정의 하였다.
        ///  return QPainterPath(); 해줬기 때문에, 빈 모양이 리턴된다.
        ///   충돌감지는 모양으로 하기때문에 빈 모양과는 충돌이 아예 불가능하다!
        if(Coin *c = qgraphicsitem_cast<Coin*>(item)){
            c->explode();
        }
    }
}

void MyScene::jump()
{
    if(QAbstractAnimation::Stopped == m_jumpAnimation->state()){
        m_jumpAnimation->start();
    }
}

void MyScene::addHorizontalInput(int input)
{
    m_horizontalInput += input;
    m_player->setDirection(qBound(-1, m_horizontalInput, 1));
    // qBound는 -1,1사이의 정수 값으로 리턴한다.
    checkTimer();
}

void MyScene::applyParallax(qreal ratio, QGraphicsItem *item)
{
    item->setX(-ratio*(item->boundingRect().width() - width()));
}

qreal MyScene::jumpFactor() const
{
    return m_jumpFactor;
}

void MyScene::setJumpFactor(qreal jumpFactor)
{
    //qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_jumpFactor, jumpFactor))
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);

    qreal groundY = (m_groundLevel - m_player->boundingRect().height()/2);
    qreal y = groundY - m_jumpAnimation->currentValue().toReal()*m_jumpHeight;
    m_player->setY(y);

    //
    checkColliding();
}













