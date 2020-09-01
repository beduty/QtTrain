#ifndef OUTLINETEXTITEM_H
#define OUTLINETEXTITEM_H
#include <QQuickPaintedItem>
#include <QPainterPath>

/// QQuickItem은 사용하기 되게 어렵다!!!
/// OpenGL을 바로 사용하기 때문에 가장 빠르지만, 복잡한 객체를 그리기가 되게 어렵다.
/// Node의 Geometry와 Material을 직접 하나하나 계산해서 그리기가 되게 힘들다!
///
/// QPainter로 MemoryBuffer에 그리고, OpenGL 텍스쳐로 변환하여 장면에 렌더링하는 방식을 더 추천!!!
/// QQuickItem에 비해서 성능저하가 있지만, 쉽고, 풍부하게 항목을 그리는 것이 더 간단하다!
/// --> QQuickPainterdItem을 상속받아서 paint로 구현하면 쉽게 사용가능하다!

/* 아래와 같이 사용가능하다.  MEMBER m_text로 쓰므로, QML 객체의 속성으로 동작한다.
 * 아래와 같이 등록한 QML객체를 어떻게 그릴까?!
 * 또한 객체 속성이 바뀌면 Reactive하게 어떻게 객체의 상태(크기, Text, font, 색상)를 바꿔줄까?!
 *
    OutlineTextItem{
        anchors.centerIn: parent
        text : "This is outliend text"
        fontFamily: "Arial"
        fontPixelSize: 64
        color: "#33ff0000"
        antialiasing: true
        border.color: "blue"
        border.width: 2
        border.style: Qt.DotLine
    }
 * QQuickPaintedItem::paint(..) 에서 QML 객체를 그려준다!
 * connect로 SIGNAL - SLOT 연결을 통해서 속성 바뀌었을 때, 처리해준다. (updateItem)
*/

class OutlineTextItemBorder;
class OutlineTextItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int fontPixelSize MEMBER m_fontPixelSize NOTIFY fontPixelSizeChanged)
    Q_PROPERTY(QColor color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged)
    Q_PROPERTY(QString fontFamily MEMBER m_fontFamily NOTIFY fontFamilyChanged)
    Q_PROPERTY(OutlineTextItemBorder *border READ border NOTIFY borderChanged)

public:
    OutlineTextItem(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    OutlineTextItemBorder * border() const;
    QPainterPath borderShape(const QPainterPath &path) const;

private slots:
    void updateItem();

signals:
    void textChanged(QString text);
    void colorChanged(QColor color);
    void borderChanged();
    void fontFamilyChanged(QString fontFamily);
    void fontPixelSizeChanged(int fontPixelSize);

private:
    OutlineTextItemBorder * m_border;
    QPainterPath m_path;
    QRectF m_boundingRect;
    QString m_text;
    QColor m_color;
    QString m_fontFamily;
    int m_fontPixelSize;
};

#endif // OUTLINETEXTITEM_H
