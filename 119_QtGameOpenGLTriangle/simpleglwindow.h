#ifndef SIMPLEGLWINDOW_H
#define SIMPLEGLWINDOW_H

/// OpenGL 렌더링 하는 방법이 많지만, Qt에서 쓸 수 있는 가장 쉬운 방법은
/// QOpenGLWindow 클래스를 SubClassing 해서 사용한다.
/// 여기서 initializeGL()과 paintGL(), resizeGL()등을 재정의 해서 사용한다.
///     1. initializeGL() : 컨텍스트를 초기화하거나 리소스를 준비한다.
///     2. paintGL() : 위젯클래스의 paintEvent()와 동일하다. Repaint될때마다 실행된다.
///     3. resizeGL() : 창크기가 조정될 때 마다 호출된다.
///  --> 위와 같은 가상 함수를 호출하기 전에 OpenGL 컨텍스트가 최신 상태인지 확인하므로,
///      수동으로 makeCurrent() 호출할 필요 없다.
///
/// 기본적으로 Qt가 크로스플랫폼이므로, 플랫폼별로 제대로 동작하지 않을 수 있다.
/// 이때문에 QOpenGLFuntions를 제공한다. QOpenGLWindow 상속받을 때, QOpenGLFuncions도
/// 같이 다중 상속 해주면 된다! glClearColor()를 쓰면,
/// openGL라이브러리의 glClearColor() 쓰는게 아닌, QOpenGLFuntions::glClearColor()사용한다.
///

#include <QOpenGLWindow>
#include <QOpenGLFunctions_1_1>
class SimpleGLWindow : public QOpenGLWindow, protected QOpenGLFunctions_1_1
{
public:
    SimpleGLWindow(QWindow *parent = 0);
protected:
    void initializeGL() override;
    void paintGL() override;

private:
    void paintTriangle();
};

#endif // SIMPLEGLWINDOW_H
