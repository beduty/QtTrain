#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

/// QPainter는 모든 그리는 작업을 총괄한다. (내부적으로는 Qt에서 디바이스에 맞게 동작한다.)
/// 주요 속성은 펜(아웃라인), 브러시(Fill), 폰트(text)
/// QPainter 좌표계는 장치(Device), Window, World(Logical) 좌표계가 있다.
/// World->Window 좌표계로 변환행렬을 사용한다.(QTransform)
/// Window->Device좌표계로 뷰포트, 윈도우 사각형을 사용한다.
///
/// 기본 좌표 시스템은 좌측 상단이 (0,0)이 되는 무한데카르트 캔버스.
/// --> 변환행렬은 단위 행렬. (X,Y 그래프 그릴때는 (1,-1)로 스케일링하면 세로축의 방향을 반전시킨다. (QTransform))
/// --> 윈도우 사각형은 App의 크기(영역)이다.
/// --> View포트 사각형은 App의 크기이다.
///
/// 윈도우 사각형을 새로 설정하면 설정한 사각형의 좌측 상단이 0,0이된다.
/// 뷰포트 사각형을 새로 설정하면 해당 영역만 그릴 수 있게 된다. 즉 캔버스이다!

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    Q_PROPERTY(int selectionStart READ selectionStart NOTIFY selectionChanged)
    Q_PROPERTY(int selectionEnd READ selectionEnd NOTIFY selectionChanged)

    int selectionStart() const;
    int selectionEnd() const;

public slots:
    void addPoint(unsigned yVal);
    void clear();

signals:
    void selectionChanged();

protected:
    // QWidget interface
    void paintEvent(QPaintEvent *event);
    void drawChart(QPainter *painter, const QRect &rect, const QRect &exposedRect);
    void drawselection(QPainter *painter, const QRect &rect, const QRect &exposedRect);

private:
    QVector<quint16> m_points;
    int m_selectionStart;
    int m_selectionEnd;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};


#endif // WIDGET_H
