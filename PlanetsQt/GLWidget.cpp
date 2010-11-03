#include "GLWidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QIcon>
#include <QKeyEvent>

#include "Noise.h"
#include "PlanetProgramOne.h"
#include "ShaderManager.h"
#include "SimpleMeshData.h"

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;

GLWidget::GLWidget(QWidget *parent) :
        QGLWidget(parent)
{
    int desktopWidth    = QApplication::desktop()->width();
    int desktopHeight   = QApplication::desktop()->height();
    int size = min(desktopWidth, desktopHeight);

    move(size / 50, size / 50);
    resize(size * 3 / 4, size * 3 / 4);

    setWindowIcon(QIcon(":/planets/resources/icon.xpm"));

    initialize();
}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    printf("OpenGL Version %s\n%s\n%s\nShader Version %s\n\n", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_SHADING_LANGUAGE_VERSION));

    //start by initializing the shader manager
    ShaderManager::get();
    ShaderManager::get().GetPlanetProgram()->SetPlanet(pPlanet);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void GLWidget::keyPressEvent(QKeyEvent *pKeyEvent)
{
//    cout << "key=" << pKeyEvent->key() << endl;

    switch (pKeyEvent->key())
    {
    case '1':
        currentMode = SHADER;
        break;

    case '2':
        currentMode = NOISE_TEST;
        break;

    case 'm':
        rotation.Dump();
        break;

    case 112: // 'p' and 'P'
    case 80:
        bPaused = !bPaused;
        break;

    case 45: // -
    case 95: // _
        g_fCameraDistance = 1.03f * g_fCameraDistance;
        g_fCameraDistance = min(g_fCameraDistance, MAX_CAMERA_DISTANCE);
        break;

    case 61: // =
    case 43: // +
        g_fCameraDistance = 0.98f * g_fCameraDistance;
        g_fCameraDistance = max(g_fCameraDistance, MIN_CAMERA_DISTANCE);
        break;

    case 3: //CTRL + c
    case 27: //esc
        exit(1);
        break;

    case 46: // '>' and '.'
    case 62:
        ShaderManager::get().NextProgram();
        break;

    case 44: // '<' and ",'
    case 60:
        ShaderManager::get().PrevProgram();
        break;

    case 91: // '[' and '{'
    case 123:
        prevShape();
        break;

    case 93: // ']' and '}'
    case 125:
        nextShape();
        break;

    case 32: //spacebar
        createRandomNoise();
        pPlanet->Randomize();
        break;

    case 117: // 'u' and 'U'
    case 85:
        bUpdate = !bUpdate;
        break;

    default:

        break;
    }
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)width() / (float)height(), 0.1, 100.0); //update this so we dont get crappy distortion
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glPushMatrix();

    switch (currentMode)
    {
    case SHADER:
        drawScene();
        drawText();
        break;

    case NOISE_TEST:
        drawNoise();
        break;

    }

    //TODO
    //   glutSwapBuffers();
}

void GLWidget::refresh()
{

}

void GLWidget::resizeGL(int width, int height)
{
    cout << "resizeGL (" << width << ", " << height << ")" << endl;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / (float)height, 0.1, 100.0); //update this so we dont get crappy distortion
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::createRandomNoise()
{
    fTime = 0.0f;

    if (pTestNoise)
    {
        delete pTestNoise;
    }

    if (pTestData)
    {
        delete pTestData;
    }

    pTestNoise = new Noise(rand());
    pTestData = new SimpleMeshData(pTestNoise);
}

