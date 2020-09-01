#ifndef VIEW_H
#define VIEW_H
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);
    ~View();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // VIEW_H
