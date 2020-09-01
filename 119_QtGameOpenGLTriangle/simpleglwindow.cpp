#include "simpleglwindow.h"

SimpleGLWindow::SimpleGLWindow(QWindow *parent):
    QOpenGLWindow(NoPartialUpdate, parent)
{
    QSurfaceFormat fmt = format();
    fmt.setSamples(16); /// 멀티샘플링을 활성화하면 Anti 앨리어싱처럼 동작한다.
    setFormat(fmt);
}

void SimpleGLWindow::initializeGL()
{
    // QOpenGLFunctions을 초기화한다!
    if(!initializeOpenGLFunctions()){
        qFatal("initializeOpenFuntions failed");
    }
    glClearColor(0.8,0.8,0.8,0);
}

void SimpleGLWindow::paintGL()
{
    paintTriangle();
}

void SimpleGLWindow::paintTriangle()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,width(), height());
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1,0,0);
        glVertex3f(0.0f,1.0f,0.0f);
        glColor3f(0,1,0);
        glVertex3f(1.0f,-1.0f,0.0f);
        glColor3f(0,0,1);
        glVertex3f(-1.0f,-1.0f,0.0f);
    }
    glEnd();
}
