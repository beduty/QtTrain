#ifndef REGULARPOLYGON_H
#define REGULARPOLYGON_H

#include <QQuickItem>

// QML의 모든 객체들은 QQuickItem을 상속받았다. Item{}
// -> x,y,width,height, anchors등을 처리한다.
// QQuickItem을 상속받아서 Custom으로 만들 수 있다.
// -> 장점은 OpenGL을 사용하기 때문에 속도가 빠르다!
// --> 하지만, OpenGL에 숙련도가 있어야 된다. 복잡한 객체를 그리기가 너무 어렵다!!! (노드계싼이 어렵다!)
// --> QPainter를 사용하자!!! !QPainter는 memory buffer에 painter로 그리고,
//     OpenGL 텍스쳐로 변화하여 렌더링하므로 조금 느리긴하나, 훨씬 다양하고, 쉬운 그리기가 가능하다!

// QSGGeometryNodes는 화면상에 그려지는 아이템 실체이다.
// ->  Geometry(메시, 정점, 구조), Material(모양이 채워지는 방식)
// QSGNode는 베이스 클래스이다.
class RegularPolygon : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int vertices READ vertices WRITE setVertives NOTIFY verticesChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    RegularPolygon();    
    int vertices() const;
    QColor color() const;

    // Item을 그리는 메소드이다.
    QSGNode * updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;

public slots:
    void setVertives(int vertices);
    void setColor(QColor color);

signals:
    void verticesChanged(int vertices);
    void colorChanged(QColor color);

private:
    int m_vertexCount;
    QColor m_color;
};

#endif // REGULARPOLYGON_H
