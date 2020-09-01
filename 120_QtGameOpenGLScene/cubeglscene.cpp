#include "cubeglscene.h"
#include "sceneglwindow.h"
#include <QOpenGLTexture>
#include <QOpenGLWindow>

CubeGLScene::CubeGLScene(SceneGLWindow *window)
    :AbstractGLScene(window)
{
    m_angle = 0;
    initializeCubeData();
}

CubeGLScene::~CubeGLScene()
{
    if(window())
        window()->makeCurrent();
    delete m_texture;
}

void CubeGLScene::initialize()
{
    AbstractGLScene::initialize();
    m_initialized = true;
    if(! m_textureImage.isNull())
        initializeTexture();

    glClearColor(1,1,1,0);
    glShadeModel(GL_SMOOTH);
}

void CubeGLScene::paint()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,window()->width(), window()->height());
    glLoadIdentity();

    glRotatef(45, 1.0,0.0,0.0);
    glRotatef(m_angle, 0.0,1.0,0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    paintCube();
}

void CubeGLScene::setTexture(const QImage &image)
{
    m_textureImage = image;
    if(m_initialized){
        initializeTexture();
    }
}

float CubeGLScene::angle() const
{
    return m_angle;
}

void CubeGLScene::setAngle(float angle)
{
    /// angle이 QPropertyAnimation에서 매번바뀌는데,
    /// 이때마다 setAngle이 호출되고, 여기서 update()로 화면 갱신된다.
    m_angle = angle;
    window()->update();
}

void CubeGLScene::initializeTexture()
{
    /// 텍스쳐 데이터를 초기화 한다.
    m_texture = new QOpenGLTexture(m_textureImage.mirrored()); // 텍스쳐 꺼꾸로 되는것 방지
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void CubeGLScene::initializeCubeData()
{
    /// 화면의 중점이 (0,0,0)이다. 공간은 (-1,-1,-1) ~ (1,1,1)의 범위를 가진다.
    /// --> 플레밍의 왼손법칙을 참조하라
    ///       - X는 중지방향이 + , 오른쪽으로 갈수록 커진다.
    ///       - Y는 엄지방향이 +, 위로 갈수록 (+) , 아래로 갈수록 (-) 가된다.
    ///       - Z는 검지방향이 +, 배꼽방향으로 갈수록 (+)이다.
    ///     반시계방향으로 Vector3D 지정한다.
    ///
    /// glTexCoord2d의 텍스쳐매핑은 다음과 같이 수행된다.
    ///  --> 텍스쳐도 역시 반시계방향으로 Vector2D 지정한다.(0,0)->(1,0)->(1,1)->(0,1)

    m_data = {
        // FRONT FACE
        /// 반시계방향으로 Vector3D 지정한다.
        /// 텍스쳐도 역시 반시계방향으로 Vector2D 지정한다.(0,0)->(1,0)->(1,1)->(0,1)
        {{-0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5,  0.5}, {0, 1}},

        // TOP FACE
        {{-0.5,  0.5,  0.5}, {0, 0}},        {{ 0.5,  0.5,  0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        // BACK FACE
        {{-0.5,  0.5, -0.5}, {0, 0}},        {{ 0.5,  0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5, -0.5}, {1, 1}},        {{-0.5, -0.5, -0.5}, {0, 1}},

         // BOTTOM FACE
        {{-0.5, -0.5, -0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5, -0.5,  0.5}, {1, 1}},        {{-0.5, -0.5,  0.5}, {0, 1}},

        // LEFT FACE
        {{-0.5, -0.5, -0.5}, {0, 0}},        {{-0.5, -0.5,  0.5}, {1, 0}},
        {{-0.5,  0.5,  0.5}, {1, 1}},        {{-0.5,  0.5, -0.5}, {0, 1}},

        // RIGHT FACE
        {{ 0.5, -0.5,  0.5}, {0, 0}},        {{ 0.5, -0.5, -0.5}, {1, 0}},
        {{ 0.5,  0.5, -0.5}, {1, 1}},        {{ 0.5,  0.5,  0.5}, {0, 1}},
    };

}

void CubeGLScene::paintCube()
{
    if(m_texture)
        m_texture->bind();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    for(const TexturedPoint &point : m_data){
        glTexCoord2d(point.uv.x(), point.uv.y());
        glVertex3f(point.coord.x(), point.coord.y(), point.coord.z());
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}














