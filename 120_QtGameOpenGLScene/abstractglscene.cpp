#include "abstractglscene.h"
#include <QOpenGLWindow>

AbstractGLScene::AbstractGLScene(QOpenGLWindow *window)
{
    m_window = window;
}

AbstractGLScene::~AbstractGLScene()
{

}

QOpenGLContext *AbstractGLScene::context()
{
    return m_window ? m_window->context() : nullptr;
}

const QOpenGLContext *AbstractGLScene::context() const
{
    return m_window ? m_window->context() : nullptr;
}

void AbstractGLScene::initialize()
{
    /// QOpenGLFunctions_1_1을 초기화 해줘야 한다!
    /// 플랫폼 독립적일 수 있도록 Qt에서 만든 Wrapper이다.
    if(!initializeOpenGLFunctions())
        qFatal("initializeOpenGLFunctions failed");
}