void GLWidget::drawNoise()
{
    glPushMatrix();

    gluLookAt(0.0, 0.0, g_fCameraDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMultMatrixf(rotation.m);

    glLineWidth(1.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glVertexPointer(3, GL_FLOAT, 0, pTestData->getVertices());
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, pTestData->getColors());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_LINES, pTestData->getNumberOfIndices(), GL_UNSIGNED_INT, pTestData->getIndices());
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glLineWidth(4.0f);

    glBegin(GL_LINES);
    glColor4f(0.7f, 0.0f, 0.0f, 1.0f);
    glVertex3f(-20.0f, 0.0f, 0.0f);
    glVertex3f(20.0f, 0.0f, 0.0f);
    glColor4f(0.0f, 0.0f, 0.7f, 1.0f);
    glVertex3f(0.0f, 20.0f, 0.0f);
    glVertex3f(0.0f, -20.0f, 0.0f);
    glColor4f(0.0f, 0.7f, 0.0f, 1.0f);

    //draw x hash marks
    for (int i = -20; i <= 20; ++i)
    {
        glVertex3f((float) i, 0.25f, 0.0f);
        glVertex3f((float) i, -0.25f, 0.0f);
    }

    //draw y hash marks
    for (int i = -20; i <= 20; ++i)
    {
        glVertex3f(0.25f, (float) i, 0.0f);
        glVertex3f(-0.25f, (float) i, 0.0f);
    }

    glEnd();

    glPopMatrix();
}

