#ifndef _GL_WIDGET_
#define _GL_WIDGET_

#include "hatfat/glee/GLee.h"
#include <QGLWidget>

#include "Matrix.h"

class Noise;
class Planet;
class SimpleMeshData;

enum MODE { SHADER, NOISE_TEST };
enum SHAPE { SPHERE, TEAPOT, CONE, CUBE, DODECAHEDRON, ICOSAHEDRON, OCTAHEDRON, TETRAHEDRON, TORUS, LAST_SHAPE };

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit        GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void            refresh();

protected:
    void            paintGL();
    void            resizeGL(int, int);

    void            keyPressEvent(QKeyEvent *);

private:
    void            createRandomNoise();
    void            drawNoise();
    void            drawScene();
    void            drawText();
    GLint           getUniformLoc(GLuint program, const GLchar *name);
    void            initialize();
    void            initializeNoise();
    void            initializeGL();
    void            keyboardStandardDown(unsigned char key, int x, int y);
    void            loopFunction();
    void            mouseMotion(int x, int y);
    void            mouseMove(int button, int state, int x, int y);
    void            nextShape();
    void            prevShape();
    void            render();

    Matrix          rotation;

    Noise           *pTestNoise;
    SimpleMeshData  *pTestData;
    Planet          *pPlanet;

    float           fTime;
    bool            bUpdate;

    int             TEXT_CHAR_LENGTH;
    char            *pText;
    SHAPE           currentShape;
    MODE            currentMode;

    int             MOUSE_X;
    int             MOUSE_Y;
    bool            bFullscreen;
    bool            bPaused;
    GLint           varLoc;

    float           PLANET_RADIUS;
    float           MAX_CAMERA_DISTANCE;
    float           MIN_CAMERA_DISTANCE;
    float           g_fCameraDistance;

signals:

public slots:

};

#endif // GLWIDGET_H
