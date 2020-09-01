#ifndef CUBEGLSCENE_H
#define CUBEGLSCENE_H
#include <QImage>
#include <QObject>
#include <QVector2D>
#include <QVector3D>
#include "abstractglscene.h"

/// 렌더링 코드를 작성한다.
/// QPropertyAnimation을 쓰기 위해서는 Q_PROPERTY 가 설정되어야 해서 QObject도 상속받았다.
///

class QOpenGLTexture;
class SceneGLWindow;
class CubeGLScene : public QObject, public AbstractGLScene
{
    Q_OBJECT
    Q_PROPERTY(float angle READ angle WRITE setAngle)
public:
    CubeGLScene(SceneGLWindow* window);
    ~CubeGLScene();

    float angle() const;
    void paint() override;  /// Scene을 그린다.
    void initialize() override; /// QOpenGLFunctions 초기화 한다.
    void setTexture(const QImage &image); /// 텍스쳐 이미지와 텍스쳐를 초기화한다.

public slots:
    void setAngle(float angle);

protected:
    void initializeTexture(); /// 텍스쳐 초기화 한다.
    void initializeCubeData(); /// 큐브데이터 초기화 한다.
    void paintCube();  /// 렌더링(큐브와 큐브면의 텍스쳐)을 입힌다.

private:
    QImage m_textureImage;
    QOpenGLTexture* m_texture = nullptr;
    bool m_initialized = false;

    struct TexturedPoint{
        QVector3D coord;
        QVector2D uv;
        TexturedPoint(const QVector3D& pcoord = QVector3D(),
                      const QVector2D& puv = QVector2D()):
            coord(pcoord), uv(puv){}
    };
    QVector<TexturedPoint> m_data;
    float m_angle;
};



#endif // CUBEGLSCENE_H
