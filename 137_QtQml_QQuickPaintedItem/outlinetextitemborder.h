#ifndef OUTLINETEXTITEMBORDER_H
#define OUTLINETEXTITEMBORDER_H

#include <QObject>
#include <QColor>

class OutlineTextItemBorder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width MEMBER m_width NOTIFY widthChanged)
    Q_PROPERTY(QColor color READ color MEMBER m_color NOTIFY colorChanged)
    Q_PROPERTY(Qt::PenStyle style  READ style  MEMBER m_style NOTIFY styleChanged)

public:
    explicit OutlineTextItemBorder(QObject *parent = nullptr);
    int width() const;
    QColor color() const;
    Qt::PenStyle style() const;
    QPen pen() const;

signals:
    void widthChanged(int width);
    void colorChanged(QColor color);
    void styleChanged(Qt::PenStyle style);

private:
    int m_width;
    QColor m_color;
    Qt::PenStyle m_style;
};

#endif // OUTLINETEXTITEMBORDER_H
