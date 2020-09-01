#include "regularpolygon.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

RegularPolygon::RegularPolygon()
{
    setFlag(ItemHasContents, true); // updatePaintNode(..)를 쓰기 위해서 필요하다
    m_vertexCount = 6;
}

int RegularPolygon::vertices() const
{
    return m_vertexCount;
}

QColor RegularPolygon::color() const
{
    return m_color;
}

void RegularPolygon::setVertives(int vertices)
{
    vertices = qMax(3,vertices);
    if (m_vertexCount == vertices)
        return;

    m_vertexCount = vertices;
    emit verticesChanged(m_vertexCount);
    update();
}

void RegularPolygon::setColor(QColor color)
{
    if (m_color == color)
        return;
    m_color = color;
    emit colorChanged(m_color);
    update();
}

QSGNode *RegularPolygon::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    // 이전 호출 중에 반환 된 노드를 받을 수 있다.

    QSGGeometryNode *node = nullptr;
    QSGGeometry *geometry = nullptr;

    if(!oldNode){
        node = new QSGGeometryNode;

        // 정점데이터 구조를 정의한다.
        geometry = new QSGGeometry(
                    QSGGeometry::defaultAttributes_Point2D(), m_vertexCount +2);
        geometry->setDrawingMode(GL_TRIANGLE_FAN);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        // 재질을 정의한다.
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(m_color);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }else{
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_vertexCount +2);
    }

    QSGMaterial *material = node->material();
    QSGFlatColorMaterial* flatMaterial = static_cast<QSGFlatColorMaterial*>(material);
    if(flatMaterial->color() != m_color){
        flatMaterial->setColor(m_color);
        node->markDirty(QSGNode::DirtyMaterial);
    }

    QRectF bounds = boundingRect();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    QPointF center = bounds.center();
    vertices[0].set(center.x(), center.y());
    qreal angleStep = 360.0 / m_vertexCount;
    qreal radius = qMin(width(), height()) /2;
    for(int i = 0; i < m_vertexCount; ++i)
    {
        qreal rads = angleStep * i * 3.141592 / 180.0;
        qreal x = center.x() + radius * std::cos(rads);
        qreal y = center.y() + radius * std::sin(rads);
        vertices[i +1].set(x,y);
    }
    vertices[m_vertexCount + 1] = vertices[1];
    node->markDirty(QSGNode::DirtyGeometry);
    return node;
}




















