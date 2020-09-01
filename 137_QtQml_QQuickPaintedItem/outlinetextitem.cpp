#include "outlinetextitem.h"
#include "outlinetextitemborder.h"
#include <QPainter>

OutlineTextItem::OutlineTextItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_border = new OutlineTextItemBorder(this);
    connect(this, &OutlineTextItem::textChanged, this, &OutlineTextItem::updateItem);
    connect(this, &OutlineTextItem::colorChanged, this, &OutlineTextItem::updateItem);
    connect(this, &OutlineTextItem::fontFamilyChanged, this, &OutlineTextItem::updateItem);
    connect(this, &OutlineTextItem::fontPixelSizeChanged, this, &OutlineTextItem::updateItem);
    connect(m_border, &OutlineTextItemBorder::widthChanged, this, &OutlineTextItem::updateItem);
    connect(m_border, &OutlineTextItemBorder::colorChanged, this, &OutlineTextItem::updateItem);
    connect(m_border, &OutlineTextItemBorder::styleChanged, this, &OutlineTextItem::updateItem);
    updateItem();
}

OutlineTextItemBorder *OutlineTextItem::border() const
{
    return m_border;
}

void OutlineTextItem::updateItem()
{
    /// 이 함수에서 쓰이는 m_fontFamily, m_fontPixelSize, m_text는
    /// 아래와 같이 QML객체 속성에 부여한 값과 동일하다.
    /// QML 엔진에서 속성을 변경하면 MEMBER m_text등으로 선언된 Q_PROPERTY와
    /// connect(..)로 연결된 SIGNAL-SLOT으로 인해 updateItem이 호출되고,
    /// 변경된 값을 바로 받아서 GUI업데이트를 수행한다!
    ///
    ///   OutlineTextItem{
    ///       anchors.centerIn: parent
    ///       text : "This is outliend text"
    ///       fontFamily: "Arial"
    ///       fontPixelSize: 64
    ///       ...
    ///   }
    ///
    QFont font(m_fontFamily, m_fontPixelSize);
    m_path = QPainterPath();
    // QString 텍스트로 Path를 만들 수 있다!! (QPainterPathStroker..)
    m_path.addText(0,0, font, m_text);
    m_boundingRect = borderShape(m_path).controlPointRect();
    setImplicitWidth(m_boundingRect.width());
    setImplicitHeight(m_boundingRect.height());
    update();
}

void OutlineTextItem::paint(QPainter *painter)
{
    if(m_text.isEmpty())
        return;

    // paint(..)는 updateItem()에서 호출한 update(..)에 의해 콜백된다.
    // m_border->pen()은 아래의 QML 객체에 설정한 속성값중 border.color 등으로 설정한
    //  m_color, m_width, m_style에 의해서 QPen OutlineTextItemBorder::pen() 이 리턴될 때
    // QPen의 속성으로 설정된다.

        //    OutlineTextItem{
        //        ...
        //        border.color: "blue"
        //        border.width: 2
        //        border.style: Qt.DotLine
        //    }
    //    QPen OutlineTextItemBorder::pen() const
    //    {
    //        QPen p;
    //        p.setColor(m_color);
    //        p.setWidth(m_width);
    //        p.setStyle(m_style);
    //        return p;
    //    }
    painter->setPen(m_border->pen());
    painter->setBrush(m_color);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(-m_boundingRect.topLeft());
    painter->drawPath(m_path);
}

QPainterPath OutlineTextItem::borderShape(const QPainterPath &path) const
{
    QPainterPathStroker pathStroker;
    pathStroker.setWidth(m_border->width());
    QPainterPath p = pathStroker.createStroke(path);
    p.addPath(path);
    return  p;
}















