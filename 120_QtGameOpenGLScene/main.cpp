#include <QApplication>
#include <QPropertyAnimation>
#include "sceneglwindow.h"
#include "cubeglscene.h"

/// 창코드와 렌더링코드를 분리한다!
/// QOpenGLWindow 클래스를 상속받아 Qt창을 만든다.
///     --> initializeGL() 과 paintGL() 에서 Scene을 만들고 그린다.
/// 렌더링 코드는 AbstractGLScene을 상속받아서 내용을 그린다.
///     --> QOpenGLFunctions_1_1을 상속받아서 AbstractGLScene을 만든다.
///     --> 새로 렌더링할때는 AbstractGLScene을 상속 받아서 아래 부분을 재정의 한다.
///         - initialize() : initializeOpenGLFunctions()를 호출하고, 배경색상을 만든다.
///         - paint() : 배경 위에 객체를 그린다.

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 1. 창을 만들고, Anit얼라이싱 설정한다.
    SceneGLWindow window;
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    window.setFormat(fmt);

    // 2. 렌더링(Scene) 객체를 만든다.
    CubeGLScene scene(&window);
    window.setScene(&scene);
    // 여기서 받은 Scene을 가상함수
    //   - initializeGL()  에서 m_scene->ininitialize();
    //   - paintGL()  에서 m_scene->paint(); 한다!
    scene.setTexture(QImage(":/texture.jpg"));
    window.resize(600,400);
    window.show();

    // 3. 애니메이션을 수행한다. (angle)
    /// QPropertyAnimation 쓰기 위해서는 Q_PROPERTY가 설정되어야 한다.
    /// scene안의 'angle' Property 의 값의 애니메이션을 수행한다.
    QPropertyAnimation animation(&scene, "angle");
    animation.setStartValue(0);
    animation.setEndValue(359);
    animation.setDuration(5000);
    animation.setLoopCount(-1);
    animation.start();

    return a.exec();
}
