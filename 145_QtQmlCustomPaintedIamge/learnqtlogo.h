#ifndef LEARNQTLOGO_H
#define LEARNQTLOGO_H

#include <QObject>
#include <QImage>
#include <QQuickPaintedItem>

class LearnQtLogo : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QtTopic topic READ topic WRITE setTopic NOTIFY topicChanged)
public:
    explicit LearnQtLogo(QQuickItem *parent = nullptr);
    enum QtTopic{
        QTCPP,
        QTQUICK
    };
    Q_ENUM(QtTopic)
    // QtTopic은 사용자정의 객체이고, Q_PROPERTY를 썼기때문에 qmlRegisterUncreatableType<QtTopic> 해줘야하나,
    // enum변수에 한하여 Q_ENUM으로 정의해주면 QML에서 알아들을 수 있기때문에 qmlRegisterUncreatableType 안써줘도 된다.

signals:
    void bgColorChanged(QColor bgColor);
    void textColorChanged(QColor textColor);
    void textChanged(QString text);
    void topicChanged(QtTopic topic);

public:
// QQuickPaintedItem interface
    void paint(QPainter *painter);

    QColor bgColor() const;
    QColor textColor() const;
    QString text() const;
    QtTopic topic() const;

public slots:
    void setBgColor(QColor bgColor);
    void setTextColor(QColor textColor);
    void setText(QString text);
    void setTopic(QtTopic topic);

private:
    QColor m_bgColor;
    QColor m_textColor;
    QString m_text;
    QtTopic m_topic;
};

#endif // LEARNQTLOGO_H