void GLWidget::drawScene()
{
    glPushMatrix();
    gluLookAt(0.0, 0.0, g_fCameraDistance, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMultMatrixf(rotation.m);

    ShaderManager::get().GetActiveProgram()->Activate();

    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glEnd();

    switch (currentShape)
    {
    case CONE:
        //glutSolidCone(PLANET_RADIUS / 3.0, PLANET_RADIUS, 45, 45);
        break;

    case CUBE:
        //glutSolidCube(PLANET_RADIUS);
        break;

    case DODECAHEDRON:
        //glutSolidDodecahedron();
        break;

    case ICOSAHEDRON:
        //glutSolidIcosahedron();
        break;

    case OCTAHEDRON:
        //glutSolidOctahedron();
        break;

    case SPHERE:
        //glutSolidSphere(PLANET_RADIUS, 45, 45);
        break;

    case TEAPOT:
        //glutSolidTeapot(PLANET_RADIUS);
        break;

    case TETRAHEDRON:
        //glutSolidTetrahedron();
        break;

    case TORUS:
        //glutSolidTorus(PLANET_RADIUS / 2.0, PLANET_RADIUS, 45, 45);
        break;

    default:
        //       assert(0 && "invalid current shape!");
        break;
    }

    glUseProgram(0);

    glPopMatrix();
}

void GLWidget::drawText()
{
//    glPushMatrix();
//    gluLookAt(0.0, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

//    glDisable(GL_DEPTH_TEST);

//    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

//    //draw program name
//    memset(pText, 0, TEXT_CHAR_LENGTH);
//    sprintf(pText, "%s%s", "Shader             ", ShaderManager::get().GetActiveProgram()->GetProgramName());
//    glRasterPos2f(-1.0f, -0.99f);
//    for (const char *c = pText; *c != '\0'; c++)
//    {
//        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//    }

//    memset(pText, 0, TEXT_CHAR_LENGTH);
//    sprintf(pText, "%s%f", "Planet Radius      ", pPlanet->GetPlanetRadius());
//    glRasterPos2f(-1.0f, -0.90f);
//    for (const char *c = pText; *c != '\0'; c++)
//    {
//        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//    }

//    memset(pText, 0, TEXT_CHAR_LENGTH);
//    sprintf(pText, "%s%f", "Archepeggiation    ", pPlanet->GetArchepeggiation());
//    glRasterPos2f(-1.0f, -0.85f);
//    for (const char *c = pText; *c != '\0'; c++)
//    {
//        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//    }

//    memset(pText, 0, TEXT_CHAR_LENGTH);
//    sprintf(pText, "%s%d", "Planet Seed        ", pPlanet->GetPlanetSeed());
//    glRasterPos2f(-1.0f, -0.80f);
//    for (const char *c = pText; *c != '\0'; c++)
//    {
//        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
//    }

//    glEnable(GL_DEPTH_TEST);

//    glPopMatrix();
}

void GLWidget::initialize()
{
    pTestNoise      = 0;
    pTestData       = 0;

    initializeNoise();

    pPlanet = new Planet();
    pPlanet->Randomize();

    fTime = 0.0f;
    bUpdate = false;

    TEXT_CHAR_LENGTH    = 42;
    pText               = new char[50];
    currentShape        = SPHERE;
    currentMode         = NOISE_TEST;//SHADER;
    MOUSE_X             = -1;
    MOUSE_Y             = -1;
    bFullscreen         = false;
    bPaused             = false;
    varLoc              = -1;

    PLANET_RADIUS       = 1.0f;
    MAX_CAMERA_DISTANCE = PLANET_RADIUS * 20.0f;
    MIN_CAMERA_DISTANCE = PLANET_RADIUS * 1.1f;
    g_fCameraDistance   = PLANET_RADIUS * 2.5f;
}

void GLWidget::initializeNoise()
{
    srand(time(0));
    createRandomNoise();
}

void GLWidget::keyboardStandardDown(unsigned char key, int x, int y)
{
    //cout << "key=" << (int)key << endl;

    //    int				dwGlutModifiers		= glutGetModifiers();

    //    bool bAltActive = (dwGlutModifiers & GLUT_ACTIVE_ALT) != 0;
    //    bool bCtrlActive = (dwGlutModifiers & GLUT_ACTIVE_CTRL) != 0;
    //    bool bShiftActive = (dwGlutModifiers & GLUT_ACTIVE_SHIFT) != 0;

    switch (key)
    {
    case '1':
        currentMode = SHADER;
        break;

    case '2':
        currentMode = NOISE_TEST;
        break;

    case 'm':
        rotation.Dump();
        break;

    case 112: // 'p' and 'P'
    case 80:
        bPaused = !bPaused;
        break;

    case 45: // -
    case 95: // _
        g_fCameraDistance = 1.03f * g_fCameraDistance;
        g_fCameraDistance = min(g_fCameraDistance, MAX_CAMERA_DISTANCE);
        break;

    case 61: // =
    case 43: // +
        g_fCameraDistance = 0.98f * g_fCameraDistance;
        g_fCameraDistance = max(g_fCameraDistance, MIN_CAMERA_DISTANCE);
        break;

    case 3: //CTRL + c
    case 27: //esc
        exit(1);
        break;

    case 46: // '>' and '.'
    case 62:
        ShaderManager::get().NextProgram();
        break;

    case 44: // '<' and ",'
    case 60:
        ShaderManager::get().PrevProgram();
        break;

    case 91: // '[' and '{'
    case 123:
        prevShape();
        break;

    case 93: // ']' and '}'
    case 125:
        nextShape();
        break;

    case 32: //spacebar
        createRandomNoise();
        pPlanet->Randomize();
        break;

    case 117: // 'u' and 'U'
    case 85:
        bUpdate = !bUpdate;
        break;

    case 13:
        //        if (bAltActive)
        //        {
        //            if (bFullscreen)
        //            {
        //                glutReshapeWindow(STARTING_WINDOW_SIZE_X, STARTING_WINDOW_SIZE_Y);
        //                glutPositionWindow(WINDOW_OFFSET, WINDOW_OFFSET);
        //            }
        //            else
        //            {
        //                glutFullScreen();
        //            }

        //            bFullscreen = !bFullscreen;
        //        }
        break;

    default:

        break;
    }
}

void GLWidget::loopFunction()
{
    //    if (bUpdate)
    //    {
    //        pTestData->generateMeshForTime(fTime);
    //        fTime += 0.003f;
    //    }

    //    glutPostRedisplay();
}

void GLWidget::mouseMotion(int x, int y)
{
    int xChange = MOUSE_X - x;
    int yChange = MOUSE_Y - y;

    MOUSE_X = x;
    MOUSE_Y = y;

    if (xChange == 0 && yChange == 0)
    {
        return;
    }

    Vector3 axis = Vector3(yChange, xChange, 0.0f);

    Matrix rot = Matrix();
    rot.SetRotation(axis, sqrt((float)abs(xChange) + (float)abs(yChange)));

    rotation.RotateBy(rot);
}

void GLWidget::mouseMove(int button, int state, int x, int y)
{
    MOUSE_X = x;
    MOUSE_Y = y;
}

void GLWidget::nextShape()
{
    if (currentShape + 1 < LAST_SHAPE)
    {
        currentShape = (SHAPE) (currentShape + 1);
    }
}

void GLWidget::prevShape()
{
    if (currentShape > 0)
    {
        currentShape = (SHAPE) (currentShape - 1);
    }
}
