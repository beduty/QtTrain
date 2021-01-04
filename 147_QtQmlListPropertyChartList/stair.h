#ifndef STAIR_H
#define STAIR_H

#include <QObject>
#include <QColor>

// ChartItem 하나의 정보를 담는다.
// 1. Bar 색상
// 2. Bar의 값.(Y길이)
// 3. X 위치
// 4. Bar 이름.
// -> 모델의 데이터 하나를 의미한다.(느낌)
class Stair : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit Stair(QObject *parent = nullptr);
    QColor color() const;
    int value() const;
    int from() const;
    QString text() const;

public slots:
    void setColor(QColor color);
    void setValue(int value);
    void setFrom(int from);
    void setText(QString text);

signals:
    void colorChanged(QColor color);
    void valueChanged(int value);
    void fromChanged(int from);
    void textChanged(QString text);

private:
    QColor m_color;
    int m_value;
    int m_from;
    QString m_text;
};

#endif // STAIR_H
