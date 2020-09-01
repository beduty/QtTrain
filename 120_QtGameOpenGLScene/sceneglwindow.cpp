#include "sceneglwindow.h"
#include "abstractglscene.h"

SceneGLWindow::SceneGLWindow(QWindow *parent)
    : QOpenGLWindow(NoPartialUpdate, parent)
{

}

void SceneGLWindow::initializeGL()
{
    if(m_scene)
        m_scene->initialize();
}

void SceneGLWindow::paintGL()
{
    if(m_scene)
        m_scene->paint();
}
